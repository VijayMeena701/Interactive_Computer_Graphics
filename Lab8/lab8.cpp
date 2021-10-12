//g++ lab8.cpp -lGL -lGLU -lglut -lGLEW -o lab8

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;
#define LENGTH 1000
#define HEIGHT 1000

struct Parabola
{
    int c[2];
    int a;
    float color[3];
    int choice;
};

struct Hyperbola
{
    int c[2];
    int a;
    int b;
    float color[3];
    int choice;
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
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, LENGTH, 0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
}

// ============================================================================
// ================== Parabola ================================================
// ============================================================================

void plot(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(round(x), round(y));
    glEnd();
}

void illuminate2Q(int c[2], float x, float y)
{
    plot(c[0] + x, c[1] + y); //Q1
    plot(c[0] - x, c[1] + y); //Q2
    plot(c[0] - x, c[1] - y); //Q3
    plot(c[0] + x, c[1] - y); //Q4
}

void mpd(Parabola P)
{
    float a = P.a;
    float x = 0;
    float y = 0;

    float p = 1 - (2 * a);

    float ymid = 2 * a;

    for (int i = 0; y <= ymid; i++) // Region 1
    {
        illuminate2Q(P.c, x, y);
        if (p < 0)
        {
            p += 1 + (2 * y);
        }
        else
        {
            x++;
            p += 1 + (2 * y) - (4 * a);
        }
        y++;
    }

    float p2 = pow((y + 0.5), 2) - ((4 * a) * (x + 1));

    for (int i = 0; x <= 500; i++) // Region 2
    {
        illuminate2Q(P.c, x, y);
        if (p2 < 0)
        {
            y++;
            p2 += (2 * y) - (4 * a);
        }
        else
        {
            p2 = p2 - (4 * a);
        }
        x++;
    }
}

void paraMetricParabolaDrawing(Parabola parabola)
{
    int xc = parabola.c[0];
    int yc = parabola.c[1];
    int a = parabola.a;
    glPointSize(3.5);
    glColor3f(parabola.color[0], parabola.color[1], parabola.color[2]);
    float step = 0.001;
    int iter = 0;
    float theta = 0;
    float t = 0;
    float x = 0;
    float y = 0;
    while (x < 400 || y < 400)
    {
        x = a * t * t;
        y = 2 * a * t;
        if (parabola.choice == 0)
        {
            glBegin(GL_POINTS);
            glVertex2f(xc + x, yc + y);
            glVertex2f(xc + x, yc - y);
            glVertex2f(xc - x, yc + y);
            glVertex2f(xc - x, yc - y);
            glEnd();
        }
        else
        {
            glBegin(GL_POINTS);
            glVertex2f(yc + y, xc + x);
            glVertex2f(yc - y, xc + x);
            glVertex2f(yc + y, xc - x);
            glVertex2f(yc - y, xc - x);
            glEnd();
        }
        t += step;
    }
}

void generalHyperbolaDrawing(Parabola parabola)
{
    float x = 0, y = 0;
    glPointSize(1.5);
    glColor3f(parabola.color[0], parabola.color[1], parabola.color[2]);
    if (parabola.choice == 0)
    {
        while (x < 500 || y < 500)
        {
            y = (float)2 * sqrt(parabola.a * x);
            glBegin(GL_POINTS);
            glVertex2f(parabola.c[0] + x, parabola.c[1] + y);
            glVertex2f(parabola.c[0] + x, parabola.c[1] - y);
            glVertex2f(parabola.c[0] - x, parabola.c[1] + y);
            glVertex2f(parabola.c[0] - x, parabola.c[1] - y);
            glEnd();
            x++;
        }
    }
    else
    {
        while (x < 500 || y < 500)
        {
            y = (float)2 * sqrt(parabola.a * x);
            glBegin(GL_POINTS);
            glVertex2f(parabola.c[1] + y, parabola.c[0] + x);
            glVertex2f(parabola.c[1] - y, parabola.c[0] + x);
            glVertex2f(parabola.c[1] + y, parabola.c[0] - x);
            glVertex2f(parabola.c[1] - y, parabola.c[0] - x);
            glEnd();
            x++;
        }
    }
}

void drawParabola()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    float color1[] = {static_cast<float>((rand() % 255) / 255.0), static_cast<float>((rand() % 255) / 255.0), static_cast<float>((rand() % 255) / 255.0)};
    float color2[] = {static_cast<float>((rand() % 255) / 255.0), static_cast<float>((rand() % 255) / 255.0), static_cast<float>((rand() % 255) / 255.0)};
    float color3[] = {static_cast<float>((rand() % 255) / 255.0), static_cast<float>((rand() % 255) / 255.0), static_cast<float>((rand() % 255) / 255.0)};

    int a1, a2, a3;
    a1 = rand() % 200 + 1;
    a2 = rand() % 200 + 1;
    a3 = rand() % 200 + 1;
    int choice = rand() % 2;
    int xc = rand() % 400 + 100;
    int yc = rand() % 400 + 100;
    Parabola P1 = {{xc, yc}, 01, {color1[0], color1[1], color1[2]}, choice};
    Parabola P2 = {{xc, yc}, a2, {color2[0], color2[1], color2[2]}, choice};
    Parabola P3 = {{xc, yc}, a3, {color3[0], color3[1], color3[2]}, choice};
    mpd(P1);
    paraMetricParabolaDrawing(P2);
    generalHyperbolaDrawing(P3);
    glutSwapBuffers();
}

