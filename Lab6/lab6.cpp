//g++ lab6.cpp -lGL -lGLU -lglut -lGLEW -o lab6

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

void myinit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 100.0, 0.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

struct circle
{
    float center[2];
    float radius;
};

void plot(float x, float y)
{
    glBegin(GL_POINTS);
    glColor3f(0, 0, 0);
    glVertex2f(round(x), round(y));
    glEnd();
}

void mirrorAllOctants(float center[2], float x, float y)
{
    plot(center[0] + y, center[1] + x); //O1
    plot(center[0] + x, center[1] + y); //O2
    plot(center[0] - x, center[1] + y); //O3
    plot(center[0] - y, center[1] + x); //O4
    plot(center[0] - y, center[1] - x); //O5
    plot(center[0] - x, center[1] - y); //O6
    plot(center[0] + x, center[1] - y); //O7
    plot(center[0] + y, center[1] - x); //O8
}

void Midpoint_Circle_Drawing(circle cir)
{
    float x = 0;
    float y = cir.radius;
    float p = 1 - cir.radius;           //initial decision parameter p0
    int x_limit = cir.radius / sqrt(2); //breaking point for 1st quadrant

    for (int i = 0; i < x_limit + 1; i++)
    {
        glPointSize(5);
        mirrorAllOctants(cir.center, x, y);
        if (p < 0) //y does not change
            p += 2 * x + 3;
        else //y decrement
        {
            p += 2 * x - 2 * y + 5;
            y--;
        }
        x++;
    }
}

void Car()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(5);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP); //Car body

    glVertex2f(5, 40);
    glVertex2f(80, 40);
    glVertex2f(80, 60);
    glVertex2f(5, 60);

    glEnd();

    glBegin(GL_LINE_STRIP); // Car Roof
    glVertex2f(25, 60);
    glVertex2f(41, 81);
    glVertex2f(69, 81);
    glVertex2f(80, 60);
    glEnd();

    glBegin(GL_LINE_LOOP); // Front Window
    glVertex2f(27, 61);
    glVertex2f(41, 79);
    glVertex2f(50, 79);
    glVertex2f(50, 61);
    glEnd();

    glBegin(GL_LINE_LOOP); //Rear Window
    glVertex2f(51, 61);
    glVertex2f(51, 79);
    glVertex2f(69, 79);
    glVertex2f(78, 61);
    glEnd();

    // WHEEL CENTERS : Front (25,40) , Rear (65,40) , radius 10

    // FRONT WHEEL
    circle cir = {{25, 40}, 10};
    Midpoint_Circle_Drawing(cir);

    //Rear WHEEL
    circle cirl = {{65, 40}, 10};
    Midpoint_Circle_Drawing(cirl);
    glFlush();
}

int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(1000, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Lab 6 - MCD - CED18I057");
    myinit();
    glutDisplayFunc(Car);
    glutMainLoop();
}