#include "GameManager.h"
#include "Enemy.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

GameManager* GameManager::Instance = NULL;

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

GameManager * GameManager::GetInstance()
{
	if (Instance == NULL)
	{
		Instance = new GameManager();
	}

	return Instance;
}

void GameManager::InitNetwork()
{
	char* _pcPacketData = 0;
	_pcPacketData = new char[MAX_MESSAGE_LENGTH];
	strcpy_s(_pcPacketData, strlen("") + 1, "");

	//Get the instance of the network
	CNetwork& _rNetwork = CNetwork::GetInstance();
	_rNetwork.StartUp();

	_pClient = nullptr;
	_pServer = nullptr;

	_InputBuffer = new CInputLineBuffer(MAX_MESSAGE_LENGTH);

	//Run receive on a separate thread so that it does not block the main client thread.
	if (_eNetworkEntityType == CLIENT) //if network entity is a client
	{

		_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());
		_ClientReceiveThread = std::thread(&CClient::ReceiveData, _pClient, std::ref(_pcPacketData));

	}

	//Run receive of server also on a separate thread 
	else if (_eNetworkEntityType == SERVER) //if network entity is a server
	{

		_pServer = static_cast<CServer*>(_rNetwork.GetInstance().GetNetworkEntity());
		_ServerReceiveThread = std::thread(&CServer::ReceiveData, _pServer, std::ref(_pcPacketData));

	}
}

	void GameManager::UpdateNetWork()
{
	while (_rNetwork.IsOnline())
	{
		if (_eNetworkEntityType == CLIENT) //if network entity is a client
		{
			_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());

			if (_pClient->GetExit()) break;

			//Prepare for reading input from the user










			//------------------------------------------------------------------------

			//Get input from the user
			if (_InputBuffer->Update())
			{
				// we completed a message, lets send it:
				int _iMessageSize = static_cast<int>(strlen(_InputBuffer->GetString()));

				//check if command
				if (_InputBuffer->GetString()[0] == '!')
				{
					TPacket CommandPacket;
					CommandPacket.Serialize(COMMAND, const_cast<char*>(_InputBuffer->GetString()));
					_rNetwork.GetInstance().GetNetworkEntity()->SendData(CommandPacket.PacketData);
				}
				else
				{
					//send message
					//Put the message into a packet structure
					TPacket _packet;
					_packet.Serialize(DATA, const_cast<char*>(_InputBuffer->GetString()));
					_rNetwork.GetInstance().GetNetworkEntity()->SendData(_packet.PacketData);
					//Clear the Input Buffer
					_InputBuffer->ClearString();
					//Print To Screen Top
					_InputBuffer->PrintToScreenTop();
				}


			}
			if (_pClient != nullptr)
			{
				//If the message queue is empty 
				if (_pClient->GetWorkQueue()->empty())
				{
					//Don't do anything
				}
				else
				{
					//Retrieve off a message from the queue and process it
					std::string temp;
					_pClient->GetWorkQueue()->pop(temp);
					_pClient->ProcessData(const_cast<char*>(temp.c_str()));
				}
			}

		}
		else //if you are running a server instance
		{

			if (_pServer != nullptr)
			{
				if (!_pServer->GetWorkQueue()->empty())
				{
					_rNetwork.GetInstance().GetNetworkEntity()->GetRemoteIPAddress(_cIPAddress);
					//std::cout << _cIPAddress
					//<< ":" << _rNetwork.GetInstance().GetNetworkEntity()->GetRemotePort() << "> " << _pcPacketData << std::endl;

					//Retrieve off a message from the queue and process it
					std::pair<sockaddr_in, std::string> dataItem;
					_pServer->GetWorkQueue()->pop(dataItem);
					_pServer->ProcessData(dataItem);
				}
			}
		}


	} //End of while network is Online
}

