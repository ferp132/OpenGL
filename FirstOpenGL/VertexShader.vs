#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 TexCoord;

out vec3 fragColor;
out vec2 fragTexCoord;

uniform float currentTime;
uniform float Rotation;

void main(void)
{
	float i = Rotation;
	
	vec3 movevec = position;
	vec3 RotVec;

	if(color == 0.0f)
	{
		movevec.x += -0.5 + sin(currentTime) * sin(currentTime);
		movevec.y += sin(currentTime) * cos(currentTime);
		
			fragTexCoord = TexCoord;
	}
	else
	{
		RotVec.x = movevec.x * cos(i) - movevec.y * sin(i);
		RotVec.y = movevec.x * sin(i) + movevec.y * cos(i);
		RotVec.z = movevec.z;
		movevec = RotVec;
		

		movevec.x -= -0.5 + sin(currentTime) * sin(currentTime);
		movevec.y -= sin(currentTime) * cos(currentTime);

			fragColor	= color;
	}

	gl_Position		= vec4(movevec, 1.0);



} 