#include "Enemy.h"

void Enemy::MoveTo(glm::vec3 toPosition)
{
	MaxSpd = 0.25f;
	AccSpd = 0.015f;
	Friction = 0.003f;

	glm::vec3 Dir = glm::normalize(toPosition - Position);
	Velocity += Dir * glm::vec3(AccSpd, AccSpd, AccSpd);
	Velocity -= Dir * glm::vec3(Friction, Friction, Friction);
	Velocity = glm::clamp(Velocity, glm::vec3(-MaxSpd), glm::vec3(MaxSpd));

	//-----Acceleration
//	if (Position.x > toPosition.x) Velocity.x -= AccSpd;
//	if (Position.x < toPosition.x) Velocity.x += AccSpd;

//	if (Position.y > toPosition.y) Velocity.y -= AccSpd;
//	if (Position.y < toPosition.y) Velocity.y += AccSpd;

//	if (Position.z > toPosition.z) Velocity.z -= AccSpd;
//	if (Position.z < toPosition.z) Velocity.z += AccSpd;

	//-----Friction
	//if (Velocity.x > Friction) Velocity.x -= Friction;
	//if (Velocity.x < -Friction) Velocity.x += Friction;

	//if (Velocity.y > Friction) Velocity.y -= Friction;
	//if (Velocity.y < -Friction) Velocity.y += Friction;

	//if (Velocity.z > Friction) Velocity.z -= Friction;
	//if (Velocity.z < -Friction) Velocity.z += Friction;

	Position += Velocity;
}
