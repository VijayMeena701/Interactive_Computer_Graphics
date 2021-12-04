/*
Instructions to run the code :
run  g++ transformation.cpp -lGL -lGLU -lglut
run ./a.out
Press the following keys to trigger the respective functions
'a':Translation
'b':rotation
'c': Scaling
'd':reflect
'e':shear
'r':to reset the window 
'f':to fullscreen and vice versa
'esc':to exit
*/

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <bits/stdc++.h>
#include <stdio.h>
#include <math.h>

using namespace std;

#define PI 3.1415926535
bool fullscreen = false;
int p = 0, q = 0, r = 0, s = 0, t = 0;
float slope;
int intercept;

int fillFlag = 0;

void edgedetect(float x1, float y1, float x2, float y2, int *le, int *re)
{
    float mx, x, temp;
    int i;
    if ((y2 - y1) < 0)
    {
        temp = y1;
        y1 = y2;
        y2 = temp;
        temp = x1;
        x1 = x2;
        x2 = temp;
    }

    if ((y2 - y1) != 0)
        mx = (x2 - x1) / (y2 - y1);
    else
        mx = x2 - x1;
    x = x1;

    for (i = y1; i <= y2; i++)
    {
        if (x < (float)le[i])
            le[i] = (int)x;

        if (x > (float)re[i])
            re[i] = (int)x;

        x += mx;
    }
}

void draw_pixel(int x, int y)
{
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void scanfill(float x1, float y1, float x2, float y2)
{
    int le[500], re[500];
    int i, y;

    for (i = 0; i < 500; i++)
    {
        le[i] = 500;
        re[i] = 0;
    }

    edgedetect(x1, y1, x2, y2, le, re);
    // edgedetect(x2, y2, x3, y3, le, re);
    // edgedetect(x3, y3, x4, y4, le, re);
    // edgedetect(x4, y4, x1, y1, le, re);

    for (y = 0; y < 500; y++)
    {
        for (i = (int)le[y]; i < (int)re[y]; i++)
            draw_pixel(i, y);
    }
}

void drawline(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void linedraw(int r, int theta)
{
    float x1 = 600, y1 = (600 * cos(theta) + r) / (sin(theta) * 1.0);
    float x2 = -600, y2 = (-600 * cos(theta) + r) / (sin(theta) * 1.0);
    glColor3f(.3, 1.0, 0.0);
    drawline(x1, y1, x2, y2);
}

void reflect_line(int x1, int y1, int x2, int y2)
{
    int x11, y11, x22, y22;

    x11 = (((1 - slope * slope) * x1) + (2 * slope * (y1 - intercept))) / (1 + slope * slope);
    y11 = (((slope * slope - 1) * y1) + (2 * slope * x1) + 2 * intercept) / (1 + slope * slope);
    x22 = (((1 - slope * slope) * x2) + (2 * slope * (y2 - intercept))) / (1 + slope * slope);
    y22 = (((slope * slope - 1) * y2) + (2 * slope * x2) + 2 * intercept) / (1 + slope * slope);

    // cout<<slope<<" "<<intercept<<endl;
    // cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
    // cout<<x11<<" "<<y11<<" "<<x22<<" "<<y22<<endl;
    glColor3f(0.3, 0.3, 1.0);
    drawline(x11, y11, x22, y22);
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //Axes
    glColor3f(0.0, 0.0, 1.0);
    drawline(0, -600, 0, 600);
    drawline(-600, 0, 600, 0);
    //drawing polygon
    glColor3f(1.0, 0.0, 1.0);
    glLineWidth(20);
    //K
    drawline(0, 0, 0, 200);
    drawline(0, 100, 100, 200);
    drawline(0, 100, 100, 0);
    //U
    drawline(100 + 20, 0, 100 + 20, 200);
    drawline(200 + 20, 0, 200 + 20, 200);
    drawline(100 + 20, 0, 200 + 20, 0);
    //M
    drawline(200 + 40, 0, 200 + 40, 200);
    drawline(200 + 40, 200, 250 + 40, 100);
    drawline(250 + 40, 100, 300 + 40, 200);
    drawline(300 + 40, 200, 300 + 40, 0);
    //Y
    drawline(300 + 60, 200, 350 + 60, 100);
    drawline(350 + 60, 100, 350 + 60, 0);
    drawline(350 + 60, 100, 400 + 60, 200);
    //Aribtarray line
    srand(time(0));
    int r = rand() % 100;
    int theta = rand() % 360;
    glLineWidth(4);
    linedraw(r, theta);
    //slope and intercept
    glLineWidth(20);
    slope = -1 * (cos(theta) / (sin(theta) * 1.0));
    intercept = r / (sin(theta) * 1.0);
    //reflecting along x*cos(theta)+y*sin(theta)=r;
    reflect_line(0, 0, 0, 200);
    reflect_line(0, 100, 100, 200);
    reflect_line(0, 100, 100, 0);
    //U
    reflect_line(100 + 20, 0, 100 + 20, 200);
    reflect_line(200 + 20, 0, 200 + 20, 200);
    reflect_line(100 + 20, 0, 200 + 20, 0);
    //M
    reflect_line(200 + 40, 0, 200 + 40, 200);
    reflect_line(200 + 40, 200, 250 + 40, 100);
    reflect_line(250 + 40, 100, 300 + 40, 200);
    reflect_line(300 + 40, 200, 300 + 40, 0);
    //Y
    reflect_line(300 + 60, 200, 350 + 60, 100);
    reflect_line(350 + 60, 100, 350 + 60, 0);
    reflect_line(350 + 60, 100, 400 + 60, 200);

    //filling
    glColor3f(0.1, 0.8, 1.0);
    scanfill(0, 0, 0, 200);
    scanfill(0, 100, 100, 200);
    scanfill(0, 100, 100, 0);
    //U
    scanfill(100 + 20, 0, 100 + 20, 200);
    scanfill(200 + 20, 0, 200 + 20, 200);
    scanfill(100 + 20, 0, 200 + 20, 0);
    //M
    scanfill(200 + 40, 0, 200 + 40, 200);
    scanfill(200 + 40, 200, 250 + 40, 100);
    scanfill(250 + 40, 100, 300 + 40, 200);
    scanfill(300 + 40, 200, 300 + 40, 0);
    //Y
    scanfill(300 + 60, 200, 350 + 60, 100);
    scanfill(350 + 60, 100, 350 + 60, 0);
    scanfill(350 + 60, 100, 400 + 60, 200);
    glFlush();
}

//keyboard event function
void keyboardEvent(unsigned char c, int x, int y)
{
    //transform();
    if (c == 27)
    {
        glutDestroyWindow(glutGetWindow());
    }
    else if (c == 'f')
    {
        fullscreen = !fullscreen;
        if (fullscreen)
        {
            glutFullScreen();
        }
        else
        {
            glutReshapeWindow(1200, 900);
            glutPositionWindow(0, 0);
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("KUMY");
    glViewport(0, 0, 600, 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-600.0, 600.0, -480.0, 480.0);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(Draw);
    glutKeyboardFunc(keyboardEvent);
    glFlush();
    glutMainLoop();
    return 0;
}