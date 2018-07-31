#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 fragColor;

uniform float currentTime;

void main(void)
{
	float i = sin(currentTime);
	vec3 movevec = position;

	movevec.x += -0.5 + sin(currentTime) * sin(currentTime);
	movevec.y += sin(currentTime) * cos(currentTime);

	//movevec.x = movevec.x * cos(i) - movevec.y * sin(i);
	//movevec.y = movevec.x * sin(i) + movevec.y * cos(i);

	gl_Position		= vec4(movevec, 1.0);

	fragColor	= color;

	fragColor.r += sin(currentTime) * cos(currentTime);
	fragColor.g -= sin(currentTime) * cos(currentTime);
	fragColor.b += sin(currentTime) * sin(currentTime);



} 