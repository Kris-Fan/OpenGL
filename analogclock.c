/**
OpenGL实现实时模拟系统时间的钟表
*/
#include "stdafx.h"
#include<gl/glut.h>
#include<math.h>
#include<Windows.h>
#include<time.h>
#define PI 3.14159
SYSTEMTIME timeNow;
int n=60,R=1;
int k=0;
float theta=0.0;
float hh,mm,ss;
int xc=0,yc=0;
float xh,yh;
float xm,ym;
float xs,ys;
void display(void);
void Reshape(int w, int h);
void myidle();
void init()
{
	GetLocalTime(&timeNow);
	ss=timeNow.wSecond;
	mm=timeNow.wMinute;
	hh=timeNow.wHour;
}
int _tmain(int argc, char**argv)
{
	glutInit(&argc,argv);    //初始化GLUT库；
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(300,300);
	glutCreateWindow("AnalogClock");
	init();
	glutDisplayFunc(display);  //注册回调函数，用于绘制当前窗口；
	
	glutIdleFunc(myidle);	//注册闲置回调函数
	glutReshapeFunc(Reshape);//注册窗口改变回调函数

	glutMainLoop();   //表示开始运行程序，用于程序的结尾；

	return 0;
}
/**回调函数
**/
void myidle()
{
	GetLocalTime(&timeNow);
	ss=timeNow.wSecond;
	theta+=1.0;
	if(theta>=360)theta-=360;
	Sleep(100);
	glutPostRedisplay();//重画，相当于调用display()
}
void display(void)
{
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//添加多边形模式设置语句观看效果（线框模式）	
   glLineWidth(2.0);  //设置线宽	
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//重回多边形填充模式

   glClearColor(1, 1, 1, 0);//设置白色绘图背景颜色(清屏颜色）
   glClear(GL_COLOR_BUFFER_BIT);  //刷新颜色缓冲区；

   glColor3f(0,0,0);
   glBegin(GL_POLYGON);	//绘制圆形
   for(int i=0;i<n;i++)
	   glVertex2f(R*cos(i*2*PI/n),R*sin(i*2*PI/n));
   glEnd();
   glBegin(GL_POLYGON);	
   for(int i=0;i<n;i++)
	   glVertex2f(1.03*R*cos(i*2*PI/n),1.03*R*sin(i*2*PI/n));
   glEnd();
   int lines = 60;
   for(int i=0;i<lines;i++)//表的刻度绘制
   {
	   if(i%5==0)
	   {
		   glLineWidth(5);
		   glBegin(GL_LINES);
		   glVertex2f(R*cos(i*2*PI/n),R*sin(i*2*PI/n));
		   glVertex2f((R-0.1)*cos(i*2*PI/n),(R-0.1)*sin(i*2*PI/n));
		   glEnd();
	   }else
	   {
		   glLineWidth(2);
		   glBegin(GL_LINES);
		   glVertex2f(R*cos(i*2*PI/n),R*sin(i*2*PI/n));
		   glVertex2f((R-0.03)*cos(i*2*PI/n),(R-0.03)*sin(i*2*PI/n));
		   glEnd();
	   }
   }
   /*绘制 秒、分、时针*/
   xs = xc + R * cos(PI / 2.0 - ss / 60 * 2 * PI);
   ys = yc + R * sin(PI / 2.0 - ss / 60 * 2 * PI);
   xm = xc + R * cos(PI / 2.0 - (mm + ss / 60.0) / 60.0*2.0*PI);	
   ym = yc + R * sin(PI / 2.0 - (mm + ss / 60.0) / 60.0*2.0*PI);	
   xh = xc + (R - 0.5)*cos(PI / 2.0 - (hh + (mm + ss / 60.0) / 60.0) / 12.0*2.0*PI);	
   yh = yc + (R - 0.5)*sin(PI / 2.0 - (hh + (mm + ss / 60.0) / 60.0) / 12.0*2.0*PI);
   glBegin(GL_LINES);
   glColor3f(1,0.1,0);
   glLineWidth(1.0);
	glVertex2f(xc,yc);
	glVertex2f(xs,ys);
   glEnd();
   glColor3f(1,1,0);
   glLineWidth(3.0);
   glBegin(GL_LINES);
	glVertex2f(xc,yc);
	glVertex2f(xm,ym);
   glEnd();
   glColor3f(0,1,1);
   glLineWidth(5.0);
   glBegin(GL_LINES);
	glVertex2f(xc,yc);
	glVertex2f(xh,yh);
   glEnd();

   glFlush(); 
}


void Reshape(GLsizei w,GLsizei h)
{
	glMatrixMode(GL_PROJECTION);//投影矩阵模式
	glLoadIdentity();	//矩阵栈清空
	gluOrtho2D(-1.5*R*w/h,1.5*R*w/h,-1.5*R,1.5*R);//设置裁剪窗口大小
	glViewport(0,0,w,h);//设置视区大小
	glMatrixMode(GL_MODELVIEW);//设置矩阵模式
}
