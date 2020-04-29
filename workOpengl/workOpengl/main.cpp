
#include<stdio.h>
#include <math.h>
//#include<windows.h>
//#include<glut.h>
#include <gl\freeglut.h>
#include <gl\glaux.h>
#define GL_PI 3.1415926
void init(void);
void drawGraphicsD(void);
void drawGraphicsH(void);
void drawGraphicsT(void);
void drawGraphicsVA(void);
void CALLBACK reshape(GLsizei w,GLsizei h);
void CALLBACK display(void);

void init(void)
{
}

void CALLBACK reshape(GLsizei w,GLsizei h)//�ص������������ڸı䴰�ڴ�Сʱ��ϵͳ���е���
	//����ע�⣡��GLsizeiΪ��ȷ���ͣ�����GLsize
{
	glViewport(0,0,w,h);//�ӿں�����ָ�����ӿڵ����½ǣ��ڵ�һ�����ڣ��ԣ�0,0��Ϊԭ�㣩λ��?
	glMatrixMode(GL_PROJECTION);//ָ����һ�������ǵ�ǰ����
	glLoadIdentity();//����ǰ�û�����ϵ��ԭ���Ƶ�����Ļ���ģ�������һ����λ����
}

void CALLBACK display(void)//�ص������������ڴ�������ʾͼ��ʱ��ϵͳ���ã��ڴ��ڴ�С�ı��ᱻ�Զ�����
{
	glShadeModel(GL_FLAT);
	glClearColor(0.0f,0.0f,0.0f,1.0f);//���������ݣ����ñ�����ɫ����RGBA���ִ�����ɫ��
	//����ͼ��ʱ������������͸��ͼ�Σ���Ϊ͸��Ч����ʾʱ��Ҫ��ͼ����ʾ������������
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//������壬�˲������������ɫ���壬color��ΪdepthΪ�����Ȼ���
	//drawGraphicsD();
	//drawGraphicsH( );
	//drawGraphicsT( );
	drawGraphicsVA();
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f(0.0f,1.0f,0.0f);
	GLfloat ver[9]={1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		-1.0f,0.0f,0.0f};
	glVertexPointer(3,GL_FLOAT,0,ver);
	glDrawArrays(GL_TRIANGLES,0,9);
	glFlush();//ǿ��ˢ�»��庯������֤ͼ�λ������ִ�ж����Ǵ洢�ڻ�����
}
void drawGraphicsVA(void)
{
	
}
void drawGraphicsH(void)
{
	bool color=false;
	glBegin(GL_TRIANGLE_FAN);//012,023,034
	     glColor3f(0.0f,0.6f,0.3f);
	     glVertex3f(0.0f, 0.0f, 0.0f);
	     for (GLfloat angle = 0.0f; angle <= (2 * GL_PI+GL_PI/8); angle += (GL_PI  / 8))
	     {
	          GLfloat x = 1.0f * sin(angle);
			  GLfloat y = 1.0f * cos(angle);
			  color = !color;

		   if(color)
			   glColor3f(1.0f, 0.0f, 0.0f);
		   else
			   glColor3f(0.0f,0.6f,0.3f);
			  glVertex3f(x, y, 0.0f);
	     }
   glEnd();
}
void drawGraphicsD(void)
{
	glBegin(GL_TRIANGLE_STRIP);  //012,123,234
	//ʹ�ú�ɫ���Ƶ�һ��������  
	glColor3f(1.0f,0.0f,0.0f);  
	glVertex3f(0.0f,0.0f,0.0f);  
	glVertex3f(0.5f,0.0f,0.0f);  
	glVertex3f(0.5f,0.5f,0.0f);  
	//ʹ����ɫ���Ƶڶ���������  
	glColor3f(0.0f,1.0f,0.0f);  
	glVertex3f(1.0f,0.5f,0.0f);  
	//ʹ����ɫ���Ƶ�����������  
	glColor3f(0.0f,0.0f,1.0f);  
	glVertex3f(1.0f,1.0f,0.0f);  
	//����GL_TRIANGLE_STRIP����������  
	glEnd();  
}
void drawGraphicsT(void)
{
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS); // ����������
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(-1.0f/2, 1.0f/2, 0.0f); // ����
	glVertex3f( 1.0f/2, 1.0f/2, 0.0f); // ����
	glColor3f(0.5f,0.3f,0.6f);
	glVertex3f( 1.0f/2,-1.0f/2, 0.0f); // ����
	glVertex3f(-1.0f/2,-1.0f/2, 0.0f); // ��
	glEnd(); // �����λ��ƽ���
}
void main(void)
{
	auxInitDisplayMode(AUX_SINGLE|AUX_RGBA);//glaux������������ʾģʽ��single�������壬һ�����ھ�̬���ƣ�RGBA��ʾ������͸����ɫ��ģʽ
	
	auxInitPosition(0,0,500,500);//glaux���������ô���λ�úʹ�С��ǰ��λ�����½�����ʱ���Ͻǵ�λ�ã�����λ�����ڵĿ�͸�

	auxInitWindow("LDSopenGL");//glaux�������������ڣ���������Ϊ���ڵ�����
	
	init();

	auxReshapeFunc(reshape);//ע��ص�������ʹ֮�ܱ�ϵͳ����
	auxMainLoop(display);//ע��ص�������ʹ֮�ܱ�ϵͳ����
}