void GameManager::Init()
{
	//-----Set Current Scene to main menu
	GetInstance()->CurrSc = MENU;

	//-----Time Init
	GetInstance()->previousTimeStamp = (float)glutGet(GLUT_ELAPSED_TIME);
	GetInstance()->timeElapsed = 0;

	//-----Seed Random
	srand((unsigned int)time(NULL));

	//-----Init Audio
	GetInstance()->AS.Init();

	//-----Init Camera
	GetInstance()->Cam.Init(800, 800, (&GetInstance()->MenuOb));

	//----- Init Text Labels
	GetInstance()->LossText.Init("You Lose!!", "Resources/Fonts/arial.ttf", glm::vec2(50.0f, 400.0f), glm::vec3(0.1f, 1.0f, 0.2f), 3.0f);
	GetInstance()->ScoreText.Init(" ", "Resources/Fonts/arial.ttf", glm::vec2(50.0f, 30.0f), glm::vec3(0.5f, 0.8f, 1.0), 1.0f);
	GetInstance()->LivesText.Init(" ", "Resources/Fonts/arial.ttf", glm::vec2(550.0f, 30.0f), glm::vec3(0.5f, 0.8f, 1.0), 1.0f);
	GetInstance()->SetScore(0);
	GetInstance()->SetLives(3);
	GetInstance()->VelocityText.Init(" ", "Resources/Fonts/arial.ttf", glm::vec2(200.0f, 750.0f), glm::vec3(0.1f, 1.0f, 0.2f), 1.0f);

	//-----Objects Init
	//CubeMap
	GetInstance()->CMap.Init(GetInstance()->Cam);

	//Buttons
	GetInstance()->ButMap.insert(std::make_pair("Play", new Button()));

	//Networking Buttons
	GetInstance()->Client.Init(glm::vec2(50.0f, 50.0f), glm::vec2(0.5f, 0.5f), "Client", "Resources/Fonts/arial.ttf", glm::vec3(0.1f, 1.0f, 0.2f));
	GetInstance()->Client.SetActive(true);
	GetInstance()->Server.Init(glm::vec2(700.0f, 50.0f), glm::vec2(0.5f, 0.5f), "Server", "Resources/Fonts/arial.ttf", glm::vec3(0.1f, 1.0f, 0.2f));
	GetInstance()->Server.SetActive(true);

	//Menu Buttons

	GetInstance()->Play.Init(glm::vec2(100.0f, 500.0f), glm::vec2(2.0f, 2.0f), "Play", "Resources/Fonts/arial.ttf", glm::vec3(0.1f, 1.0f, 0.2f));
	GetInstance()->Play.SetActive(true);
	GetInstance()->PlayAI.Init(glm::vec2(100.0f, 350.0f), glm::vec2(2.0f, 2.0f), "Play AI Scene", "Resources/Fonts/arial.ttf", glm::vec3(0.1f, 1.0f, 0.2f));
	GetInstance()->PlayAI.SetActive(true);
	GetInstance()->Exit.Init(glm::vec2(100.0f, 200.0f), glm::vec2(2.0f, 2.0f), "Exit", "Resources/Fonts/arial.ttf", glm::vec3(0.1f, 1.0f, 0.2f));
	GetInstance()->Exit.SetActive(true);
	GetInstance()->Return.Init(glm::vec2(200.0f, 200.0f), glm::vec2(1.0f, 1.0f), "Return To Menu", "Resources/Fonts/arial.ttf", glm::vec3(0.1f, 1.0f, 0.2f));
	GetInstance()->Return.SetActive(true);

	//AI Buttons
	GetInstance()->Seek.Init(glm::vec2(50.0f, 50.0f), glm::vec2(1.0f, 1.0f), "Seek", "Resources/Fonts/arial.ttf", glm::vec3(1.0f, 1.0f, 1.0f));
	GetInstance()->Arrive.Init(glm::vec2(50.0f, 100.0f), glm::vec2(1.0f, 1.0f), "Arrive", "Resources/Fonts/arial.ttf", glm::vec3(1.0f, 1.0f, 1.0f));
	GetInstance()->Wander.Init(glm::vec2(50.0f, 150.0f), glm::vec2(1.0f, 1.0f), "Wander", "Resources/Fonts/arial.ttf", glm::vec3(1.0f, 1.0f, 1.0f));
	GetInstance()->Follow.Init(glm::vec2(50.0f, 200.0f), glm::vec2(1.0f, 1.0f), "Follow", "Resources/Fonts/arial.ttf", glm::vec3(1.0f, 1.0f, 1.0f));
	GetInstance()->Queue.Init(glm::vec2(50.0f, 250.0f), glm::vec2(1.0f, 1.0f), "Queue", "Resources/Fonts/arial.ttf", glm::vec3(1.0f, 1.0f, 1.0f));

	GetInstance()->Contain.Init(glm::vec2(50.0f, 350.0f), glm::vec2(1.0f, 1.0f), "Contain", "Resources/Fonts/arial.ttf", glm::vec3(1.0f, 1.0f, 1.0f));
	GetInstance()->Seperate.Init(glm::vec2(50.0f, 400.0f), glm::vec2(1.0f, 1.0f), "Seperate", "Resources/Fonts/arial.ttf", glm::vec3(1.0f, 1.0f, 1.0f));
	GetInstance()->Avoid.Init(glm::vec2(50.0f, 450.0f), glm::vec2(1.0f, 1.0f), "Avoid", "Resources/Fonts/arial.ttf", glm::vec3(1.0f, 1.0f, 1.0f));

	GetInstance()->Done.Init(glm::vec2(700.0f, 100.0f), glm::vec2(1.0f, 1.0f), "Done", "Resources/Fonts/arial.ttf", glm::vec3(1.0f, 1.0f, 1.0f));

	//Menu Object
	GetInstance()->MenuOb.Init(0, "Resources/Textures/AwesomeFace.png", "Resources/Shaders/Reflection.shader", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f, 20.0f, 10.0f));
	GetInstance()->MenuOb.SetActive(true);
	GetInstance()->MenuOb.SetBaseFoward(glm::vec3(-1.0f, 0.0f, 0.0f));
	GetInstance()->MenuOb.SetBaseLeft(glm::vec3(-1.0f, 0.0f, 0.0f));
	GetInstance()->MenuOb.SetBaseRight(glm::vec3(1.0f, 0.0f, 0.0f));
	GetInstance()->MenuOb.SetBaseUp(glm::vec3(0.0f, 1.0f, 0.0f));
	GetInstance()->MenuOb.SetRotSpd(0.01f);

	//Player
	GetInstance()->player.Init(2, "Resources/Textures/AwesomeFace.png", "Resources/Shaders/BlinnPhong.shader", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 7.5f, 1.0f));

	GetInstance()->player.SetBaseFoward(glm::vec3(0.0f, -1.0f, 0.0f));
	GetInstance()->player.SetBaseLeft(glm::vec3(-1.0f, 0.0f, 0.0f));
	GetInstance()->player.SetBaseRight(glm::vec3(1.0f, 0.0f, 0.0f));
	GetInstance()->player.SetBaseUp(glm::vec3(0.0f, 0.0f, 1.0f));
	GetInstance()->player.SetMaxSpd(20.0f);
	GetInstance()->player.SetAccSpd(1.0f);
	GetInstance()->player.SetFriction(0.25f);
	GetInstance()->player.SetRotSpd(1.0f);

	//-----Init Path
	GetInstance()->path.AddPoint(glm::vec3(0.0f, 0.0f, 0.0f));
	GetInstance()->path.AddPoint(glm::vec3(0.0f, -10000.0f, 0.0f));


	//-----Init Network
	GetInstance()->InitNetwork();
}

