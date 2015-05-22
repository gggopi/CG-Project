/*
CG PROJECT

BASIC OPENGL FUNCTIONS

BY
S.GOPINATH      12IT64
S.VINAY KUMAR   12IT66
SHAMBU KUMAR    12IT72

        INSTRUCTIONS FOR THE USER

        Run the file (We used CODEBLOCKS to run this)
        Observe the objects getting translated and rotated.. the pyramid also gets scaled when it reaches the edge of the screen
        Press 'SPACE' to pause/resume the animation
        Press 'l' to see new objects which has lighting effects
        Press 'LEFT MOUSE BUTTON' to bring the objects at their starting point, i.e., on the y-axis
        Press 'ESC' to exit



        FUNCTIONS ACHIEVED

        3D transformations
        Keyboard functions
        Mouse functions
        Lighting effects
*/


//#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>

void init()
{

    glClearColor(1.0f,1.0f,0.0f,0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);

    //glLoadIdentity();
}

int sign=1;
float sx=0.1,sy=0.1, sz=0.1;
int angle = 5.0;
float rx=1,ry=1,rz=1;

float tx=0.2,ty=0.0,tz=0;

bool pause=true;



int ch=1;


void translate()                                //TRANSLATION USING
                                                //Matrix Multiplication
{
    float A[16]={1,0,0,0,0,1,0,0,0,0,1,0,sign*tx,ty,tz,1};
    glMultMatrixf(A);
    //glPopMatrix();
}

void disp()
{
init();
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//glEnable(GL_CULL_FACE);
glEnable(GL_DEPTH_TEST);

if(ch==1){
glLoadIdentity();
glPushMatrix();
//glTranslatef(sign*tx,ty,tz);
translate();
glRotatef(angle,0,1,0);
glBegin(GL_TRIANGLES);
glColor3f(0,0,0);
glVertex3f(-0.1,-0.4,0);
glColor3f(0.2,0.2,0.2);
glVertex3f(-0.4,-0.7,0);
glColor3f(0.9,0.9,0.9);
glVertex3f(0.2,-0.6,0);
glColor3f(0,0,0);
glEnd();
glPopMatrix();

glPushMatrix();
glTranslatef(sign*tx,ty,tz);
glRotatef(angle,2,3,1);
//glScalef(0.5,0.5,0.5);
glScalef(sx,sy,sz);

//glVertex2f(-0.1,0.0);
//glVertex2f(0.0,0.1);
//glVertex2f(0.1,0.0);
glBegin(GL_TRIANGLES);
glColor4f(1,0,0, 1);
glVertex3f(1,0,0);
glVertex3f(0,1,0);
glVertex3f(0,0,1);

glColor4f(0,1,0, 1);
glVertex3f(0,0,1);glVertex3f(0,0,0);glVertex3f(0,1,0);

glColor4f(0,0,1,1);
glVertex3f(0,1,0);glVertex3f(0,0,0);glVertex3f(1,0,0);

glColor4f(1,0,1,1);
glVertex3f(1,0,0);glVertex3f(0,0,0);glVertex3f(0,0,1);
glEnd();
glPopMatrix();

    glPushMatrix();
    glTranslatef(tx,0.5,0.0);
    glRotatef(angle,0,1,1);
    glColor3f(0.3,0.6,0.4);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
    glutWireSphere(0.3,30,30);
    glPopMatrix();
/*
    glTranslatef(0.4,-0.8,0.0);
    glutSolidCube(0.5);

*/
glutSwapBuffers();

    //glFlush();
}
else
{  glPushMatrix();
    glTranslatef(tx,0.5,0.0);
    glRotatef(angle,0,1,1);
    glColor3f(0.2,0.2,0.2);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glutSolidCube(0.3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx,-0.5,0.0);
    glRotatef(angle,0,1,1);
    glutWireTeapot(0.4);
    glPopMatrix();
    glutSwapBuffers();
}
}


void update(int v)
{
    if(pause)
    {
        angle+=2.0;
        tx+=0.01;
        if(angle>360)
            angle-=360;
        if(tx>0.9)
        {
            tx-=1.9;
            sign*=-1;
            sx+=0.1;
            sy+=0.1;
            sz+=0.1;
            if(sx>3)
                sx=sy=sz=0;
        }
//        if(angle%3==0)
//        rx++;
//        else
//        if(angle%3==1)
//            ry++;
//        else
//            rz++;
        v++;
    }
    glutPostRedisplay();
    if(v>5000000) return ;				 // so that animation stop after some time, i.e. aftr 125000 seconds..
    glutTimerFunc(25,update,v);
    return ;

}

void mouse1(int button, int state, int x, int y )
{
    if(button==GLUT_LEFT_BUTTON)
    {

        tx=ty=tz=0;
    }
    glutPostRedisplay();
}

void keys(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27 : exit(0);
        case 'l' : ch=0;
                        break;
        case ' ' : pause=(!pause); break;

        default : printf("\ndont press the keys unnecessarily!!");
    }
    glutPostRedisplay();
}
int main(int argv, char **argc)
{
    glutInit(&argv,argc);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
    glutInitWindowPosition(500,0);
    glutInitWindowSize(500,500);
    //init();
    glutCreateWindow("CG PROJECT");
    //rx=ry=rz=1;
    glutDisplayFunc(disp);
    glutTimerFunc(20,update,0);
    glutMouseFunc(mouse1);
    glutKeyboardFunc(keys);
    glutMainLoop();
    return 0;


}
