#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600
#define RADIUS 8
#define NSEGMENTS 100
#define PI 3.1415926535

int numCircles, count=0, XMax[50], XMin[50], YMax[50], YMin[50] ;
float color1[150], color2[150], color3[150], centerX[100], centerY[100], waitTime, AGENTSIZE = RADIUS*2, d_h = RADIUS*2*4, vx[100], vy[100], vx_goal[100], vy_goal[100];
float fps = 0, fps_avg = 0, f_avoid_x = 0, f_avoid_y = 0, f_avoid_ctr = 0, f_goal_x, f_goal_y;
//float TIME_STEP = 25;
//float TIME_STEP = 0.42;
float TIME_STEP = 1.2;
float MAX_SPEED = 1.99;
//float MAX_FORCE = 0.05;
float MAX_FORCE = 0.07;
float zeta = 1.0023;
int initial_time = 0, final_time, frame_count=0, lastTime=0, frames = 0, totalTime = 0, updateTime = 0, updateFrames =0, interacting_agents_cntr = 0, timeSinceStart[50];

void display(void);
void drawCircle(float, float, float);
void introscreen();

float max(float num1, float num2)
{
    return (num1 > num2 ) ? num1 : num2;
}

void init(void)
{
    lastTime = glutGet(GLUT_ELAPSED_TIME);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    waitTime = 25;

    //SETTING INITIAL POSITION OF THE CIRCLE RANDOMLY.AND CREATING SOME RANDOM COLORS
    for (int i = 0; i < numCircles*2; i+=2)
    {
        color1[i] = (double)rand() / (double)RAND_MAX;
        color2[i] = (double)rand() / (double)RAND_MAX;
        color3[i] = (double)rand() / (double)RAND_MAX;

        centerX[i] =  (rand() % 500);
        centerY[i] =  (rand() % 500);

        //vx[i] = 1.5;
        //vy[i] = 1.5;
        vx[i] = (double)rand() / (double)RAND_MAX*2;
        vy[i] = (double)rand() / (double)RAND_MAX*2;

        vx_goal[i] = (double)rand() / (double)RAND_MAX*2;
        vy_goal[i] = (double)rand() / (double)RAND_MAX*2;

        //printf("vx[%d]= %.3f, vy[%d]= %.3f\n", i, vx[i], i, vy[i]);
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

    char fps_result[50], fps_avg_result[50];

    int now =  glutGet(GLUT_ELAPSED_TIME);
    int delta = now - lastTime;
    lastTime = now;
    totalTime+=delta;
    frames++;
    updateTime+=delta;
    updateFrames++;
    if(updateTime > 1000)
    {
        fps = 1000*frames/totalTime;
        fps_avg = 1000*updateFrames/updateTime;

       // printf("fps = %.2f fps_avg = %.2f\n\n", fps, fps_avg);

        updateTime = 0;
        updateFrames =0;
    }
    sprintf(fps_result, "FPS: %.2f,     FPS_AVG: %.2f", fps, fps_avg);
    drawBitmapText(fps_result,50,0);

    glLoadIdentity();
    //drawBitmapText("Displaying text in opengl",50,0);
    //drawBitmapText(result,50,0);
    glutSwapBuffers();
    glFlush();
}

void drawBitmapText(char *string,float x,float y)
{
    char *c;
    glRasterPos2f(x,y);

    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
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
            centerX[i] = x1 + vx[i];
        if(y1 > (HEIGHT - RADIUS) || y1 < (HEIGHT + RADIUS))
            centerY[i] = y1 + vy[i];
        //if(centerX[i] >= (WIDTH - RADIUS) || centerX[i] <= 0 || centerY[i] >= (HEIGHT - RADIUS) || centerY[i] <= 0 || timeSinceStart%25==0)
        if(centerX[i] >= (WIDTH - RADIUS) || centerX[i] <= 0 || centerY[i] >= (HEIGHT - RADIUS) || centerY[i] <= 0)
        {
            centerX[i] =  (rand() % 500);
            centerY[i] =  (rand() % 500);
        }

        //f_goal_x[i] = (vx_goal[i] - vx[i]) / zeta;
        //f_goal_y[i] = (vy_goal[i] - vy[i]) / zeta;
        f_goal_x = (vx_goal[i] - vx[i]) / zeta;
        f_goal_y = (vy_goal[i] - vy[i]) / zeta;

        // CIRCLE TO CIRCLE COLLISION DETECTION
        for(int j=0; j< numCircles*2; j+=2)
        {
            if(i==j)
                continue;
            else
            {
                float distanceBtwnCenters = sqrt(((centerX[i] - centerX[j])*(centerX[i] - centerX[j])) + ((centerY[i] - centerY[j])*(centerY[i] - centerY[j])));
                //printf("distance between circle[%d] & circle[%d] = %.3f\n", i, j, distanceBtwnCenters);
                /*
                if(distanceBtwnCenters <= 30)
                    //drawCircle(centerX[j], centerY[j], RADIUS);
                    centerX[i] = centerX[i] - vx[i];
                    //centerY[i] = centerY[i] - vy[i];
                */
                if(distanceBtwnCenters > 0 && distanceBtwnCenters < d_h)
                {
                    float d_ab = max(distanceBtwnCenters-AGENTSIZE,0.001);
                    // why did I choose 0.0001
                    float k = max(d_h - d_ab, 0);
                    float x_ab = (centerX[i] - centerX[j])/distanceBtwnCenters;
                    float y_ab = (centerY[i] - centerY[j])/distanceBtwnCenters;
                    interacting_agents_cntr +=1;
                    f_avoid_x += k * x_ab / d_ab;
                    f_avoid_y += k * y_ab / d_ab;
                    f_avoid_ctr = f_avoid_ctr+1;
                }
            }
        }

        if(f_avoid_ctr > 0 )
        {
            f_avoid_x = f_avoid_x / f_avoid_ctr;
            f_avoid_y = f_avoid_y / f_avoid_ctr;
        }

        float force_sum_x = f_goal_x + f_avoid_x;
        float force_sum_y = f_goal_y + f_avoid_y;
        float f_avoid_mag = sqrt(force_sum_x*force_sum_x + force_sum_y*force_sum_y);

        if(f_avoid_mag > MAX_FORCE )
        {
            force_sum_x = MAX_FORCE* force_sum_x/ f_avoid_mag ;
            force_sum_y = MAX_FORCE* force_sum_y / f_avoid_mag ;
        }
        vx[i] += TIME_STEP * force_sum_x;
        vy[i] += TIME_STEP * force_sum_y;
        float speed = sqrt(vx[i]*vx[i] + vy[i]*vy[i]);

        if(speed > MAX_SPEED)
        {
            vx[i] = MAX_SPEED * vx[i] / speed  ;
            vy[i] = MAX_SPEED * vy[i] / speed;
        }
        // centerX[i] += TIME_STEP* vx[i];
        // centerY[i] += TIME_STEP* vy[i];


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
    glutCreateWindow("Calculating Frames Per Second");
    glutDisplayFunc(display);
    glutTimerFunc(waitTime, timerFunc, 1);

    init();

    glutMainLoop();
}