void GameManager::Render(void)
{
	//-----ClearScreen
	GetInstance()->Ren.Clear();

	//-----Render CubeMap
	GetInstance()->CMap.Render();

	//-----Render Scene
	switch (GetInstance()->CurrSc)
	{
	case MENU:
	{
		GetInstance()->RenMenu();
		break;
	}
	case PLAY:
	{
		GetInstance()->RenPlay();
		break;
	}
	case PLAYAI:
	{
		GetInstance()->RenAI();
		break;
	}
	case LOSS:
	{
		GetInstance()->RenLoss();
		break;
	}
	}
	glutSwapBuffers();
}

void GameManager::Update()
{
	//-----Update Time
	float currentTime = (float)glutGet(GLUT_ELAPSED_TIME);
	GetInstance()->deltaTime = (currentTime - GetInstance()->previousTimeStamp) * 0.001f;
	GetInstance()->previousTimeStamp = currentTime;
	GetInstance()->timeElapsed += GetInstance()->deltaTime;

	//-----Update Audio System
	GetInstance()->AS.GetID()->update();

	//-----Update CubeMap
	GetInstance()->CMap.Update();

	//-----Update Camera
	GetInstance()->Cam.Update(GetInstance()->timeElapsed);

	switch (GetInstance()->CurrSc)
	{
	case MENU:
	{
		GetInstance()->UpdMenu();
		break;
	}
	case PLAY:
	{
		GetInstance()->UpdPlay();
		break;
	}
	case PLAYAI:
	{
		GetInstance()->UpdAI();
		break;
	}
	case LOSS:
	{
		GetInstance()->UpdLoss();
		break;
	}
	}

	glutPostRedisplay();

}

