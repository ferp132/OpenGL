#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 fragColor;

uniform float currentTime;

void main(void)
{
	vec3 movevec = position;
	movevec.x += (-0.5 + (sin(currentTime) * sin(currentTime))) * 4;
	movevec.y += sin(currentTime) * cos(currentTime)  * 4;

	movevec *= 0.3;

	gl_Position		= vec4(movevec, 1.0);
	fragColor		= color;
} 