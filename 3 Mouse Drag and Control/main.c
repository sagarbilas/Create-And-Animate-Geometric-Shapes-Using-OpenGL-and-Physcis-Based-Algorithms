#include <stdio.h>
#include <stdbool.h>
#include <GL/glut.h>

int WindowWidth = 500, WindowHeight = 500;
bool drag_circle1 = false;
bool drag_circle2 = false;
float centre_x = 50.0, centre_y = 50.0, centre_x2=100, centre_y2=100, radius = 30.0;

char str1[20];
char str2[] ="-mouse";
int flag=0;

void mouseControlFunction( int button, int state, int click_x, int click_y )
{
    if( GLUT_DOWN == state )
    {
        //FOR THE FIRST CIRCLE
        float val1 = (click_x - centre_x) * (click_x - centre_x) + (click_y - centre_y) * (click_y - centre_y);
        float val2 = radius*radius;
        float valDiff = val2 - val1;

        //FOR THE SECOND CIRCLE
        float val3 = (click_x - centre_x2) * (click_x - centre_x2) + (click_y - centre_y2) * (click_y - centre_y2);
        float val4 = radius*radius;
        float valDiff2 = val3 - val4;

        //CHECKING WHETHER MOUSE IS DRAGGED IN THE FIRST CIRCLE OR NOT. IF YES, CHANGE THE CENTRE POSITION OF THE CIRCLE
        //TO WHERE MOUSE IS CLICKED
        if(val2 >= val1)
        {
            drag_circle1 = true;
            centre_x = click_x;
            centre_y =click_y;
            glutPostRedisplay();
        }
        //CHECKING WHETHER MOUSE IS DRAGGED IN THE SECOND CIRCLE OR NOT. IF YES, CHANGE THE CENTRE POSITION OF THE CIRCLE
        //TO WHERE MOUSE IS CLICKED
        else if(val4 >= val3)
        {
            drag_circle2 = true;
            centre_x2 = click_x;
            centre_y2 =click_y;
            glutPostRedisplay();
        }
    }
    else
    {
        drag_circle1 = false;
        drag_circle2 = false;
    }
}

void motion( int x, int y )
{
    //CHANGING THE CENTER OF THE FIRST CIRCLE TO WHERE MOUSE IS RELEASED
    if(drag_circle1)
    {
        centre_x = x;
        centre_y = y;
        glutPostRedisplay();
    }
    //CHANGING THE CENTER OF THE SECOND CIRCLE TO WHERE MOUSE IS RELEASED
    else if(drag_circle2)
    {
        centre_x2 = x;
        centre_y2 = y;
        glutPostRedisplay();
    }
}

void drawCircles()
{
    //DRAW THE FIRST CIRCLE
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    float angle;
    for(int i=0; i<360; i++)
    {
        angle = i * 3.1416/180;
        glVertex2f(centre_x + cos(angle)*radius, centre_y + sin(angle)*radius);
    }
    glEnd();
    glPopMatrix();

    //DRAW THE SECOND CIRCLE
    glPushMatrix();
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i++)
    {
        angle = i * 3.1416/180;
        glVertex2f(centre_x2 + cos(angle)*radius, centre_y2 + sin(angle)*radius);
    }
    glEnd();
    glPopMatrix();
}

void display()
{
    glClearColor( 0.870, 0.905, 0.937, 1 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, WindowWidth, WindowHeight, 0, -1, 1 );
    //gluOrtho2D(0.0,w,0.0,h);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    drawCircles();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    printf("\nEnter -mouse to initiate the display:\n");
    gets(str1);

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( WindowWidth, WindowHeight );
    glutCreateWindow( "Mouse Drag and Control" );
    //glutDisplayFunc( display );

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
        printf("\nYour entered string is not -mouse!\n");
    }

    glutMouseFunc( mouseControlFunction );
    glutMotionFunc( motion );
    glutMainLoop();
    return 0;
}