void GameManager::RenMenu()
{
	//-----Render Object
	GetInstance()->MenuOb.Render();

	//-----Render Buttons
	GetInstance()->Play.Render();
	GetInstance()->PlayAI.Render();
	GetInstance()->Exit.Render();

	//Networking Buttons
	GetInstance()->Client.Render();
	GetInstance()->Server.Render();
}

void GameManager::RenPlay()
{
	//-----Render Objects
	for (unsigned int i = 0; i < GetInstance()->ObVec.size(); i++)
	{
		GetInstance()->ObVec.at(i).Render();
	}
	//Enemies
	for (unsigned int i = 0; i < GetInstance()->EnVec.size(); i++)
	{
		GetInstance()->EnVec.at(i).Render();
	}
	//Player
	GetInstance()->player.Render();

	//-----Render Text
	GetInstance()->ScoreText.Render();
	GetInstance()->LivesText.Render();
	GetInstance()->VelocityText.Render();


}

void GameManager::RenAI()
{
	//-----Render Objects
	for (unsigned int i = 0; i < GetInstance()->ObVec.size(); i++)
	{
		GetInstance()->ObVec.at(i).Render();
	}
	//Enemies
	for (unsigned int i = 0; i < GetInstance()->EnVec.size(); i++)
	{
		GetInstance()->EnVec.at(i).Render();
	}
	//Player
	GetInstance()->player.Render();

	//-----Menu Buttons Render
	GetInstance()->Seek.Render();
	GetInstance()->Arrive.Render();
	GetInstance()->Wander.Render();
	GetInstance()->Follow.Render();
	GetInstance()->Queue.Render();

	GetInstance()->Contain.Render();
	GetInstance()->Seperate.Render();
	GetInstance()->Avoid.Render();

	GetInstance()->Done.Render();
}

void GameManager::RenLoss()
{
	//-----Render Objects
	for (unsigned int i = 0; i < GetInstance()->ObVec.size(); i++)
	{
		GetInstance()->ObVec.at(i).Render();
	}
	//Enemies
	for (unsigned int i = 0; i < GetInstance()->EnVec.size(); i++)
	{
		GetInstance()->EnVec.at(i).Render();
	}
	//Player
	GetInstance()->player.Render();
	GetInstance()->LossText.Render();
	GetInstance()->Return.Render();
}

