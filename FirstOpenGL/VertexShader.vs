#version 450 core

void main(void)
{
	const vec3 vertices[] = vec3[](vec3( 0.0, 0.5, 0.0),
							vec3( 0.5, 0.0, 0.0),
							vec3(-0.5, 0.0, 0.0));
	gl_Position = vec4(vertices[gl_VertexID], 1.0);
} 