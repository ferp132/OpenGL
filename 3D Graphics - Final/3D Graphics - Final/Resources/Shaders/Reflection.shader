#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 v_TexCoord;

uniform mat4 u_MVP;
uniform mat4 model;

void main()
{
	gl_Position = u_MVP * position;
	fragPos = vec3(model * position);
	fragNormal = mat3(transpose(inverse(model))) * normal;
	v_TexCoord = texCoord;
};

//------------------------------------------------------------------------------------------//

#shader fragment
#version 330 core

//layout(location = 0) out vec4 color;

in vec3 fragPos;
in vec2 v_TexCoord;
in vec3 fragNormal;

out vec4 color;

uniform sampler2D	u_Texture;
uniform vec3		camPos;		// = vec3(0.0f, 0.0f, 2.0f);
uniform samplerCube skybox;


void main()
{
	vec3 norm = normalize(fragNormal);
	vec3 viewDir = normalize(fragPos - camPos);
	vec3 reflectDir = reflect(viewDir, norm);
	color = vec4(texture(skybox, reflectDir).rgb, 1.0f);
};