void GameManager::UpdMenu()
{
	GetInstance()->Play.Update();
	GetInstance()->PlayAI.Update();
	GetInstance()->Exit.Update();
	GetInstance()->Client.Update();
	GetInstance()->Server.Update();

	if (GetInstance()->Play.GetClicked())
	{
		CurrSc = PLAY;
		InstPlay();
		Cam.SetFollowing(&player);
		Cam.SetRotFollow(true);
		GetInstance()->SetLives(3);
		GetInstance()->Play.SetClicked(false);
		EnMoveType = 5; // 0 = Seek , 1 = Arrive, 2 = Wander, 3 = Path Follow, 4 = leader follow, 5 = Queue;
	}
	if (GetInstance()->PlayAI.GetClicked())
	{
		CurrSc = PLAYAI;
		InstAI();
		Cam.SetFollowing(&player);
		Cam.SetRotFollow(true);
		GetInstance()->PlayAI.SetClicked(false);
		GetInstance()->SetLives(3);
		EnMoveType = 0; // 0 = Seek , 1 = Arrive, 2 = Wander, 3 = Path Follow, 4 = leader follow, 5 = Queue;
	}
	if (Client.GetClicked())
	{

	}
	if (Server.GetClicked())
	{

	}


	GetInstance()->MenuOb.RotateOnAxis(glm::vec3(0.0f, 1.0f, 0.0f));
	GetInstance()->MenuOb.Update(deltaTime);
}

void GameManager::UpdPlay()
{
	//-----Process Input
	GetInstance()->player.ProcessInput(deltaTime);

	//-----Update Objects
	for (unsigned int i = 0; i < GetInstance()->ObVec.size(); i++)
	{
		GetInstance()->ObVec.at(i).Update(GetInstance()->deltaTime);
	}
	//Enemies
	for (unsigned int i = 0; i < GetInstance()->EnVec.size(); i++)
	{
		//GetInstance()->EnVec.at(i).MoveTo(GetInstance()->player.GetPosition(), EnMoveType);
		GetInstance()->EnVec.at(i).MoveTo(GetInstance()->player.GetCenter(), EnMoveType, path);
		GetInstance()->EnVec.at(i).Update(GetInstance()->deltaTime);
	}
	//Player
	GetInstance()->player.Update(GetInstance()->deltaTime);

	//-----Update Text
	SetVel();

	if (GetInstance()->Lives == 0)
	{
		CurrSc = LOSS;
	}
}