// ===================================================================
// ================ HyperBola ========================================
// ===================================================================

void midPointHyperbolaDrawing(Hyperbola hyperbola, int thresh = 10000)
{
    glPointSize(1.5);
    glColor3f(hyperbola.color[0], hyperbola.color[1], hyperbola.color[2]);

    if (hyperbola.choice == 0)
    {
        //Region 1
        float x = hyperbola.a, y = 0;
        float p = hyperbola.a * hyperbola.b * hyperbola.b - hyperbola.a * hyperbola.a + hyperbola.b * hyperbola.b / 4;
        while (x * hyperbola.b * hyperbola.b > y * hyperbola.a * hyperbola.a && y < thresh)
        {
            glBegin(GL_POINTS);
            glVertex2f(hyperbola.c[0] + x, hyperbola.c[1] + y);
            glVertex2f(hyperbola.c[0] + x, hyperbola.c[1] - y);
            glVertex2f(hyperbola.c[0] - x, hyperbola.c[1] + y);
            glVertex2f(hyperbola.c[0] - x, hyperbola.c[1] - y);
            glEnd();
            y += 1;
            if (p > 0)
            {
                p = p - hyperbola.a * hyperbola.a * (2 * y + 1);
            }
            else
            {
                x += 1;
                p = p - hyperbola.a * hyperbola.a * (2 * y + 1) + hyperbola.b * hyperbola.b * (2 * x);
            }
        }
        //Region 2
        if (hyperbola.a > hyperbola.b)
        {
            float load_x = hyperbola.a * hyperbola.a / sqrt(hyperbola.a * hyperbola.a - hyperbola.b * hyperbola.b);
            float load_y = hyperbola.b * hyperbola.b / sqrt(hyperbola.a * hyperbola.a - hyperbola.b * hyperbola.b);
            p = pow(hyperbola.b * (x + 1), 2) + pow(hyperbola.a * (y + 1 / 2), 2) - hyperbola.a * hyperbola.a * hyperbola.b * hyperbola.b;
            while (x < 400)
            {
                glBegin(GL_POINTS);
                glVertex2f(hyperbola.c[0] + x, hyperbola.c[1] + y);
                glVertex2f(hyperbola.c[0] + x, hyperbola.c[1] - y);
                glVertex2f(hyperbola.c[0] - x, hyperbola.c[1] + y);
                glVertex2f(hyperbola.c[0] - x, hyperbola.c[1] - y);
                glEnd();
                x += 1;
                if (p < 0)
                    p = p + hyperbola.b * hyperbola.b * (2 * x + 1);
                else
                {
                    y += 1;
                    p = p + hyperbola.b * hyperbola.b * (2 * x + 1) - hyperbola.a * hyperbola.a * (2 * y);
                }
            }
        }
    }
    else
    {
        //Region 1
        float x = hyperbola.a, y = 0;
        float p = hyperbola.a * hyperbola.b * hyperbola.b - hyperbola.a * hyperbola.a + hyperbola.b * hyperbola.b / 4;
        while (x * hyperbola.b * hyperbola.b > y * hyperbola.a * hyperbola.a && y < 600)
        {
            glBegin(GL_POINTS);
            glVertex2f(hyperbola.c[1] + y, hyperbola.c[0] + x);
            glVertex2f(hyperbola.c[1] - y, hyperbola.c[0] + x);
            glVertex2f(hyperbola.c[1] + y, hyperbola.c[0] - x);
            glVertex2f(hyperbola.c[1] - y, hyperbola.c[0] - x);
            glEnd();
            y += 1;
            if (p > 0)
            {
                p = p - hyperbola.a * hyperbola.a * (2 * y + 1);
            }
            else
            {
                x += 1;
                p = p - hyperbola.a * hyperbola.a * (2 * y + 1) + hyperbola.b * hyperbola.b * (2 * x);
            }
        }
        //Region 2
        if (hyperbola.a > hyperbola.b)
        {
            float load_x = (float)hyperbola.a * hyperbola.a / sqrt(hyperbola.a * hyperbola.a - hyperbola.b * hyperbola.b);
            float load_y = (float)hyperbola.b * hyperbola.b / sqrt(hyperbola.a * hyperbola.a - hyperbola.b * hyperbola.b);
            p = pow(hyperbola.b * (x + 1), 2) + pow(hyperbola.a * (y + 1 / 2), 2) - hyperbola.a * hyperbola.a * hyperbola.b * hyperbola.b;
            while (x < 400)
            {
                glBegin(GL_POINTS);
                glVertex2f(hyperbola.c[1] + y, hyperbola.c[0] + x);
                glVertex2f(hyperbola.c[1] - y, hyperbola.c[0] + x);
                glVertex2f(hyperbola.c[1] + y, hyperbola.c[0] - x);
                glVertex2f(hyperbola.c[1] - y, hyperbola.c[0] - x);
                glEnd();
                x += 1;
                if (p < 0)
                    p = p + hyperbola.b * hyperbola.b * (2 * x + 1);
                else
                {
                    y += 1;
                    p = p + hyperbola.b * hyperbola.b * (2 * x + 1) - hyperbola.a * hyperbola.a * (2 * y);
                }
            }
        }
    }
}

