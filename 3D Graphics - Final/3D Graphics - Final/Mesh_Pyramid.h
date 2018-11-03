#pragma once
#include "Mesh.h"

class PyramidMesh : public Mesh
{
private:


public:
	//-----Con/Destructor
	PyramidMesh(const std::string& TextureFP, const std::string & ShaderFP);
	~PyramidMesh();
};