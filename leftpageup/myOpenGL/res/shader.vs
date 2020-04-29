#version 330 core
in vec3 aPos;   // 位置变量的属性位置值为 0 
in vec2 aTexCoord;

out vec2 TexCoord;
void main()
{
    gl_Position = vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}
