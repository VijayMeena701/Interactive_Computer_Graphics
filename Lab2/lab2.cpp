// g++ Assignment2-CED18I057.cpp -lGL -lGLU -lglut -lGLEW -o lab2

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

void myinit(void)
{
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_COLOR,GL_ONE_MINUS_SRC_COLOR);
    // glCullFace(GL_BACK);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}

void House()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
    //glEnable(GL_BLEND);
    //housePoints
    glColor3f(0.2, 0.2, 1); //blue

    glVertex2f(30, 10);
    glVertex2f(70, 10);
    glVertex2f(70, 50);
    glVertex2f(30, 50);

    //door
    glColor3f(1, 1, 1); //white

    glVertex2f(54, 10);
    glVertex2f(54, 30);
    glVertex2f(46, 30);
    glVertex2f(46, 10);

    //right window
    glVertex2f(60, 30);
    glVertex2f(65, 30);
    glVertex2f(65, 25);
    glVertex2f(60, 25);

    //left window
    glVertex2f(40, 30);
    glVertex2f(40, 25);
    glVertex2f(35, 25);
    glVertex2f(35, 30);

    //roof
    glColor3f(1, 0.3, 0.3); //red

    glVertex2f(70, 50);
    glVertex2f(50, 80);
    glVertex2f(30, 50);
    glVertex2f(70, 50);

    // glVertex2f();
    // glVertex2f();
    // glVertex2f();
    // glVertex2f();
    glEnd();

    //OUTLINE CO-ORDINATE REPEAT
    glLineWidth(5);

    glBegin(GL_LINE_LOOP); // house outline
    glColor3f(0, 0, 0);    //black

    glVertex2f(30, 10);
    glVertex2f(70, 10);
    glVertex2f(70, 50);
    glVertex2f(30, 50);

    glEnd();

    glBegin(GL_LINE_LOOP); //door outline
    glVertex2f(54, 10);
    glVertex2f(54, 30);
    glVertex2f(46, 30);
    glVertex2f(46, 10);

    glEnd();
    glBegin(GL_LINE_LOOP); //right window outline
    glVertex2f(60, 30);
    glVertex2f(65, 30);
    glVertex2f(65, 25);
    glVertex2f(60, 25);

    glEnd();
    glBegin(GL_LINE_LOOP); //left window outline
    glVertex2f(40, 30);
    glVertex2f(40, 25);
    glVertex2f(35, 25);
    glVertex2f(35, 30);

    glEnd();
    glBegin(GL_LINE_LOOP); //Roof outline
    glVertex2f(70, 50);
    glVertex2f(50, 80);
    glVertex2f(30, 50);

    glEnd();

    glFlush();
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

    struct Circle
    {
        float x;
        float y;
        float r;
        float ry;
    };

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

    glBegin(GL_POLYGON); // Front Wheel outline
    glColor3f(0, 0, 0);
    for (float i = 0; i <= 3600; i++) //iterate through radians
    {
        glVertex2f(25 + 10.5 * cos(i), 40 + 10.5 * sin(i)); //plotting x+r*cosA,y+r*sinA
    }
    glEnd();

    glBegin(GL_POLYGON);      // Front Wheel
    glColor3f(0.7, 0.7, 0.7); // grey

    for (float i = 0; i <= M_PI * 2; i += 0.001) //iterate through radians
    {
        glVertex2f(25 + 10 * cos(i), 40 + 10 * sin(i)); //plotting x+r*cosA,y+r*sinA
    }
    glEnd();

    //Rear WHEEL

    glBegin(GL_POLYGON); // Rear Wheel outline
    glColor3f(0, 0, 0);
    for (float i = 0; i <= 3600; i++) //iterate through radians
    {
        glVertex2f(65 + 10.5 * cos(i), 40 + 10.5 * sin(i)); //plotting x+r*cosA,y+r*sinA
    }
    glEnd();

    glBegin(GL_POLYGON);      // Rear Wheel
    glColor3f(0.7, 0.7, 0.7); // grey

    for (float i = 0; i <= 3600; i++) //iterate through radians
    {
        glVertex2f(65 + 10 * cos(i), 40 + 10 * sin(i)); //plotting x+r*cosA,y+r*sinA
    }
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("LAB2. HOUSE - CED18I057");
    myinit();
    glutDisplayFunc(House);
    glutCreateWindow("LAB2. CAR - CED18I057");
    myinit();
    glutDisplayFunc(Car);
    glutMainLoop();
}
