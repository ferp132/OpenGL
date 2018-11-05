#pragma once
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include <vector>

class Path 
{
private:
	std::vector<glm::vec3> PtVec;

	float Radius;
public:
	Path();
	~Path();

	void AddPoint(glm::vec3 newPoint);

	std::vector<glm::vec3>* GetPtVec() { return &PtVec; }
	float GetRadius() { return Radius; }

};