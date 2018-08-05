#version 450 core

in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 color;

uniform float currentTime;
uniform sampler2D RaymanTex;
uniform sampler2D AwesomeDTex;
uniform float Rotation;

void main(void)
{
	float i = Rotation/2;

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
		colorTemp.r += sin(i) * cos(i);
		colorTemp.g -= sin(i) * cos(i);
		colorTemp.b += sin(i) * sin(i);
		colorTemp += -0.25 + (0.25) * sin(i) * cos(i);

		color = vec4(colorTemp, 1.0);
	}


} 