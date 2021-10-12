//g++ lab7.cpp -lGL -lGLU -lglut -lGLEW -o lab7

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

// Structure for Ellipse
struct ellipse
{
    float c[2];
    float a, b;
};

//Structure for Ellpitical Arc
struct ellipticalArc
{
    float c[2];
    float a, b, alpha, beta;
};

void changeViewPort(int w, int h)
{
    if (w >= h)
        glViewport(w / 2 - h / 2, 0, h, h);
    else
        glViewport(0, h / 2 - w / 2, w, w);
}

void myinit(void)
{
    glClearColor(0.1, 0.11, 0.12, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void draw(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(round(x), round(y));
    glEnd();
}

void illuminateAllQuadrants(float c[2], float x, float y)
{
    draw(c[0] + x, c[1] + y); //Q1
    draw(c[0] - x, c[1] + y); //Q2
    draw(c[0] - x, c[1] - y); //Q3
    draw(c[0] + x, c[1] - y); //Q4
}

// =============== General Ellipse Drawing ===============================

void generalEllipseDrawing(ellipse ell)
{
    float a = ell.a, b = ell.b;
    float x = 0;
    float y = b;
    float a2 = a * a, b2 = b * b;
    glColor3f(1, 1, 1);
    while (y >= 0)
    {
        illuminateAllQuadrants(ell.c, x, y);
        x++;
        y = sqrt((a2 - x * x) * b2 / a2);
    }
}

// =============== End of General Ellipse Drawing ========================

// =============== Parametric Ellipse Drawing ============================

void parametricEllipseDrawing(ellipse ell)
{
    glColor3f(1, 1, 1);
    for (float i = 0; i <= 2 * M_PI; i += 0.001)
        draw(ell.c[0] + ell.a * cos(i), ell.c[1] + ell.b * sin(i));
}

// =============== End of Parametric Ellipse Drawing =====================

// =============== Midpoint Ellipse Drawing ==============================

void midPointEllipseDrawing(ellipse ell)
{
    float a = ell.a; //length of axis along x
    float b = ell.b; //length of axis along y
    float x = 0;
    float y = b;
    float a2 = a * a, b2 = b * b;

    float p = round(b2 + a2 * 0.25 - a2 * b);

    float breakpoint = round(a2 / sqrt(a2 + b2));

    for (int i = 0; x <= breakpoint; i++) //wider part of ellipse where we iterate over x
    {
        illuminateAllQuadrants(ell.c, x, y);
        if (p < 0) //y does not change
            p += 2 * b2 * (x + 1) + b2;
        else //y decrement
        {
            y--;
            p += 2 * b2 * (x + 1) + b2 - 2 * a2 * (y - 1);
        }
        x++;
    }

    for (int i = 0; y >= 0; i++) //vertical part of ellipse where we iterate y
    {
        illuminateAllQuadrants(ell.c, x, y);
        if (p > 0)
        {
            p += a2 * (1 - 2 * y); //decision parameter for vertical part
        }
        else
        {
            p += a2 * (1 - 2 * y) + 2 * b2 * (x + 1);
            x++;
        }
        y--;
    }
}

// =============== End of Midpoint Ellipse Drawing ==============================

// ============== Arc Drawing ===================================================

int quadrantCheck(float x, float y, float alpha, float beta)
{
    float lowerAngle, upperAngle;

    float pointAngle = (180 / M_PI) * atan2(y, x);
    if (pointAngle < 0)
        pointAngle += 360; //making atan2 range from 0 to 2PI

    if (alpha >= 0 && beta >= 0)
    {
        lowerAngle = alpha;
        upperAngle = alpha + beta;
        if (upperAngle > 360)
        {
            upperAngle -= 360;
            if (pointAngle >= lowerAngle || pointAngle <= upperAngle)
                return 1;
            else
                return 0;
        }
        else
        {
            if (pointAngle >= lowerAngle && pointAngle <= upperAngle)
                return 1;
            else
                return 0;
        }
    }
    else if (alpha < 0 && beta > 0)
    {
        lowerAngle = alpha + 360; //making it positive
        upperAngle = lowerAngle + beta;
        if (upperAngle > 360)
        {
            upperAngle -= 360;
            if (pointAngle >= lowerAngle || pointAngle <= upperAngle)
                return 1;
            else
                return 0;
        }
        else
        {
            if (pointAngle >= lowerAngle && pointAngle <= upperAngle)
                return 1;
            else
                return 0;
        }
    }
    else if (alpha >= 0 && beta < 0)
    {
        upperAngle = alpha;
        lowerAngle = alpha + beta; //less than upper, maybe -ve
        if (lowerAngle < 0)
        {
            lowerAngle += 360;
            if (pointAngle >= lowerAngle || pointAngle <= upperAngle)
                return 1;
            else
                return 0;
        }
        else
        {
            if (pointAngle >= lowerAngle && pointAngle <= upperAngle)
                return 1;
            else
                return 0;
        }
    }
    else //both negative
    {
        upperAngle = alpha + 360;          //greater than 0
        lowerAngle = 360 + (alpha + beta); //less than 360
        if (lowerAngle < 0)
        {
            lowerAngle += 360;
            if (pointAngle >= lowerAngle || pointAngle <= upperAngle)
                return 1;
            else
                return 0;
        }
        else
        {
            if (pointAngle >= lowerAngle && pointAngle <= upperAngle)
                return 1;
            else
                return 0;
        }
    }
    return 0;
}

void plotArcPoints(float c[2], float x, float y, float alpha, float beta)
{

    if (quadrantCheck(x, y, alpha, beta) == 1)
        draw(c[0] + x, c[1] + y); //Q1
    if (quadrantCheck(-x, y, alpha, beta) == 1)
        draw(c[0] - x, c[1] + y); //Q2
    if (quadrantCheck(-x, -y, alpha, beta) == 1)
        draw(c[0] - x, c[1] - y); //Q3
    if (quadrantCheck(x, -y, alpha, beta) == 1)
        draw(c[0] + x, c[1] - y); //Q4
}

void med(ellipticalArc ell)
{
    float a = ell.a, b = ell.b;
    float x = 0;
    float y = b;
    float a2 = a * a, b2 = b * b;

    float p = round(b2 + a2 * 0.25 - a2 * b);

    float breakpoint = round(a2 / sqrt(a2 + b2));
    for (int i = 0; x <= breakpoint; i++)
    {
        plotArcPoints(ell.c, x, y, ell.alpha, ell.beta);
        if (p < 0) //y does not change
            p += 2 * b2 * (x + 1) + b2;
        else //y decrement
        {
            y--;
            p += 2 * b2 * (x + 1) + b2 - 2 * a2 * (y - 1);
        }
        x++;
    }

    for (int i = 0; y >= 0; i++) //vertical part of ellipse where we iterate y
    {
        plotArcPoints(ell.c, x, y, ell.alpha, ell.beta);
        if (p > 0)
        {
            p += a2 * (1 - 2 * y); //pk for vertical part
        }
        else
        {
            p += a2 * (1 - 2 * y) + 2 * b2 * (x + 1);
            x++;
        }
        y--;
    }
}

void arcDrawing(ellipticalArc ell)
{
    float xAxis[2][2] = {{ell.c[0] - 1000, ell.c[1]},
                         {ell.c[0] + 1000, ell.c[1]}}; // Defining X-Axis for the Quadrants.

    float yAxis[2][2] = {{ell.c[0], ell.c[1] - 1000},
                         {ell.c[0], ell.c[1] + 1000}}; // Defining Y-Axis for the quadrants

    glBegin(GL_LINES); // Drawing the Quadrants.
    glColor3f(1, 1, 1);
    glVertex2fv(xAxis[0]);
    glVertex2fv(xAxis[1]);
    glVertex2fv(yAxis[0]);
    glVertex2fv(yAxis[1]);
    glEnd();

    med(ell);
}

// ============== End of Arc Drawing ============================================

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    ellipse ell = {{500, 500}, 300, 200};
    ellipticalArc ellArc = {{500, 500}, 200, 300, 0, 90};
    // generalEllipseDrawing(ell);
    // parametricEllipseDrawing(ell);
    midPointEllipseDrawing(ell); // Midpoint Ellipse Drawing
    // arcDrawing(ellArc);
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(1000, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Lab 7 - Ellipse - CED18I057");
    myinit();
    glutDisplayFunc(draw);
    glutReshapeFunc(changeViewPort);
    glutMainLoop();
}