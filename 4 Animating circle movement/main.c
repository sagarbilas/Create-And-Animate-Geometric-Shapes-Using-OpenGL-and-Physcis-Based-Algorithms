#include <stdio.h>
#include <stdbool.h>
#include <GL/glut.h>
#include<math.h>
#include<windows.h>
#include<stdlib.h>
#define PI 3.14159265f

char str1[20];
char str2[] ="-anim";
int flag=0;

GLfloat radius = 0.2f;
GLfloat centerX1 = -1.2f;
GLfloat centerY1 = -1.2f;
GLfloat centerXMax1, centerXMin1, centerYMax1, centerYMin1;
GLfloat speedTowardX1 = 0.05f;     //ball's speed in x & y directions
GLfloat speedTowardY1 = 0.05f;

GLfloat centerX2 = -1.2f;
GLfloat centerY2= -1.2f;
GLfloat centerXMax2, centerXMin2, centerYMax2, centerYMin2;
GLfloat speedTowardX2 = 0.09f;
GLfloat speedTowardY2 = 0.02f;

int timeSinceStart = 0;
int refreshMillis = 25;

void initGL()
{
    glClearColor(0.870, 0.905, 0.937, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-2.5, 2.5, -2.5, 2.5);

    // MAXIMUM X & Y AXIS BOUNDARY FOR THE BALL'S CENTERS
    centerXMin1 =  -2.5;
    centerXMax1 = 2.5;
    centerYMin1 = -2.5;
    centerYMax1 = 2.5;

    centerXMin2 =  -2.5;
    centerXMax2 = 2.5;
    centerYMin2 = -2.5;
    centerYMax2 = 2.5;
}

void display()
{
    timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    //printf("timeSinceStart = %d milliseconds\n", timeSinceStart);

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(centerX1, centerY1, 0.0f);
    //printf("centerX1=%f, centerY1=%f\n\n", centerX1, centerY1);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    float angle;
    for(int i=0; i<360; i++)
    {
        angle = i * 3.1416/180;
        glVertex2f( cos(angle)*radius, sin(angle)*radius);
    }
    glEnd();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(centerX2, centerY2, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i++)
    {
        angle = i * 3.1416/180;
        glVertex2f( cos(angle)*radius, sin(angle)*radius);
    }
    glEnd();

    glutSwapBuffers();

    //CONTROLLING THE ANIMATION - CALCULATING THE LOCATION OF CIRCLES AFTER NEXT REFRESH HAPPENS
    centerX1 += speedTowardX1;
    centerY1 += speedTowardY1;

    //CHECK IF THE FIRST BALL HITS ANY RECTANGULAR BOUNDARY OR ELAPSED TIME CROSSES 25 MILLISECONDS LIMIT OT NOT
    if(centerX1 >= centerXMax1 || timeSinceStart%25==0)
    {
        centerX1 = -1.2f;
        centerY1 = -1.2f;
    }
    else if (centerX1 <= centerXMin1)
    {
        centerX1 = centerXMin1;
        speedTowardX1 = - speedTowardX1;
    }
    if (centerY1 >= centerYMax1 || timeSinceStart%25==0)
    {
        centerX1 = -1.2f;        //ball's center (x,y) position
        centerY1 = -1.2f;
    }
    else if (centerY1 <= centerYMin1)
    {
        centerY1 = centerYMin1;
        speedTowardY1 = - speedTowardY1;
    }

    centerX2 += speedTowardX2;
    centerY2 += speedTowardY2;

    //CHECK IF THE SECOND BALL HITS ANY RECTANGULAR BOUNDARY OR ELAPSED TIME CROSSES 25 MILLISECONDS LIMIT OT NOT
    if(centerX2 >= centerXMax2 || timeSinceStart%25==0)
    {
        centerX2 = -1.2f;
        centerY2 = -1.2f;
    }
    else if (centerX2 <= centerXMin2)
    {
        centerX2 = centerXMin2;
        speedTowardX2 = - speedTowardX2;
    }
    if (centerY2 >= centerYMax2 || timeSinceStart%25==0)
    {
        centerX2 = -1.2f;
        centerY2 = -1.2f;
    }
    else if (centerY2 <= centerYMin2)
    {
        centerY2 = centerYMin2;
        speedTowardY2 = - speedTowardY2;
    }
}

void Timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(refreshMillis, Timer, 0);
}

int main(int argc, char **argv)
{
    printf("\nEnter -anim to initiate the display:\n");
    gets(str1);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE );
    glutInitWindowSize( 540, 480 );
    glutInitWindowPosition(100, 100);
    glutCreateWindow( "Animating circle movement" );
    //glutDisplayFunc(display);

    //check whether the entered string is -circles or not. If it is circles, i shall allow opengl to start the visualization.
    if (strcmp(str1,str2) == 0)
    {
        flag=1;
    }
    if(flag==1)
    {
        glutDisplayFunc(display);
    }
    else
    {
        printf("\nYour entered string is not -anim!\n");
    }

    glutTimerFunc(0, Timer, 0);
    //glutTimerFunc(0, display, 0);
    initGL();
    glutMainLoop();
    return 0;
}
