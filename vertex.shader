#version 330 core

in layout(location = 0) vec3 position;
in layout(location = 1) vec2 uv;
in layout(location = 2) vec3 normal;

uniform mat4 pr_matrix = mat4(1.0f);
uniform mat4 vw_matrix = mat4(1.0f);
uniform mat4 tr_matrix = mat4(1.0f);
uniform mat4 rt_matrix = mat4(1.0f);
uniform mat4 sc_matrix = mat4(1.0f);

out vec3 _position;
out vec2 _uv;
out vec3 _normal;

void main()
{

	mat4 ml_matrix = tr_matrix * rt_matrix * sc_matrix;
	gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(position, 1);

	// Wonder why this works for the normal but not the position
	_position = vec3(ml_matrix * vec4(position, 1));
	_uv = uv;
	// Jamie says you can get away with using 3 dimensions for rotation matrices, but not others
	_normal = normalize(mat3(rt_matrix) * normal);
}