#version 330 core
layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec4 v_col;
layout(location = 2) in vec2 v_uv;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

out vec4 f_col;

void main()
{
	f_col = v_col; //+ vec4(v_uv, 0.0, 0.0);
	gl_Position = proj_matrix * view_matrix * model_matrix * vec4(v_pos, 1.0);
}
