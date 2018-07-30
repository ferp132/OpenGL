#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 fragColor;

uniform float currentTime;

void main(void)
{
	float i = sin(currentTime);
	vec3 movevec = position;
	vec3 movevec2 = position;
	//movevec.x += -0.5 + sin(currentTime) * sin(currentTime);
	//movevec.y += sin(currentTime) * cos(currentTime);



	movevec2.x = (movevec2.x * cos(i)) - (movevec2.y * sin(i));
	movevec2.y = (movevec2.y * cos(i)) + (movevec2.x * sin(i));

	movevec += movevec2;






	gl_Position		= vec4(movevec, 1.0);
	fragColor		= color;
} 