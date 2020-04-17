#version 330 core
layout (location = 0) in vec2 v_pos;
layout (location = 1) in vec2 v_uv;

out vec2 f_uv;

void main()
{
	gl_Position = vec4(v_pos.x, v_pos.y, 0.0, 1.0);
	f_uv = v_uv;
}
