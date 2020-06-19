#include <GL/gl.h>
#include <GL/glut.h>

char str1[20];
char str2[] ="-quad";
int flag=0;

void drawQuad(void)
{
    glClearColor(0.870, 0.905, 0.937, 0.0);
    glClear (GL_COLOR_BUFFER_BIT);

    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    //DRAW THE RECTANGLE
    glColor3f (0.807, 0.0, 0.0);
    glVertex2f(0.20f, 0.6f);
    glVertex2f(0.7f, 0.6f);
    glVertex2f(0.7f, 0.2f);
    glVertex2f(0.20f, 0.2f);
    glEnd();

    glLineWidth(2);
    //SETTING THE COLOR OF THE EDGES AS BLACK
    glBegin(GL_LINES);
    glColor3f (0.0, 0.0, 0.0);
    glVertex2f(0.20f, 0.6f);
    glVertex2f(0.7f, 0.6f);

    glColor3f (0.0, 0.0, 0.0);
    glVertex2f(0.7f, 0.6f);
    glVertex2f(0.7f, 0.2f);

    glColor3f (0.0, 0.0, 0.0);
    glVertex2f(0.7f, 0.2f);
    glVertex2f(0.20f, 0.2f);

    glColor3f (0.0, 0.0, 0.0);
    glVertex2f(0.20f, 0.2f);
    glVertex2f(0.20f, 0.6f);

    glEnd();

    glFlush ();
}

void init (void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -10.0, 10.0);
}


int main(int argc, char** argv)
{
    printf("\nEnter -quad to initiate the display:\n");
    gets(str1);

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (350, 350);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Drawing a Quad");
    init ();

    //to check whether the entered string is -circles or not. If it is circles, i shall allow opengl to start the visualization.
    if (strcmp(str1,str2) == 0)
    {
        flag=1;
    }
    if(flag==1)
    {
        glutDisplayFunc(drawQuad);
    }
    else
    {
        printf("\nYour entered string is not -quad!\n");
    }

   // glutDisplayFunc(drawQuad);
    glutMainLoop();
    return 0;
}
