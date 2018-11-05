#include "Mesh.h"
#include "GameManager.h"

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
	if (Reflect) Shad.setUniform1i("skybox", GameManager::GetInstance()->GetSkyBox()->GetTextureID());

	VAO.Bind();
	if(Reflect) Tex.Bind(GL_TEXTURE_CUBE_MAP);
	else Tex.Bind(GL_TEXTURE_2D);
	GLCall(glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr));
	VAO.Unbind();
	if (Reflect) Tex.Unbind(GL_TEXTURE_CUBE_MAP);
	else Tex.Unbind(GL_TEXTURE_2D);
	Shad.Unbind();
}
