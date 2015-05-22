//#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
const float xmin=20,xmax=80,ymin=20,ymax=80;			// clippin boundary
float cx1,cx2,cy1,cy2;
void init()
{

    glClearColor(1.0f,1.0f,0.0f,0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,100,0,100);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);

    //glLoadIdentity();
}

void LC()
{

    float m=(cy2-cy1)/(cx2-cx1);
	float xc=cy2-m*cx2;
float len1,len2; 	
float x1,y1,x2,y2;
x1=cx1;
x2=cx2;
y1=cy1;
y2=cy2;
	printf("m=%f\n",m);
    float tmp;
    len1=sqrt((cy2-cy1)*(cy2-cy1)+(cx2-cx1)*(cx2-cx1));
Lbl:

        if(cx1<xmin)
        {
            cx1=xmin;
            
		cy1=m*cx1+xc;

        }
        if(cx2>xmax)
        {
            cx2=xmax;
            cy2=m*cx2+xc;
        }

        if(cy1<ymin)
        {
            cy1=ymin;
            cx1=(cy1-xc)/m;
        }
        if(cy2>ymax)
        {
            cy2=ymax;
            cx2=(cy2-xc)/m;
        }
	printf("\n%f %f %f %f \n",cx1,cy1,cx2,cy2);
	len2=sqrt((cy2-cy1)*(cy2-cy1)+(cx2-cx1)*(cx2-cx1));        
	if(!(len2<len1)&&(x1==cx1||x2==cx2||y1==cy1||y2==cy2))
        {
 tmp=cx1;
        cx1=cx2;
        cx2=tmp;
        tmp=cy1;
        cy1=cy2;
        cy2=tmp;

goto Lbl;
}
        glutPostRedisplay();

}

void disp()
{
    init();
    glClear(GL_COLOR_BUFFER_BIT);



    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex2f(cx1,cy1);
    glVertex2f(cx2,cy2);
    glEnd();
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmin,ymax);
    glVertex2f(xmax,ymax);
    glVertex2f(xmax,ymin);
    glEnd();
    
    glFlush();



}

int main(int argv, char **argc)
{
    glutInit(&argv,argc);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(500,0);
    glutInitWindowSize(500,500);
    
    glutCreateWindow("Line clipping");
  
    printf("boundary of the Clipping rectangle:\n ");
    printf("xmin=%f, xmax=%f, ymin=%f, ymax=%f\n",xmin, ymin, xmax, ymax);		//globally instialized.. constant values..
    printf("enter the coordinates x1,y1,x2,y2: \n ");
    scanf("%f%f%f%f",&cx1,&cy1,&cx2,&cy2);

    // cx1=30; cy1=30; cx2=50; cy2=10;			// some hard coded values..
    // cx1=10; cy1=30; cx2=70; cy2=50;
    LC();    						// comment it to avoid clipping..

    glutDisplayFunc(disp);
    glutMainLoop();
    return 0;


}
