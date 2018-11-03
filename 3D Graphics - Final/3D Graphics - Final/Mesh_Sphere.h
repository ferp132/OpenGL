#pragma once
#include "Mesh.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

class SphereMesh : public Mesh
{
private:


public:
	//-----Con/Destructor
	SphereMesh(const std::string& TextureFP, const std::string & ShaderFP);
	~SphereMesh();
};