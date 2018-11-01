#shader vertex
#version 450 core

layout(location = 0) in vec4 vertex;


out vec2 fragTexCoord;

uniform mat4 proj;


void main()
{
	gl_Position = proj * vec4(vertex.xy, 0.0, 1.0);
	fragTexCoord = vertex.zw;
};

#shader fragment
#version 450 core

in vec2 fragTexCoord;
out vec4 color;

uniform vec3 textColor;
uniform sampler2D u_tex;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_tex, fragTexCoord).r);
	color = vec4(textColor, 1.0) * sampled;
	//color = vec4(1.0f, 1.0f, 1.0f, 1.0f) * texture(u_tex, fragTexCoord);
};