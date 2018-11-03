#pragma once
#include "Mesh.h"

class CubeMesh : public Mesh
{
private:


public:
	//-----Con/Destructor
	CubeMesh(const std::string& TextureFP, const std::string & ShaderFP);
	~CubeMesh();
};