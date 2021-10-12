//g++ Assignment3-CED18I057.cpp -lGL -lGLU -lglut -lGLEW -o lab3
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

void changeViewPort(int w, int h) // to always have the viewport in the centre of the window in SQUARE SHAPE
{
    if (w >= h)
        glViewport(w / 2 - h / 2, 0, h, h);
    else
        glViewport(0, h / 2 - w / 2, w, w);
}

void init(void)
{
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 100, 0, 100);
}

struct Ellipse
{
    float x;
    float y;
    float rx;
    float ry;
};

int flag = 1;

void drawEllipse(Ellipse outer, Ellipse inner, float startAngle, float endAngle)
//draws a specified ellipse in CLOCKWISE direction
// works only in between glBegin() ___ glEnd()
{
    int flag = 0;
    if (startAngle < endAngle)
    {
        for (float i = startAngle; i <= endAngle; i += 0.001)
        {
            if (flag == 0)
            {
                glVertex2f(outer.x + outer.rx * cos(i), outer.y + outer.ry * sin(i));
                flag = 1;
            }
            else
            {
                glVertex2f(inner.x + inner.rx * cos(i), inner.y + inner.ry * sin(i));
                flag = 0;
            }
        }
    }
}

float randColor()
{
    float r = (float)((rand() % 10)) / 9;
    return r;
}

void letters(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    //________Letter I_________________

    glBegin(GL_QUADS); //  I
    glColor3f(randColor(), randColor(), randColor());
    //base
    glVertex2f(10, 50);
    glVertex2f(30, 50);
    glVertex2f(30, 54);
    glVertex2f(10, 54);
    //vertical part
    glVertex2f(22, 52);
    glVertex2f(22, 78);
    glVertex2f(18, 78);
    glVertex2f(18, 52);
    //top
    glVertex2f(10, 80);
    glVertex2f(10, 76);
    glVertex2f(30, 76);
    glVertex2f(30, 80);
    glEnd();

    //_____Letter C_____________________________

    Ellipse outerC = {50, 65, 10, 15}; //ellipse for C
    Ellipse innerC = {52, 65, 6, 11};  //ellipse for c

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(randColor(), randColor(), randColor());
    drawEllipse(outerC, innerC, M_PI * 0.2, M_PI * 1.8);
    glEnd();

    //_____Letter G ______________________________

    Ellipse outerG = {80, 65, 10, 15}; //ellipse for semicircle of G
    Ellipse innerG = {82, 65, 6, 11};  //ellipse for semicircle of G

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(randColor(), randColor(), randColor());
    drawEllipse(outerG, innerG, M_PI * 0.2, M_PI * 1.8);
    glEnd();

    //horizontal part of G
    glBegin(GL_POLYGON);
    glVertex2f(80, 65);
    glVertex2f(80, 61);
    glVertex2f(88, 61);
    glVertex2f(88, 65);
    glEnd();
    // Vertical part
    glBegin(GL_POLYGON);
    glVertex2f(88, 61);
    glVertex2f(88, 56.5);
    glVertex2f(83, 54);
    glVertex2f(83, 61);
    glEnd();

    //__________Number 5_____________

    glBegin(GL_QUADS);
    glColor3f(randColor(), randColor(), randColor());

    //horizontal
    glVertex2f(45 - 6.65, 40);
    glVertex2f(25 - 6.65, 40);
    glVertex2f(25 - 6.65, 36);
    glVertex2f(45 - 6.65, 36);
    //vertical
    glVertex2f(25 - 6.65, 36);
    glVertex2f(29 - 6.65, 36);
    glVertex2f(29 - 6.65, 26);
    glVertex2f(25 - 6.65, 25);
    glEnd();

    //curvy bit
    Ellipse outer5 = {25, 18, 15, 12};
    Ellipse inner5 = {25, 18, 11, 8};

    glBegin(GL_TRIANGLE_STRIP);

    drawEllipse(outer5, inner5, -M_PI * 0.65, M_PI * 0.65);
    glEnd();

    //___________Number 7_______________

    glBegin(GL_POLYGON);
    glColor3f(randColor(), randColor(), randColor());
    glVertex2f(47, 40);
    glVertex2f(65, 40);
    glVertex2f(65, 36);
    glVertex2f(47, 36);
    glEnd();

    //curvy bit
    Ellipse outer7 = {65, 6, 9, 32};
    Ellipse inner7 = {65, 6, 6, 28};

    glBegin(GL_TRIANGLE_STRIP);

    drawEllipse(outer7, inner7, M_PI * 0.5, M_PI * 0.95);
    glEnd();

    glFlush();
}

// void timer(int)
// {
//     glutPostRedisplay();
//     glutTimerFunc(100, timer, 0); //10 fps
// }

int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);                       //initialize glut
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //Display Mode
    glutInitWindowPosition(700, 100);            //Top-right
    glutInitWindowSize(800, 800);                //width and Height
    glutCreateWindow("Lab 3 - ICG CED57");       //Window name
    init();
    glutReshapeFunc(changeViewPort);
    glutDisplayFunc(letters);
    // glutTimerFunc(0, timer, 0);
    glutMainLoop(); //Loop
}