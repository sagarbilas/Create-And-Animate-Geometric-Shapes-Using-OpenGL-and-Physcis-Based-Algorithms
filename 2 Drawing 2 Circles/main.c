#include<windows.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>

char str1[20];
char str2[] ="-circles";
int flag=0;
float radius = 1.0;

void drawCircles(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.807, 0.0, 0.0);

    //DRAW THE FIRST CIRCLE
    glBegin(GL_POLYGON);
    float angle;
        for(int i=0; i<360; i++){
        angle = i * 3.1416/180;
        glVertex2f(1 + cos(angle)*radius, 1 + sin(angle)*radius);
      }
    glEnd();

    //DRAW THE SECOND CIRCLE
    glColor3f(0.807, 0.0, 0.0);
    glBegin(GL_POLYGON);
        for(int i=0; i<360; i++){
        angle = i * 3.1416/180;
        glVertex2f(8 + cos(angle)*radius, 8 + sin(angle)*radius);
      }
    glEnd();


    //SETTING OUTER BOUNDARY IF THE FIRST CIRCLE BLACK
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);

    for(int i=0; i<360; i++){
    angle = i * 3.1416/180;
    glVertex2f(1 + cos(angle)*radius, 1 + sin(angle)*radius);
    }
    glEnd();


    //SETTING OUTER BOUNDARY IF THE SECOND CIRCLE BLACK
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);

    for(int i=0; i<360; i++){
    angle = i * 3.1416/180;
    glVertex2f(8 + cos(angle)*radius, 8 + sin(angle)*radius);
    }
    glEnd();

 glFlush();
}

void init(void)
{
	glClearColor(0.870, 0.905, 0.937, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-20.0, 20.0, -20.0, 20.0);
}

int main(int argc, char* argv[])
{
    printf("\nEnter -circles to initiate the display:\n");
    gets(str1);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(350, 350);
	glutCreateWindow("Drawing 2 Circles ");

	init();
	//glutDisplayFunc(drawCircles);

    //to check whether the entered string is -circles or not. If it is circles, i shall allow opengl to start the visualization.
    if (strcmp(str1,str2) == 0)
    {
        flag=1;
    }
    if(flag==1)
    {
        glutDisplayFunc(drawCircles);
    }
    else
    {
        printf("\nYour entered string is not -quad!\n");
    }

	glutMainLoop();

	return 0;
}
