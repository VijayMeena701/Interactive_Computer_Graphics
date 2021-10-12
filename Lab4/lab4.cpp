//g++ Assignment4-CED18I057.cpp -lGL -lGLU -lglut -lGLEW -o lab4
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

void changeViewPort(int w, int h)
{
    if (w >= h)
        glViewport(w / 2 - h / 2, 0, h, h);
    else
        glViewport(0, h / 2 - w / 2, w, w);
}

void myinit(void)
{
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 400, 0, 400);
    glMatrixMode(GL_MODELVIEW);
}
float detail = 20;

void plot(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void DDA(float p1[2], float p2[2])
{
    float x1 = p1[0], y1 = p1[1];
    float x2 = p2[0], y2 = p2[1];
    float dx = p2[0] - p1[0];
    float dy = p2[1] - p1[1];
    float m = dy / dx;
    float dist, inX, inY;

    if (abs(m) < 1)
        dist = abs(dx);
    else
        dist = abs(dy);

    inX = dx / dist; // if m<1 , inX is 1, else 1/m
    inY = dy / dist; // if m<1 , inY is m, else 1

    for (int i = 0; i < dist; i++)
    {
        plot(x1, y1);
        x1 += inX;
        y1 += inY;
    }
}

void fillTriangle(float p1[2], float p2[2], float p3[2])
{
    float x1 = p1[0], y1 = p1[1];
    float x2 = p2[0], y2 = p2[1];
    float x3 = p3[0], y3 = p3[1];
    float vertex[2] = {x3, y3};

    // DDA line drawing

    float dx = x2 - x1;
    float dy = y2 - y1;
    float m = dy / dx;
    float dist, inX, inY;

    if (abs(m) < 1)
        dist = abs(dx);
    else
        dist = abs(dy);

    inX = dx / dist; // if m<1 , inX is 1, else 1/m
    inY = dy / dist; // if m<1 , inY is m, else 1

    int i;
    float point[2] = {x1, y1};

    for (int i = 0; i < dist; i++)
    {
        DDA(vertex, point); //Drawing line from vertex to every point on line
        point[0] += inX;
        point[1] += inY;
    }
}

void hexagon()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    float c[2] = {50, 50}; //center of hexagon
    float r = 40;          //radius for polar co-ordinates
    float rotation = 30;   //rotation in degrees for drawing hexagon

    float p1[2] = {c[0] + r * (float)cos((rotation + 90) * M_PI / 180), c[1] + r * (float)sin((rotation + 90) * M_PI / 180)};     //p1 = x0 + rcos120,    y0 + rsin120
    float p2[2] = {c[0] + r * (float)cos((rotation + 30) * M_PI / 180), c[1] + r * (float)sin((rotation + 30) * M_PI / 180)};     //p2 = x0 + rcos60,     y0 + rsin60
    float p3[2] = {c[0] + r * (float)cos((rotation + -30) * M_PI / 180), c[1] + r * (float)sin((rotation + -30) * M_PI / 180)};   //p3 = x0 + rcos0,      y0 + rsin0
    float p4[2] = {c[0] + r * (float)cos((rotation + -90) * M_PI / 180), c[1] + r * (float)sin((rotation + -90) * M_PI / 180)};   //p4 = x0 + rcos-60,    y0 + rsin-60
    float p5[2] = {c[0] + r * (float)cos((rotation + -150) * M_PI / 180), c[1] + r * (float)sin((rotation + -150) * M_PI / 180)}; //p5 = x0 + rcos-120,   y0 + rsin-120
    float p6[2] = {c[0] + r * (float)cos((rotation + 150) * M_PI / 180), c[1] + r * (float)sin((rotation + 150) * M_PI / 180)};   //p6 = x0 + rcos-180,   y0 + rsin-180

    glPointSize(3);     //point Size
    glColor3f(0, 0, 0); //Black color for drawing lines

    //Drawing points
    DDA(p1, p2); //plotting line p1,p2
    DDA(p2, p3); //plotting line p2,p3
    DDA(p3, p4); //plotting line p3,p4
    DDA(p4, p5); //plotting line p4,p5
    DDA(p5, p6); //plotting line p5,p6
    DDA(p6, p1); //plotting line p6,p1
    glutSwapBuffers();
}

void house()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPointSize(3);

    //_____Square part of House_______

    float a[2] = {30, 10};
    float b[2] = {70, 10};
    float c[2] = {70, 50};
    float d[2] = {30, 50};

    //filling in color
    glColor3f(0.2, 0.2, 1); //Blue
    fillTriangle(a, b, c);
    fillTriangle(b, c, d);
    fillTriangle(c, d, a);
    fillTriangle(d, a, b);

    //outline of Square
    glColor3f(0, 0, 0); //black outline
    DDA(a, b);
    DDA(b, c);
    DDA(c, d);
    DDA(d, a);

    //_____Roof of House(Triangle)__________

    float e[2] = {50, 80}; //Vertex of top of house

    //filling in color
    glColor3f(1, 0.3, 0.3); //red

    fillTriangle(c, d, e);
    fillTriangle(d, e, c);
    fillTriangle(e, c, d);

    //Outline of Triangle
    glColor3f(0, 0, 0); //black outline
    DDA(c, d);
    DDA(d, e);
    DDA(e, c);

    //______DOOR of House(rectangle)_________

    float f[2] = {46, 10};
    float g[2] = {54, 10};
    float h[2] = {54, 30};
    float i[2] = {46, 30};

    //filling in color
    glColor3f(1, 1, 1); //white

    fillTriangle(f, g, h);
    fillTriangle(g, h, i);
    fillTriangle(h, i, f);
    fillTriangle(i, f, g);

    //outline of rectangle
    glColor3f(0, 0, 0); //black outline
    DDA(f, g);
    DDA(g, h);
    DDA(h, i);
    DDA(i, f);

    //______LEFT WINDOW__________

    float j[2] = {35, 25};
    float k[2] = {40, 25};
    float l[2] = {40, 30};
    float m[2] = {35, 30};

    //filling in color
    glColor3f(1, 1, 1); //white

    fillTriangle(j, k, l);
    fillTriangle(k, l, m);
    fillTriangle(l, m, j);
    fillTriangle(m, j, k);

    //outline
    glColor3f(0, 0, 0); //black outline
    DDA(j, k);
    DDA(k, l);
    DDA(l, m);
    DDA(m, j);

    //______RIGHT WINDOW__________

    float n[2] = {60, 25};
    float o[2] = {65, 25};
    float p[2] = {65, 30};
    float q[2] = {60, 30};

    //filling in color
    glColor3f(1, 1, 1); //white

    fillTriangle(n, o, p);
    fillTriangle(o, p, q);
    fillTriangle(p, q, n);
    fillTriangle(q, n, o);

    //outline
    glColor3f(0, 0, 0); //black outline
    DDA(n, o);
    DDA(o, p);
    DDA(p, q);
    DDA(q, n);

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(700, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Lab 4 - Hexagon - CED18I057");
    myinit();
    glutDisplayFunc(hexagon);
    glutCreateWindow("Lab 4 - House - CED18I057");
    myinit();
    glutDisplayFunc(house);
    glutReshapeFunc(changeViewPort);
    glutMainLoop();
}