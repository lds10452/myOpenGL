#version 330 core
in vec3 aPos;   // λ�ñ���������λ��ֵΪ 0 
in vec2 aTexCoord;

out vec2 TexCoord;
void main()
{
    gl_Position = vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}
