#version 330 core
in vec4 f_col;
in vec3 f_normal;
out vec4 color;

void main()
{
	color =f_col;// * 1.0 - (gl_FragCoord.y / 720);
}