void GameManager::UpdAI()
{
	//-----Process Input
	GetInstance()->player.ProcessInput(deltaTime);

	//-----Update Objects
	for (unsigned int i = 0; i < GetInstance()->ObVec.size(); i++)
	{
		GetInstance()->ObVec.at(i).Update(GetInstance()->deltaTime);
	}
	//Enemies
	for (unsigned int i = 0; i < GetInstance()->EnVec.size(); i++)
	{
		//GetInstance()->EnVec.at(i).MoveTo(GetInstance()->player.GetPosition(), EnMoveType);
		GetInstance()->EnVec.at(i).MoveTo(GetInstance()->player.GetCenter(), EnMoveType, path);
		GetInstance()->EnVec.at(i).Update(GetInstance()->deltaTime);
	}
	//Player
	GetInstance()->player.Update(GetInstance()->deltaTime);




	if (GetInstance()->Seek.GetClicked())	EnMoveType = 0;
	if (GetInstance()->Arrive.GetClicked())	EnMoveType = 1;
	if (GetInstance()->Wander.GetClicked())	EnMoveType = 2;
	if (GetInstance()->Follow.GetClicked())	EnMoveType = 4;
	if (GetInstance()->Queue.GetClicked())	EnMoveType = 5;

	if (GetInstance()->EnMoveType == 0)
	{
		GetInstance()->Seek.SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
		GetInstance()->Arrive.SetClicked(false);
		GetInstance()->Wander.SetClicked(false);
		GetInstance()->Follow.SetClicked(false);
		GetInstance()->Queue.SetClicked(false);
	}
	else GetInstance()->Seek.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	if (GetInstance()->EnMoveType == 1)
	{
		GetInstance()->Arrive.SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
		GetInstance()->Seek.SetClicked(false);
		GetInstance()->Wander.SetClicked(false);
		GetInstance()->Follow.SetClicked(false);
		GetInstance()->Queue.SetClicked(false);
	}
	else GetInstance()->Arrive.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	if (GetInstance()->EnMoveType == 2)
	{
		GetInstance()->Wander.SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
		GetInstance()->Seek.SetClicked(false);
		GetInstance()->Arrive.SetClicked(false);
		GetInstance()->Follow.SetClicked(false);
		GetInstance()->Queue.SetClicked(false);
	}
	else GetInstance()->Wander.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	if (GetInstance()->EnMoveType == 4)
	{
		GetInstance()->Follow.SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
		GetInstance()->Seek.SetClicked(false);
		GetInstance()->Arrive.SetClicked(false);
		GetInstance()->Wander.SetClicked(false);
		GetInstance()->Queue.SetClicked(false);
	}
	else GetInstance()->Follow.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	if (GetInstance()->EnMoveType == 5)
	{
		GetInstance()->Queue.SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
		GetInstance()->Seek.SetClicked(false);
		GetInstance()->Arrive.SetClicked(false);
		GetInstance()->Wander.SetClicked(false);
		GetInstance()->Follow.SetClicked(false);
	}
	else GetInstance()->Queue.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	if (GetInstance()->Contain.GetClicked())
	{
		GetInstance()->Con = !GetInstance()->Con;
		if (GetInstance()->Con)	GetInstance()->Contain.SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
		else					GetInstance()->Contain.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		GetInstance()->Contain.SetClicked(false);
	}
	if (GetInstance()->Seperate.GetClicked())
	{
		GetInstance()->Sep = !GetInstance()->Sep;
		if (GetInstance()->Sep)		GetInstance()->Seperate.SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
		else						GetInstance()->Seperate.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		GetInstance()->Seperate.SetClicked(false);
	}

	if (GetInstance()->Avoid.GetClicked())
	{
		GetInstance()->avoid = !GetInstance()->avoid;
		if (GetInstance()->avoid)	GetInstance()->Avoid.SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
		else						GetInstance()->Avoid.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		GetInstance()->Avoid.SetClicked(false);
	}

	if (GetInstance()->Done.GetClicked())
	{
		CurrSc = MENU;
		GetInstance()->Cam.SetFollowing(&MenuOb);
		GetInstance()->Cam.SetRotFollow(false);
		GetInstance()->Done.SetClicked(false);

		GetInstance()->ObVec.clear();
		GetInstance()->EnVec.clear();
		GetInstance()->player.SetPosition(glm::vec3(0.0f));
	}


	GetInstance()->Seek.ProcessInput();
	GetInstance()->Arrive.ProcessInput();
	GetInstance()->Wander.ProcessInput();
	GetInstance()->Follow.ProcessInput();
	GetInstance()->Queue.ProcessInput();

	GetInstance()->Contain.ProcessInput();
	GetInstance()->Seperate.ProcessInput();
	GetInstance()->Avoid.ProcessInput();

	GetInstance()->Done.ProcessInput();


}

void GameManager::UpdLoss()
{
	GetInstance()->Return.ProcessInput();
	if (GetInstance()->Return.GetClicked())
	{
		GetInstance()->CurrSc = MENU;
		GetInstance()->Cam.SetFollowing(&MenuOb);
		GetInstance()->Cam.SetRotFollow(false);

		GetInstance()->ObVec.clear();
		GetInstance()->EnVec.clear();
		GetInstance()->player.SetPosition(glm::vec3(0.0f));
	}
}

