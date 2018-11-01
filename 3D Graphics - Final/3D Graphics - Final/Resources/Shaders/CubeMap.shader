#shader vertex
#version 450 core

layout(location = 0) in vec3 position;

out vec3 fragTexCoord;
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	fragTexCoord = position;
};

#shader fragment
#version 450 core

in vec3 fragTexCoord;
out vec4 color;

uniform samplerCube cubeSampler;

void main()
{
	color = texture(cubeSampler, fragTexCoord);
};