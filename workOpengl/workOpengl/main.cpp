
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

void CALLBACK reshape(GLsizei w,GLsizei h)//回调函数，用于在改变窗口大小时由系统自行调用
	//！！注意！！GLsizei为正确类型！而非GLsize
{
	glViewport(0,0,w,h);//视口函数，指定了视口的左下角（在第一象限内，以（0,0）为原点）位置?
	glMatrixMode(GL_PROJECTION);//指定哪一个矩阵是当前矩阵
	glLoadIdentity();//将当前用户坐标系的原点移到了屏幕中心，类似于一个复位操作
}

void CALLBACK display(void)//回调函数，用于在窗口内显示图像时由系统调用，在窗口大小改变后会被自动调用
{
	glShadeModel(GL_FLAT);
	glClearColor(0.0f,0.0f,0.0f,1.0f);//清理窗口内容，设置背景颜色。由RGBA数字代表颜色；
	//绘制图形时尽量避免设置透明图形，因为透明效果显示时需要对图像显示层数进行排序
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//清除缓冲，此参数代表清除颜色缓冲，color改为depth为清除深度缓冲
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
	glFlush();//强制刷新缓冲函数，保证图形绘制命令被执行而不是存储在缓冲区
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
	//使用红色绘制第一个三角形  
	glColor3f(1.0f,0.0f,0.0f);  
	glVertex3f(0.0f,0.0f,0.0f);  
	glVertex3f(0.5f,0.0f,0.0f);  
	glVertex3f(0.5f,0.5f,0.0f);  
	//使用绿色绘制第二个三角形  
	glColor3f(0.0f,1.0f,0.0f);  
	glVertex3f(1.0f,0.5f,0.0f);  
	//使用蓝色绘制第三个三角形  
	glColor3f(0.0f,0.0f,1.0f);  
	glVertex3f(1.0f,1.0f,0.0f);  
	//结束GL_TRIANGLE_STRIP绘制三角形  
	glEnd();  
}
void drawGraphicsT(void)
{
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS); // 绘制正方形
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(-1.0f/2, 1.0f/2, 0.0f); // 左上
	glVertex3f( 1.0f/2, 1.0f/2, 0.0f); // 右上
	glColor3f(0.5f,0.3f,0.6f);
	glVertex3f( 1.0f/2,-1.0f/2, 0.0f); // 左下
	glVertex3f(-1.0f/2,-1.0f/2, 0.0f); // 右
	glEnd(); // 正方形绘制结束
}
void main(void)
{
	auxInitDisplayMode(AUX_SINGLE|AUX_RGBA);//glaux函数：设置显示模式，single代表单缓冲，一般用于静态绘制，RGBA表示红绿蓝透明度色彩模式
	
	auxInitPosition(0,0,500,500);//glaux函数：设置窗口位置和大小，前两位代表新建窗口时左上角的位置，后两位代表窗口的宽和高

	auxInitWindow("LDSopenGL");//glaux函数：创建窗口，函数参数为窗口的名字
	
	init();

	auxReshapeFunc(reshape);//注册回调函数，使之能被系统调用
	auxMainLoop(display);//注册回调函数，使之能被系统调用
}