void GameManager::InstPlay()
{
	//Basic Objects
	Object* NewObject;
	for (int i = 0; i < 10; i++)
	{
		NewObject = new Object;
		GetInstance()->ObVec.push_back(*NewObject);
	}

	for (unsigned int i = 0; i < GetInstance()->ObVec.size(); i++)
	{
		GetInstance()->ObVec.at(i).Init(0, "Resources/Textures/AwesomeFace.png",
			"Resources/Shaders/BlinnPhong.shader",
			glm::vec3(250 - (rand() % 500)),
			glm::vec3((rand() % 15)));
	}

	//Enemies
	Enemy* newEn;
	for (int i = 0; i < 50; i++)	//Must be Odd
	{
		newEn = new Enemy;
		GetInstance()->EnVec.push_back(*newEn);
	}
	for (unsigned int i = 0; i < GetInstance()->EnVec.size(); i++)
	{
		GetInstance()->EnVec.at(i).Init(1, "Resources/Textures/AwesomeFace.png",
			"Resources/Shaders/BlinnPhong.shader",
			glm::vec3(100 - (rand() % 100 + 100), 100 - (rand() % 100 + 100), 100 - (rand() % 100 + 100)),
			glm::vec3(5.0f));
		GetInstance()->EnVec.at(i).SetMaxSpd(50.0f);
		GetInstance()->EnVec.at(i).SetAccSpd(2.0f);
		GetInstance()->EnVec.at(i).SetFriction(0.4f);
		GetInstance()->EnVec.at(i).SetWanRad(10.0f);
		GetInstance()->EnVec.at(i).SetConRad(200.0f);
		GetInstance()->EnVec.at(i).SetID(i);
	}

}

void GameManager::InstAI()
{
	//Basic Objects
	Object* NewObject;
	for (int i = 0; i < 10; i++)
	{
		NewObject = new Object;
		GetInstance()->ObVec.push_back(*NewObject);
	}

	for (unsigned int i = 0; i < GetInstance()->ObVec.size(); i++)
	{
		GetInstance()->ObVec.at(i).Init(0, "Resources/Textures/AwesomeFace.png",
			"Resources/Shaders/BlinnPhong.shader",
			glm::vec3(250 - (rand() % 500)),
			glm::vec3((rand() % 15)));
	}

	//Enemies
	Enemy* newEn;
	for (int i = 0; i < 50; i++)	//Must be Odd
	{
		newEn = new Enemy;
		GetInstance()->EnVec.push_back(*newEn);
	}
	for (unsigned int i = 0; i < GetInstance()->EnVec.size(); i++)
	{
		GetInstance()->EnVec.at(i).Init(1, "Resources/Textures/AwesomeFace.png",
			"Resources/Shaders/BlinnPhong.shader",
			glm::vec3(100 - (rand() % 100 + 100), 100 - (rand() % 100 + 100), 100 - (rand() % 100 + 100)),
			glm::vec3(5.0f));
		GetInstance()->EnVec.at(i).SetMaxSpd(50.0f);
		GetInstance()->EnVec.at(i).SetAccSpd(0.5f);
		GetInstance()->EnVec.at(i).SetFriction(0.1f);
		GetInstance()->EnVec.at(i).SetWanRad(5.0f);
		GetInstance()->EnVec.at(i).SetConRad(200.0f);
		GetInstance()->EnVec.at(i).SetID(i);
	}
}

void GameManager::SetScore(int newScore)
{
	Score = newScore;
	ScoreText.SetText("Score: " + to_string(Score));
}

void GameManager::SetLives(int newLives)
{
	Lives = newLives;
	LivesText.SetText("Lives: " + to_string(Lives));
}

void GameManager::SetVel()
{
	glm::vec3 Vel = GetInstance()->player.GetVelocity();
	float Velocity = abs(Vel.x + Vel.y + Vel.z);
	VelocityText.SetText("Velocity: " + to_string(Velocity));
}
