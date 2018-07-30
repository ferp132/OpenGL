#version 450 core

in vec3 fragColor;

out vec4 color;

uniform float currentTime;

void main(void)
{
	vec3 colorTemp = fragColor;
	colorTemp.x += -0.25 + (0.25) *sin(currentTime);
	colorTemp.y += -0.25 + (0.25) *sin(currentTime);
	colorTemp.z += -0.25 + (0.25) *sin(currentTime);
	color = vec4(colorTemp, 1.0);
} 