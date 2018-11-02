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

uniform vec4		u_Color;
uniform sampler2D	u_Texture;
//-----Ambient
uniform float		ambientStr = 0.5f;
uniform vec3		ambientColor = vec3(1.0f, 1.0f, 1.0f);
//-----Diffuse
uniform vec3		lightColor = vec3(1.0f, 1.0f, 2.0f);
uniform vec3		lightPos = vec3(-100.0f, -500.0f, 100.0f);
//-----Specular
uniform vec3		camPos;		// = vec3(0.0f, 0.0f, 2.0f);
uniform float		lightSpecStr = 10.0f;
uniform float		shininess = 32.0f;

void main()
{
	//-----Ambient
	vec3 ambient = ambientStr * ambientColor;

	//-----Light Direction
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(fragPos - lightPos);

	//-----Diffuse Coloring
	float diffuseStr = max(dot(norm, -lightDir), 0.0f);
	vec3 diffuse = diffuseStr * lightColor;

	//-----Specular Highlight
	vec3 negViewDir = normalize(camPos - fragPos);
	vec3 reflectDir = reflect(lightDir, norm);
	float spec = pow(max(dot(negViewDir, reflectDir), 0.0f), shininess);
	vec3 specular = lightSpecStr * spec * lightColor;

	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor * vec4(ambient + diffuse + specular, 1.0f);
};