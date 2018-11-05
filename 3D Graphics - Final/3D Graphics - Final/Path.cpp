#include "Path.h"
#include <vector>
#include <stdlib.h>

Path::Path()
{
	Radius = 10.0f;
}

Path::~Path()
{
}

void Path::AddPoint(glm::vec3 newPoint)
{
	PtVec.push_back(newPoint);
}

