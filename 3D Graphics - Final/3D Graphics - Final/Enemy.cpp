#include "Enemy.h"
#include "GameManager.h"
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>


void Enemy::MoveTo(glm::vec3 toPosition, int newmovetype, Path initPath)
{
	DesPos = toPosition;
	movetype = newmovetype;
	path = initPath;

	switch (movetype)
	{
	case SEEK:
	{
		GameManager::GetInstance()->GetEnVec()->at(0).SetScale(glm::vec3(5.0f));
		Seek();
		break;
	}
	case ARRIVE:
	{
		DesPos.x = (ID / 10) * Scale.x * 3;
		DesPos.y = (ID % 10) * Scale.y * 3;
		DesPos.z = 0.0f;

		GameManager::GetInstance()->GetEnVec()->at(0).SetScale(glm::vec3(5.0f));
		Arrive();
		break;
	}
	case WANDER:
	{
		GameManager::GetInstance()->GetEnVec()->at(0).SetScale(glm::vec3(5.0f));
		Wander();
		break;
	}
	case PATH:
	{
		GameManager::GetInstance()->GetEnVec()->at(0).SetScale(glm::vec3(5.0f));
		//PathFollow();
		break;
	}
	case FOLLOW:
	{
		GameManager::GetInstance()->GetEnVec()->at(0).SetScale(glm::vec3(10.0f));
		Follow(GameManager::GetInstance()->GetEnVec()->at(0).GetCenter());
		break;
	}
	case QUEUE:
	{
		GameManager::GetInstance()->GetEnVec()->at(0).SetScale(glm::vec3(10.0f));
		Queue();
		break;
	}
	}

	if(GameManager::GetInstance()->GetCon())Containment();
	if (GameManager::GetInstance()->GetSep())Separate();
	if (GameManager::GetInstance()->GetAvoid())Avoid();
}

void Enemy::Seek()
{
		glm::vec3 Desired = glm::normalize(DesPos - Center);
		Desired *= glm::vec3(MaxSpd);
		glm::vec3 Steer = Desired - Velocity;
		Steer = glm::clamp(Steer, glm::vec3(-AccSpd), glm::vec3(AccSpd));


	Acceleration += Steer;
}

void Enemy::Arrive()
{


	glm::vec3 Desired = DesPos - Position;
	float Dis = glm::length(Desired);

	Desired = glm::normalize(Desired);

	if (Dis < 10.0f)
	{
		float M = map(Dis, 0, 10, 0, MaxSpd);
		Desired *= M;
	}
	else Desired *= MaxSpd;

	glm::vec3 Steer = Desired - Velocity;
	Steer = glm::clamp(Steer, -AccSpd, AccSpd);

	Acceleration += Steer;
}

void Enemy::Wander()
{
	glm::vec3 WanderDir = glm::normalize(glm::vec3(500 - rand() % 1000, 500 - rand() % 1000, 500 - rand() % 1000));
	glm::vec3 WanderSA = WanderDir * WanRad;
	glm::vec3 WanderPoint = Position + Velocity * 10.0f + WanderSA;

	DesPos = WanderPoint;
	Seek();
}

void Enemy::Containment()
{
	if (Position.x > ConRad)	Acceleration.x = -MaxSpd;
	else if (Position.x < -ConRad)	Acceleration.x = MaxSpd;

	if (Position.y > ConRad)	Acceleration.y = -MaxSpd;
	else if (Position.y < -ConRad)	Acceleration.y = MaxSpd;

	if (Position.z > ConRad)	Acceleration.z = -MaxSpd;
	else if (Position.z < -ConRad)	Acceleration.z = MaxSpd;

	Acceleration = glm::clamp(Acceleration, -AccSpd, AccSpd);

}

void Enemy::Separate()
{
	std::vector<Enemy>* EnVec = GameManager::GetInstance()->GetEnVec();

	float DesSep = Scale.x * 1.25;
	glm::vec3 Sum;
	int count = 0;

	for (int i = 0; i < EnVec->size(); i++)
	{
		float Dis = glm::distance(Center, EnVec->at(i).GetCenter());
		if (Dis > 0 && Dis < DesSep)
		{
			glm::vec3 Diff = Center - EnVec->at(i).GetCenter();
			Diff = glm::normalize(Diff);
			Diff /= Dis;
			Sum += Diff;
			count++;
		}
	}
	if (count > 0)
	{
		Sum /= count;
		Sum = glm::normalize(Sum);
		Sum *= MaxSpd;

		Acceleration = glm::clamp(Sum, -AccSpd, AccSpd);
	}

}

void Enemy::Avoid()
{
	std::vector<Object>* ObVec = GameManager::GetInstance()->GetObVec();

	
	glm::vec3 Sum;
	int count = 0;

	for (int i = 0; i < ObVec->size(); i++)
	{
		float DesSep = ObVec->at(i).GetScale().x * 2;

		float Dis = glm::distance(Center, ObVec->at(i).GetCenter());
		if (Dis > 0 && Dis < DesSep)
		{
			glm::vec3 Diff = Center - ObVec->at(i).GetCenter();
			Diff = glm::normalize(Diff);
			Diff /= Dis;
			Sum += Diff;
			count++;
		}
	}
	if (count > 0)
	{
		Sum /= count;
		Sum = glm::normalize(Sum);
		Sum *= MaxSpd;

		Acceleration = glm::clamp(Sum, -AccSpd*2, AccSpd*2);
	}
}

void Enemy::PathFollow()
{
	//Predict the location that the Enemy is moving to
	if(Velocity == glm::vec3(0.0f)) Wander();
	glm::vec3 Predict = Velocity;

	Predict = glm::normalize(Predict);
	Predict *= 25.0f;

	glm::vec3 PredictPoint = Center + Predict;
	
	//-----Find NormalPoint
	glm::vec3 A = path.GetPtVec()->at(0);				//A points from the start of the path to the Predicted location
	glm::vec3 B = path.GetPtVec()->at(1);							//B points from the start of the path to the end of the path

	//the distance from the start of the path to Scalar projection of The predicted point is |A| * cos(theta), 
	//theta is the angle between A and B
	B = glm::normalize(B);
	B *= glm::dot(A, B);

	glm::vec3 NormalPoint = A + B;							//The Scalar Projection of A to the predicted point

//	if (NormalPoint.x < A.x || NormalPoint.x > B.x) NormalPoint = B;

	float Dis = glm::distance(PredictPoint, NormalPoint);	//How far the Predicted Location is from the center


	if (Dis > path.GetRadius()) 
	{
		B = glm::normalize(B);
		B *= 10;
		DesPos = NormalPoint + B;
		Seek();
	}
	

}

void Enemy::Follow(glm::vec3 LeaderPos)
{
	if (Center == LeaderPos)
	{
		Wander();
	}
	else
	{
		DesPos = LeaderPos;
		Seek();
	}
}

void Enemy::Queue()
{
	if (Center == GameManager::GetInstance()->GetEnVec()->at(0).GetCenter())
	{
		Wander();

		/*

		Using this code has an interesting effect.
		The leader of the queue will try and follow the last member of the queue.
		On observation it seems like the enemies following the leader do not like him to follow others and they will "push" the leader away from his desired location


		DesPos = GameManager::GetInstance()->GetEnVec()->back().GetCenter();
		Arrive();

		*/
	}
	else
	{
		DesPos = GameManager::GetInstance()->GetEnVec()->at(ID-1).GetCenter();
		//Seek();	//Arrive works much better for this code
		Arrive();
	}
}
