#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define RADIUS 25
#define NSEGMENTS 100
#define PI 3.1415926535
int numCircles, count=0;
int XMax[50], XMin[50], YMax[50], YMin[50] ;

int timeSinceStart[50];

float color1[150], color2[150], color3[150];
float centerX[100], centerY[100];
float speedX[100];
float speedY[100];

float waitTime;

void display(void);
void drawCircle(float, float, float);

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    waitTime = 25;

    //SETTING INITIAL POSITION OF THE CIRCLE RANDOMLY.AND CREATING SOME RANDOM COLORS
    for (int i = 0; i < numCircles*2; i+=2)
    {
        color1[i] = (double)rand() / (double)RAND_MAX;
        color2[i] = (double)rand() / (double)RAND_MAX;
        color3[i] = (double)rand() / (double)RAND_MAX;

        centerX[i] =  (rand() % 500);
        centerY[i] =  (rand() % 500);

        //speedX[i] = 1.5;
        //speedY[i] = 1.5;
        speedX[i] = (double)rand() / (double)RAND_MAX*2;
        speedY[i] = (double)rand() / (double)RAND_MAX*2;
    }
    glutPostRedisplay();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < numCircles*2; i+=2)
    {
        glColor3f(color1[i], color2[i], color3[i]);
        //glColor3f(1.0, 0.0, 0.0);
        drawCircle(centerX[i], centerY[i], RADIUS);
    }
    glFlush();
}


void drawCircle(float x, float y, float radius)
{
    GLfloat phi, x1, y1;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(int j = 0; j <= NSEGMENTS; j++)
    {
        phi = j * 2 * PI/NSEGMENTS;
        x1 = x + radius * cos(phi);
        y1 = y + radius * sin(phi);
        glVertex2f(x1, y1);
    }
    glEnd();
}

//CALCULATES THE BALL POSITION AND ADJUST THE POSITION IF ANY RECTANGULAR BOUNDARY IS HIT

void timerFunc(int value)
{
    for(int i = 0; i < numCircles*2; i+=2)
    {
        float x1, x2, y1, y2;
        x1 = centerX[i];
        y1 = centerY[i];

        //int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);

        if(x1 > (WIDTH - RADIUS) || x1 < (WIDTH + RADIUS) )
            centerX[i] = x1 + speedX[i];
        if(y1 > (HEIGHT - RADIUS) || y1 < (HEIGHT + RADIUS))
            centerY[i] = y1 + speedY[i];
        //if(centerX[i] >= (WIDTH - RADIUS) || centerX[i] <= 0 || centerY[i] >= (HEIGHT - RADIUS) || centerY[i] <= 0 || timeSinceStart%25==0)
        if(centerX[i] >= (WIDTH - RADIUS) || centerX[i] <= 0 || centerY[i] >= (HEIGHT - RADIUS) || centerY[i] <= 0)
        {
            centerX[i] =  (rand() % 500);
            centerY[i] =  (rand() % 500);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(waitTime, timerFunc, 0);
}


int main(int argc, char *argv[])
{
    numCircles = 50;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Animating circle movement- 50 circles moving around");
    glutDisplayFunc(display);
    glutTimerFunc(waitTime, timerFunc, 1);

    init();

    glutMainLoop();
}