void paraMetricHyperbolaDrawing(Hyperbola hyperbola)
{
    int xc = hyperbola.c[0];
    int yc = hyperbola.c[1];
    int a = hyperbola.a;
    int b = hyperbola.b;
    int c = hyperbola.choice;
    glPointSize(3.5);
    glColor3f(hyperbola.color[0], hyperbola.color[1], hyperbola.color[2]);
    float step = 2 * (M_PI) / (4 * a - 4);
    int iter = 0;
    float theta = 0;
    float x = 0, y = 0;
    while (theta < M_PI / 2)
    {
        x = a / cos(theta);
        y = b * tan(theta);
        if (c == 0)
        {
            glBegin(GL_POINTS);
            glVertex2f(xc + x, yc + y);
            glVertex2f(xc + x, yc - y);
            glVertex2f(xc - x, yc + y);
            glVertex2f(xc - x, yc - y);
            glEnd();
        }
        else
        {
            glBegin(GL_POINTS);
            glVertex2f(yc + y, xc + x);
            glVertex2f(yc - y, xc + x);
            glVertex2f(yc + y, xc - x);
            glVertex2f(yc - y, xc - x);
            glEnd();
        }
        theta += step;
    }
}

void generalHyperbolaDrawing(Hyperbola hyperbola)
{
    float x = hyperbola.a, y = 0;
    glPointSize(1.5);
    glColor3f(hyperbola.color[0], hyperbola.color[1], hyperbola.color[2]);
    if (hyperbola.choice == 0)
    {
        while (x < hyperbola.a + 400)
        {
            y = (float)hyperbola.b / hyperbola.a * sqrt(x * x - hyperbola.a * hyperbola.a);
            glBegin(GL_POINTS);
            glVertex2f(hyperbola.c[0] + x, hyperbola.c[1] + y);
            glVertex2f(hyperbola.c[0] + x, hyperbola.c[1] - y);
            glVertex2f(hyperbola.c[0] - x, hyperbola.c[1] + y);
            glVertex2f(hyperbola.c[0] - x, hyperbola.c[1] - y);
            glEnd();
            x++;
        }
    }
    else
    {
        while (x < hyperbola.a + 400)
        {
            y = (float)hyperbola.b / hyperbola.a * sqrt(x * x - hyperbola.a * hyperbola.a);
            glBegin(GL_POINTS);
            glVertex2f(hyperbola.c[1] + y, hyperbola.c[0] + x);
            glVertex2f(hyperbola.c[1] - y, hyperbola.c[0] + x);
            glVertex2f(hyperbola.c[1] + y, hyperbola.c[0] - x);
            glVertex2f(hyperbola.c[1] - y, hyperbola.c[0] - x);
            glEnd();
            x++;
        }
    }
}

void window_color()
{

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw()
{

    window_color();
    float colour1[] = {static_cast<float>((rand() % 255) / 255.0), static_cast<float>((rand() % 255) / 255.0), static_cast<float>((rand() % 255) / 255.0)};
    float colour2[] = {static_cast<float>((rand() % 255) / 255.0), static_cast<float>((rand() % 255) / 255.0), static_cast<float>((rand() % 255) / 255.0)};
    float colour3[] = {static_cast<float>((rand() % 255) / 255.0), static_cast<float>((rand() % 255) / 255.0), static_cast<float>((rand() % 255) / 255.0)};

    int a1, a2, a3, b1, b2, b3;
    a1 = rand() % 200 + 1;
    a2 = rand() % 200 + 1;
    a3 = rand() % 200 + 1;
    b1 = rand() % 200 + 1;
    b2 = rand() % 200 + 1;
    b3 = rand() % 200 + 1;
    int choice = rand() % 2;
    int xc = rand() % 400 + 100;
    int yc = rand() % 400 + 100;

    Hyperbola h1 = {{xc, yc}, 0, 0, {colour1[0], colour1[1], colour1[2]}, choice};
    Hyperbola h2 = {{xc, yc}, 0, 0, {colour2[0], colour2[1], colour2[2]}, choice};
    Hyperbola h3 = {{xc, yc}, a3, b3, {colour3[0], colour3[1], colour3[2]}, choice};

    paraMetricHyperbolaDrawing(h1);
    midPointHyperbolaDrawing(h2);
    generalHyperbolaDrawing(h3);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(LENGTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 8 - Parabola - CED18I057");
    myinit();
    glutDisplayFunc(draw);
    // glutDisplayFunc(drawParabola);
    glutReshapeFunc(changeViewPort);
    glutMainLoop();
}