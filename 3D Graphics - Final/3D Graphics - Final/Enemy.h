#pragma once
#include "Object.h"
#include "Path.h"

class Enemy : public Object
{
	enum MoveType {SEEK, ARRIVE, WANDER, PATH, FOLLOW, QUEUE};
private:
	glm::vec3 DesPos;					//Desired Position
	int movetype;
	float WanRad;						//Wander Circle Radius
	float ConRad;						//Containment Radius, MAximum allowed distance from Origin



	Path path;
	int ID;

public:
	void MoveTo(glm::vec3 toPosition, int newmovetype, Path initPath);
	void Seek();
	void Arrive();
	void Wander();
	void Containment();
	void Separate();
	void Avoid();
	void PathFollow();
	void Follow(glm::vec3 LeaderPos);
	void Queue();

	//-----Setter
	void SetMoveType(int newMoveType) { movetype = newMoveType; }
	void SetDesPos(glm::vec3 newPos) { DesPos = newPos; }
	void SetWanRad(float newRad) { WanRad = newRad; }
	void SetConRad(float newRad) { ConRad = newRad; }



	void SetID(int newID) { ID = newID; }
};