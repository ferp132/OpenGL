#include "GameManager.h"
#include "Enemy.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

GameManager* GameManager::Instance = NULL;

GameManager::GameManager()
{
	//CNetwork& _rNetwork = CNetwork::GetInstance();
	_rNetwork.StartUp();
	//GetInstance()->_eNetworkEntityType = NONE;
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

	if (!_rNetwork.GetInstance().Initialise(_eNetworkEntityType))
	{
		std::cout << "Unable to initialise the Network........";
	}

	//Run receive on a separate thread so that it does not block the main client thread.
	if (_eNetworkEntityType == CLIENT) //if network entity is a client
	{
		_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());
		GetInstance()->_ClientReceiveThread = std::thread(&CClient::ReceiveData, _pClient, std::ref(_pcPacketData));
	}

	//Run receive of server also on a separate thread 
	else if (_eNetworkEntityType == SERVER) //if network entity is a server
	{
		_pServer = static_cast<CServer*>(_rNetwork.GetInstance().GetNetworkEntity());
		GetInstance()->_ServerReceiveThread = std::thread(&CServer::ReceiveData, _pServer, std::ref(_pcPacketData));
	}
}

void GameManager::UpdateNetWork()
{
	if (_rNetwork.IsOnline())
	{
		if (_eNetworkEntityType == CLIENT) //if network entity is a client
		{
			_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());

			//if (_pClient->GetExit()) break;

			//Prepare for reading input from the user

			//------------------------------------------------------------------------

			//Get input from the user
			//if (_InputBuffer->Update())
			//{
			//	// we completed a message, lets send it:
			//	int _iMessageSize = static_cast<int>(strlen(_InputBuffer->GetString()));

			//	//check if command
			//	if (_InputBuffer->GetString()[0] == '!')
			//	{
			//		TPacket CommandPacket;
			//		CommandPacket.Serialize(COMMAND, const_cast<char*>(_InputBuffer->GetString()));
			//		_rNetwork.GetInstance().GetNetworkEntity()->SendData(CommandPacket.PacketData);
			//	}
			//	else
			//	{
			//		//send message
			//		//Put the message into a packet structure
			//		TPacket _packet;
			//		_packet.Serialize(DATA, const_cast<char*>(_InputBuffer->GetString()));
			//		_rNetwork.GetInstance().GetNetworkEntity()->SendData(_packet.PacketData);
			//		//Clear the Input Buffer
			//		_InputBuffer->ClearString();
			//		//Print To Screen Top
			//		_InputBuffer->PrintToScreenTop();
			//	}


			
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

void GameManager::InitButtons()
{
	//-----Main Menu
	GetInstance()->ButMap.insert(std::make_pair("Play",		new Button(glm::vec2(100.0f, 500.0f), glm::vec2(1.0f, 1.0f), "Play",			ftArial, glm::vec3(0.1f, 1.0f, 0.2f))));
	GetInstance()->ButMap.insert(std::make_pair("PlayAI",	new Button(glm::vec2(100.0f, 400.0f), glm::vec2(1.0f, 1.0f), "Play AI Scene",	ftArial, glm::vec3(0.1f, 1.0f, 0.2f))));
	GetInstance()->ButMap.insert(std::make_pair("Multi",	new Button(glm::vec2(100.0f, 300.0f), glm::vec2(1.0f, 1.0f), "Multi-Player",	ftArial, glm::vec3(0.1f, 1.0f, 0.2f))));
	GetInstance()->ButMap.insert(std::make_pair("Exit",		new Button(glm::vec2(100.0f, 200.0f), glm::vec2(1.0f, 1.0f), "Exit",			ftArial, glm::vec3(0.1f, 1.0f, 0.2f))));

	//-----AI Scene
	GetInstance()->ButMap.insert(std::make_pair("Seek",		new Button(glm::vec2(50.0f, 50.0f), glm::vec2(1.0f, 1.0f), "Seek", ftArial, glm::vec3(1.0f, 1.0f, 1.0f))));
	GetInstance()->ButMap.insert(std::make_pair("Arrive",	new Button(glm::vec2(50.0f, 100.0f), glm::vec2(1.0f, 1.0f), "Arrive", ftArial, glm::vec3(1.0f, 1.0f, 1.0f))));
	GetInstance()->ButMap.insert(std::make_pair("Wander",	new Button(glm::vec2(50.0f, 150.0f), glm::vec2(1.0f, 1.0f), "Wander", ftArial, glm::vec3(1.0f, 1.0f, 1.0f))));
	GetInstance()->ButMap.insert(std::make_pair("Follow",	new Button(glm::vec2(50.0f, 200.0f), glm::vec2(1.0f, 1.0f), "Follow", ftArial, glm::vec3(1.0f, 1.0f, 1.0f))));
	GetInstance()->ButMap.insert(std::make_pair("Queue",	new Button(glm::vec2(50.0f, 250.0f), glm::vec2(1.0f, 1.0f), "Queue", ftArial, glm::vec3(1.0f, 1.0f, 1.0f))));
	GetInstance()->ButMap.insert(std::make_pair("Contain",	new Button(glm::vec2(50.0f, 350.0f), glm::vec2(1.0f, 1.0f), "Contain", ftArial, glm::vec3(1.0f, 1.0f, 1.0f))));
	GetInstance()->ButMap.insert(std::make_pair("Seperate", new Button(glm::vec2(50.0f, 400.0f), glm::vec2(1.0f, 1.0f), "Seperate", ftArial, glm::vec3(1.0f, 1.0f, 1.0f))));
	GetInstance()->ButMap.insert(std::make_pair("Avoid",	new Button(glm::vec2(50.0f, 450.0f), glm::vec2(1.0f, 1.0f), "Avoid", ftArial, glm::vec3(1.0f, 1.0f, 1.0f))));
	GetInstance()->ButMap.insert(std::make_pair("Done",		new Button(glm::vec2(700.0f, 100.0f), glm::vec2(1.0f, 1.0f), "Done", ftArial, glm::vec3(1.0f, 1.0f, 1.0f))));

	//-----Game Scene
	GetInstance()->ButMap.insert(std::make_pair("Return",	new Button(glm::vec2(200.0f, 200.0f), glm::vec2(1.0f, 1.0f), "Return To Menu", ftArial, glm::vec3(0.1f, 1.0f, 0.2f))));

	//Networking
	GetInstance()->ButMap.insert(std::make_pair("Client",	new Button(glm::vec2(300.0f, 600.0f), glm::vec2(1.0f, 1.0f), "Client", ftArial, glm::vec3(0.1f, 1.0f, 0.2f))));
	GetInstance()->ButMap.insert(std::make_pair("Server",	new Button(glm::vec2(300.0f, 400.0f), glm::vec2(1.0f, 1.0f), "Server", ftArial, glm::vec3(0.1f, 1.0f, 0.2f))));

}

void GameManager::InitPlayer()
{
	GetInstance()->PlayerMap["LocalPlayer"] = new Player;
	GetInstance()->PlayerMap["LocalPlayer"]->Init(2, "Resources/Textures/AwesomeFace.png",
		"Resources/Shaders/BlinnPhong.shader", glm::vec3(0.0f), glm::vec3(1.0f));
	GetInstance()->MenuOb.SetBaseFoward(glm::vec3(-1.0f, 0.0f, 0.0f));
	GetInstance()->MenuOb.SetBaseLeft(glm::vec3(-1.0f, 0.0f, 0.0f));
	GetInstance()->MenuOb.SetBaseRight(glm::vec3(1.0f, 0.0f, 0.0f));
	GetInstance()->MenuOb.SetBaseUp(glm::vec3(0.0f, 1.0f, 0.0f));
	GetInstance()->MenuOb.SetRotSpd(0.01f);
}

void GameManager::Init()
{
	//Set ftArialValue
	GetInstance()->ftArial = "Resources/Fonts/arial.ttf";

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

	//-----Init Text Labels
	GetInstance()->LossText.Init("You Lose!!",	GetInstance()->ftArial, glm::vec2(50.0f, 400.0f),	glm::vec3(0.1f, 1.0f, 0.2f), 3.0f);
	GetInstance()->ScoreText.Init(" ",			GetInstance()->ftArial, glm::vec2(50.0f, 30.0f),	glm::vec3(0.5f, 0.8f, 1.0), 1.0f);
	GetInstance()->LivesText.Init(" ",			GetInstance()->ftArial, glm::vec2(550.0f, 30.0f),	glm::vec3(0.5f, 0.8f, 1.0), 1.0f);
	GetInstance()->VelocityText.Init(" ",		GetInstance()->ftArial, glm::vec2(200.0f, 750.0f),	glm::vec3(0.1f, 1.0f, 0.2f), 1.0f);

	GetInstance()->SetScore(0);
	GetInstance()->SetLives(3);


	//-----Objects Init
	//CubeMap
	GetInstance()->CMap.Init(GetInstance()->Cam);

	//Local Player Init
	GetInstance()->InitPlayer();

	//Buttons
	GetInstance()->InitButtons();

	//Menu Object
	GetInstance()->MenuOb.Init(0, "Resources/Textures/AwesomeFace.png", "Resources/Shaders/Reflection.shader", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.5f, 10.0f, 5.0f));
	GetInstance()->MenuOb.SetActive(true);
	GetInstance()->MenuOb.SetBaseFoward(glm::vec3(-1.0f, 0.0f, 0.0f));
	GetInstance()->MenuOb.SetBaseLeft(glm::vec3(-1.0f, 0.0f, 0.0f));
	GetInstance()->MenuOb.SetBaseRight(glm::vec3(1.0f, 0.0f, 0.0f));
	GetInstance()->MenuOb.SetBaseUp(glm::vec3(0.0f, 1.0f, 0.0f));
	GetInstance()->MenuOb.SetRotSpd(0.01f);


	//-----Init Path
	GetInstance()->path.AddPoint(glm::vec3(0.0f, 0.0f, 0.0f));
	GetInstance()->path.AddPoint(glm::vec3(0.0f, -10000.0f, 0.0f));
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
	case MULTI:
	{
		GetInstance()->RenMulti();
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

	//-----Update Network
	if(GetInstance()->_eNetworkEntityType != NONE) GetInstance()->UpdateNetWork();

	for (std::map<std::string, Button*>::iterator it = GetInstance()->ButMap.begin(); it != GetInstance()->ButMap.end(); it++)
	{
		it->second->SetClicked(false);
	}

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
	case MULTI:
	{
		GetInstance()->UpMulti();
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

	GetInstance()->ButMap["Play"]->Render();
	GetInstance()->ButMap["PlayAI"]->Render();
	GetInstance()->ButMap["Multi"]->Render();
	GetInstance()->ButMap["Exit"]->Render();
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
	//Players Render
	for (std::map<std::string, Player*>::iterator it = GetInstance()->PlayerMap.begin(); it != GetInstance()->PlayerMap.end(); it++)
	{
		it->second->Render();
	}
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

	//Players Render
	for (std::map<std::string, Player*>::iterator it = GetInstance()->PlayerMap.begin(); it != GetInstance()->PlayerMap.end(); it++)
	{
		it->second->Render();
	}
	//-----Menu Buttons Render
	GetInstance()->ButMap["Seek"]->Render();
	GetInstance()->ButMap["Arrive"]->Render();
	GetInstance()->ButMap["Wander"]->Render();
	GetInstance()->ButMap["Follow"]->Render();
	GetInstance()->ButMap["Queue"]->Render();
	GetInstance()->ButMap["Contain"]->Render();
	GetInstance()->ButMap["Seperate"]->Render();
	GetInstance()->ButMap["Avoid"]->Render();
	GetInstance()->ButMap["Done"]->Render();
}

void GameManager::RenMulti()
{
	//-----Render Object
	GetInstance()->MenuOb.Render();

	//Networking Buttons
	if (GetInstance()->ButMap["Client"]->GetActive())
	{
		GetInstance()->ButMap["Client"]->Render();
	}
	if (GetInstance()->ButMap["Return"]->GetActive())	GetInstance()->ButMap["Return"]->Render();
	if (GetInstance()->ButMap["Server"]->GetActive())	GetInstance()->ButMap["Server"]->Render();

	//-----Render TExt
	for (std::map<std::string, TextLabel*>::iterator it = GetInstance()->NetText.begin(); it != GetInstance()->NetText.end(); it++)
	{
		it->second->Render();
	}

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
	//Players
	for (std::map<std::string, Player*>::iterator it = GetInstance()->PlayerMap.begin(); it != GetInstance()->PlayerMap.end(); it++)
	{
		it->second->Render();
	}

	GetInstance()->LossText.Render();
	GetInstance()->ButMap["Return"]->Render();
}

void GameManager::UpdMenu()
{
	GetInstance()->ButMap["Play"]->Update();
	GetInstance()->ButMap["PlayAI"]->Update();
	GetInstance()->ButMap["Multi"]->Update();
	GetInstance()->ButMap["Exit"]->Update();



	//Process Input

	if (GetInstance()->ButMap["Play"]->GetClicked())
	{
		CurrSc = PLAY;
		InstPlay();
		Cam.SetFollowing(GetInstance()->PlayerMap["LocalPlayer"]);
		Cam.SetRotFollow(true);
		GetInstance()->SetLives(3);
		EnMoveType = 5; // 0 = Seek , 1 = Arrive, 2 = Wander, 3 = Path Follow, 4 = leader follow, 5 = Queue;
	}
	if (GetInstance()->ButMap["PlayAI"]->GetClicked())
	{
		CurrSc = PLAYAI;
		InstAI();
		Cam.SetFollowing(GetInstance()->PlayerMap["LocalPlayer"]);
		Cam.SetRotFollow(true);
		GetInstance()->SetLives(3);
		EnMoveType = 0; // 0 = Seek , 1 = Arrive, 2 = Wander, 3 = Path Follow, 4 = leader follow, 5 = Queue;
	}
	if (GetInstance()->ButMap["Multi"]->GetClicked())
	{
		CurrSc = MULTI;
		GetInstance()->ButMap["Client"]->SetActive(true);
		GetInstance()->ButMap["Return"]->SetActive(true);
		GetInstance()->ButMap["Server"]->SetActive(true);
	}

	GetInstance()->MenuOb.RotateOnAxis(glm::vec3(0.0f, 1.0f, 0.0f));
	GetInstance()->MenuOb.Update(deltaTime);
}

void GameManager::UpdPlay()
{
	//-----Process Input
	GetInstance()->PlayerMap["LocalPlayer"]->ProcessInput(deltaTime);

	//-----Update Objects
	for (unsigned int i = 0; i < GetInstance()->ObVec.size(); i++)
	{
		GetInstance()->ObVec.at(i).Update(GetInstance()->deltaTime);
	}
	//Enemies
	for (unsigned int i = 0; i < GetInstance()->EnVec.size(); i++)
	{
		//GetInstance()->EnVec.at(i).MoveTo(GetInstance()->PlayerMap["LocalPlayer"]->GetPosition(), EnMoveType);
		GetInstance()->EnVec.at(i).MoveTo(GetInstance()->PlayerMap["LocalPlayer"]->GetCenter(), EnMoveType, path);
		GetInstance()->EnVec.at(i).Update(GetInstance()->deltaTime);
	}
	//Player
	GetInstance()->PlayerMap["LocalPlayer"]->Update(GetInstance()->deltaTime);

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
	GetInstance()->PlayerMap["LocalPlayer"]->ProcessInput(deltaTime);

	//-----Update Objects
	for (unsigned int i = 0; i < GetInstance()->ObVec.size(); i++)
	{
		GetInstance()->ObVec.at(i).Update(GetInstance()->deltaTime);
	}
	//Enemies
	for (unsigned int i = 0; i < GetInstance()->EnVec.size(); i++)
	{
		//GetInstance()->EnVec.at(i).MoveTo(GetInstance()->PlayerMap["LocalPlayer"]->GetPosition(), EnMoveType);
		GetInstance()->EnVec.at(i).MoveTo(GetInstance()->PlayerMap["LocalPlayer"]->GetCenter(), EnMoveType, path);
		GetInstance()->EnVec.at(i).Update(GetInstance()->deltaTime);
	}
	//Player
	GetInstance()->PlayerMap["LocalPlayer"]->Update(GetInstance()->deltaTime);




	if (GetInstance()->ButMap["Seek"]->GetClicked())	EnMoveType = 0;
	if (GetInstance()->ButMap["Arrive"]->GetClicked())	EnMoveType = 1;
	if (GetInstance()->ButMap["Wander"]->GetClicked())	EnMoveType = 2;
	if (GetInstance()->ButMap["Follow"]->GetClicked())	EnMoveType = 4;
	if (GetInstance()->ButMap["Queue"]->GetClicked())	EnMoveType = 5;

	if (GetInstance()->EnMoveType == 0)
	{
		GetInstance()->ButMap["Seek"]->SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
	}
	else GetInstance()->ButMap["Seek"]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	if (GetInstance()->EnMoveType == 1)
	{
		GetInstance()->ButMap["Arrive"]->SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
	}
	else GetInstance()->ButMap["Arrive"]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	if (GetInstance()->EnMoveType == 2)
	{
		GetInstance()->ButMap["Wander"]->SetColor(glm::vec3(0.1f, 1.0f, 0.2f));

	}
	else GetInstance()->ButMap["Wander"]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	if (GetInstance()->EnMoveType == 4)
	{
		GetInstance()->ButMap["Follow"]->SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
	}
	else GetInstance()->ButMap["Follow"]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	if (GetInstance()->EnMoveType == 5)
	{
		GetInstance()->ButMap["Queue"]->SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
	}
	else GetInstance()->ButMap["Queue"]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	if (GetInstance()->ButMap["Contain"]->GetClicked())
	{
		GetInstance()->Con = !GetInstance()->Con;
		if (GetInstance()->Con)	GetInstance()->ButMap["Contain"]->SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
		else					GetInstance()->ButMap["Contain"]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		GetInstance()->ButMap["Contain"]->SetClicked(false);
	}
	if (GetInstance()->ButMap["Seperate"]->GetClicked())
	{
		GetInstance()->Sep = !GetInstance()->Sep;
		if (GetInstance()->Sep)		GetInstance()->ButMap["Seperate"]->SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
		else						GetInstance()->ButMap["Seperate"]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		GetInstance()->ButMap["Seperate"]->SetClicked(false);
	}

	if (GetInstance()->ButMap["Avoid"]->GetClicked())
	{
		GetInstance()->avoid = !GetInstance()->avoid;
		if (GetInstance()->avoid)	GetInstance()->ButMap["Avoid"]->SetColor(glm::vec3(0.1f, 1.0f, 0.2f));
		else						GetInstance()->ButMap["Avoid"]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		GetInstance()->ButMap["Avoid"]->SetClicked(false);
	}

	if (GetInstance()->ButMap["Done"]->GetClicked())
	{
		CurrSc = MENU;
		GetInstance()->Cam.SetFollowing(&MenuOb);
		GetInstance()->Cam.SetRotFollow(false);
		GetInstance()->ButMap["Done"]->SetClicked(false);

		GetInstance()->ObVec.clear();
		GetInstance()->EnVec.clear();
		GetInstance()->PlayerMap["LocalPlayer"]->SetPosition(glm::vec3(0.0f));
	}


	GetInstance()->ButMap["Seek"]->ProcessInput();
	GetInstance()->ButMap["Arrive"]->ProcessInput();
	GetInstance()->ButMap["Wander"]->ProcessInput();
	GetInstance()->ButMap["Follow"]->ProcessInput();
	GetInstance()->ButMap["Queue"]->ProcessInput();

	GetInstance()->ButMap["Contain"]->ProcessInput();
	GetInstance()->ButMap["Seperate"]->ProcessInput();
	GetInstance()->ButMap["Avoid"]->ProcessInput();

	GetInstance()->ButMap["Done"]->ProcessInput();


}

void GameManager::UpMulti()
{
	//Networking Buttons
	if (GetInstance()->ButMap["Client"]->GetActive())	GetInstance()->ButMap["Client"]->Update();
	if (GetInstance()->ButMap["Return"]->GetActive())	GetInstance()->ButMap["Return"]->Update();
	if(GetInstance()->ButMap["Server"]->GetActive())	GetInstance()->ButMap["Server"]->Update();

	if (GetInstance()->ButMap["Client"]->GetClicked() && _eNetworkEntityType == 0)
	{
		GetInstance()->ButMap["Server"]->SetActive(false);
		GetInstance()->ButMap["Client"]->SetActive(false);

		_eNetworkEntityType = CLIENT;
		GetInstance()->InitNetwork();
			//GetInstance()->NetText["ServerFound"] = new TextLabel();
		//	GetInstance()->NetText["ServerFound"]->Init("Server Found", GetInstance()->ftArial, glm::vec2(50.0f, 400.0f), glm::vec3(0.1f, 1.0f, 0.2f), 3.0f);

			//GetInstance()->NetText["UserName"] = new TextLabel();
		//	GetInstance()->NetText["UserName"]->Init("Enter A Username", GetInstance()->ftArial, glm::vec2(50.0f, 400.0f), glm::vec3(0.1f, 1.0f, 0.2f), 3.0f);


	}
	if (GetInstance()->ButMap["Server"]->GetClicked() && _eNetworkEntityType == 0)
	{
		GetInstance()->ButMap["Client"]->SetActive(false);
		GetInstance()->ButMap["Server"]->SetActive(false);

		_eNetworkEntityType = SERVER;
		GetInstance()->InitNetwork();

	}

	if (GetInstance()->ButMap["Return"]->GetClicked())
	{
		GetInstance()->CurrSc = MENU;
	}

	GetInstance()->MenuOb.RotateOnAxis(glm::vec3(0.0f, 1.0f, 0.0f));
	GetInstance()->MenuOb.Update(deltaTime);

}

void GameManager::UpdLoss()
{
	GetInstance()->ButMap["Return"]->ProcessInput();
	if (GetInstance()->ButMap["Return"]->GetClicked())
	{
		GetInstance()->CurrSc = MENU;
		GetInstance()->Cam.SetFollowing(&MenuOb);
		GetInstance()->Cam.SetRotFollow(false);

		GetInstance()->ObVec.clear();
		GetInstance()->EnVec.clear();
		GetInstance()->PlayerMap["LocalPlayer"]->SetPosition(glm::vec3(0.0f));
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
			glm::vec3(250.0f - (rand() % 500)),
			glm::vec3((float)(rand() % 15)));
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
			glm::vec3(250.0f - (rand() % 500)),
			glm::vec3((float)(rand() % 15)));
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
		GetInstance()->EnVec.at(i).SetMaxSpd(25.0f);
		GetInstance()->EnVec.at(i).SetAccSpd(0.25f);
		GetInstance()->EnVec.at(i).SetFriction(0.05f);
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
	glm::vec3 Vel = GetInstance()->PlayerMap["LocalPlayer"]->GetVelocity();
	float Velocity = abs(Vel.x + Vel.y + Vel.z);
	VelocityText.SetText("Velocity: " + to_string(Velocity));
}
