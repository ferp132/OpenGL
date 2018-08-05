#version 450 core

in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 color;

uniform float currentTime;
uniform sampler2D RaymanTex;
uniform sampler2D AwesomeDTex;

void main(void)
{
	vec3 colorTemp = fragColor;
	float MixValue = 0.25 + sin(currentTime);
	if(MixValue > 1.0f) MixValue = 1.0f;
	else if (MixValue < 0.0f) MixValue = 0.0f;


	
	if(fragColor == 0.0f)
	{
		color = mix(texture(RaymanTex, fragTexCoord), texture(AwesomeDTex, fragTexCoord), MixValue);
	}
	else
	{
		colorTemp.r += sin(currentTime) * cos(currentTime);
		colorTemp.g -= sin(currentTime) * cos(currentTime);
		colorTemp.b += sin(currentTime) * sin(currentTime);
		colorTemp += -0.25 + (0.25) * sin(currentTime) * cos(currentTime);

		color = vec4(colorTemp, 1.0);
	}


} 