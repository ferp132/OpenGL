#include "Mesh.h"

Mesh::Mesh(const std::string & TextureFP, const std::string & ShaderFP)
{

}

Mesh::~Mesh()
{
}

void Mesh::Render(glm::mat4 MVP, glm::mat4 Model, glm::vec3 CamPos)
{
	//-----Shader Bind & Set Uniforms
	Shad.Bind();
	Shad.setUniformMat4f("u_MVP", MVP);
	Shad.setUniformMat4f("model", Model);
	Shad.setUniform3f("camPos", CamPos.x, CamPos.y, CamPos.z);

	VAO.Bind();
	Tex.Bind(GL_TEXTURE_2D);
	GLCall(glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr));
	VAO.Unbind();
	Tex.Unbind(GL_TEXTURE_2D);
	Shad.Unbind();
}
