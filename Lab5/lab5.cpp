//g++ Assignment5-CED18I057.cpp -lGL -lGLU -lglut -lGLEW -o lab5

// USE '1' AND '2' TO NAVIGATE FROM HEXAGON TO HOUSE, and '~' to toggle between DDA and BLD, and call 1 or 2 to draw
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

int drawMode = 0;

float DDA_MSE_TOTAL = 0;
float BLD_MSE_TOTAL = 0;

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
    gluOrtho2D(0.0, 1000.0, 0.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void plot(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(round(x), round(y));
    glEnd();
}

float randColor()
{
    float r = (float)((rand() % 1000)) / 999;
    return r;
}

vector<pair<float, float>> bruteMSE(float p1[2], float p2[2])
{
    vector<pair<float, float>> brute;
    float x1 = p1[0], y1 = p1[1];
    float x2 = p2[0], y2 = p2[1];
    float dx = x2 - x1; //5
    float dy = y2 - y1; //3
    float m = dy / dx;
    float dist, inX, inY;

    if (abs(m) < 1)
        dist = abs(dx);
    else
        dist = abs(dy);

    inX = dx / dist; // if m<1 , inX is 1, else 1/m
    inY = dy / dist; // if m<1 , inY is m, else 1

    float x = x1, y = y1;
    for (int i = 0; i < dist; i++)
    {
        plot(x, y);
        brute.push_back(make_pair(x, y));
        x += inX;
        y += inY;
    }
    return brute;
}

void DDA(float p1[2], float p2[2])
{
    float DDA_MSE = 0;
    vector<pair<float, float>> dda;
    vector<pair<float, float>> brute = bruteMSE(p1, p2);
    float x1 = p1[0], y1 = p1[1];
    float x2 = p2[0], y2 = p2[1];
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

    float x = x1, y = y1;
    //glColor3f(randColor(),randColor(),randColor());
    for (int i = 0; i < dist; i++)
    {
        plot(x, y);
        dda.push_back(make_pair(round(x), round(y)));
        x += inX;
        y += inY;
    }

    //Calculation of MSE of line segment
    for (int i = 0; i < dda.size(); i++)
    {
        // cout << PP[i] << " - " << DDA[i] << endl;
        DDA_MSE += pow((brute[i].first - dda[i].first), 2) + pow((brute[i].second - dda[i].second), 2);
    }
    DDA_MSE /= (float)dda.size();
    //printf("DDA - From (%f,%f) to (%f,%f), Error: %f\n", x1, y1, x2, y2, DDA_MSE);
    DDA_MSE_TOTAL += DDA_MSE;
}

void BLD(float p1[2], float p2[2])
{
    float BLD_MSE = 0;
    vector<pair<float, float>> bld;
    vector<pair<float, float>> brute = bruteMSE(p1, p2);
    float x1 = p1[0], y1 = p1[1];
    float x2 = p2[0], y2 = p2[1];
    float dx = x2 - x1;
    float dy = y2 - y1;
    float m = dy / dx;
    float dist, inX, inY;
    int x, y;

    int p;

    if (abs(dy) < abs(dx)) //if m < 1
    {
        p = 2 * abs(dy) - abs(dx); //initial decision parameter
        for (int i = 0; i < abs(dx); i++)
        {
            x = round(x1);
            y = round(y1);
            plot(x, y);
            bld.push_back(make_pair(x, y));

            if (p > 0)
            {
                p += (2 * abs(dy) - 2 * abs(dx));
                y1 += dy / abs(dy);
            }
            else
            {
                p += (2 * abs(dy));
            }
            x1 += dx / (abs(dx));
        }
    }
    else
    {
        p = 2 * abs(dx) - abs(dy); //initial decision parameter
        for (int i = 0; i < abs(dy); i++)
        {
            x = round(x1);
            y = round(y1);
            plot(x, y);
            bld.push_back(make_pair(x, y));

            if (p > 0)
            {
                p += (2 * abs(dx) - 2 * abs(dy));
                x1 += dx / abs(dx);
            }
            else
            {
                p += (2 * abs(dx));
            }
            y1 += dy / (abs(dy));
        }
    }

    //Calculation of MSE of line segment
    for (int i = 0; i < bld.size(); i++)
    {
        // cout << PP[i] << " - " << DDA[i] << endl;
        BLD_MSE += pow((brute[i].first - bld[i].first), 2) + pow((brute[i].second - bld[i].second), 2);
    }
    BLD_MSE /= (float)bld.size();
    //printf("BLD - From (%f,%f) to (%f,%f), Error: %f\n", x1, y1, x2, y2, BLD_MSE);
    BLD_MSE_TOTAL += BLD_MSE;
}

void plotMode(float p1[2], float p2[2])
{
    if (drawMode == 0)
        DDA(p1, p2);
    else
        BLD(p1, p2);
}
void fillTriange(float p1[2], float p2[2], float p3[2])
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

    for (i = 0; i < dist; i++)
    {
        plotMode(vertex, point);
        point[0] += inX;
        point[1] += inY;
    }
}

void hexagon()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //HEXAGON CONTROLS___
    float c[2] = {500, 500}; //center
    float r = 300;           //side length
    float rotation = 30;     // in degrees
    //__________________
    float p1[2] = {round(c[0] + r * (float)cos((rotation + 90) * M_PI / 180)), round(c[1] + r * (float)sin((rotation + 90) * M_PI / 180))};
    float p2[2] = {round(c[0] + r * (float)cos((rotation + 30) * M_PI / 180)), round(c[1] + r * (float)sin((rotation + 30) * M_PI / 180))};
    float p3[2] = {round(c[0] + r * (float)cos((rotation + -30) * M_PI / 180)), round(c[1] + r * (float)sin((rotation + -30) * M_PI / 180))};
    float p4[2] = {round(c[0] + r * (float)cos((rotation + -90) * M_PI / 180)), round(c[1] + r * (float)sin((rotation + -90) * M_PI / 180))};
    float p5[2] = {round(c[0] + r * (float)cos((rotation + -150) * M_PI / 180)), round(c[1] + r * (float)sin((rotation + -150) * M_PI / 180))};
    float p6[2] = {round(c[0] + r * (float)cos((rotation + 150) * M_PI / 180)), round(c[1] + r * (float)sin((rotation + 150) * M_PI / 180))};
    glPointSize(3);
    glColor3f(0, 0, 0);

    plotMode(p1, p2);
    plotMode(p2, p3);
    plotMode(p3, p4);
    plotMode(p4, p5);
    plotMode(p5, p6);
    plotMode(p6, p1);

    glutSwapBuffers();
    if (drawMode == 0)
        printf("Total DDA Mean Square Error = %f \n", DDA_MSE_TOTAL);
    else
        printf("Total BLD Mean Square Error = %f \n", BLD_MSE_TOTAL);

    DDA_MSE_TOTAL = 0;
    BLD_MSE_TOTAL = 0;
}

void house()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPointSize(3);

    //_____House____________

    float a[2] = {300, 100};
    float b[2] = {700, 100};
    float c[2] = {700, 500};
    float d[2] = {300, 500};

    //filling in color
    glColor3f(0.2, 0.2, 1); //blue

    fillTriange(a, c, b);
    fillTriange(a, c, d); //along diagonal

    //outline
    glColor3f(0, 0, 0); //black outline
    plotMode(a, b);
    plotMode(b, c);
    plotMode(c, d);
    plotMode(d, a);

    //_____ROOF__________

    float e[2] = {500, 800}; //roof tip

    //filling in color
    glColor3f(1, 0.3, 0.3); //red

    fillTriange(c, d, e);

    //outline
    glColor3f(0, 0, 0); //black outline
    plotMode(c, d);
    plotMode(d, e);
    plotMode(e, c);

    //______DOOR_________

    float f[2] = {460, 100};
    float g[2] = {540, 100};
    float h[2] = {540, 300};
    float i[2] = {460, 300};

    //filling in color
    glColor3f(1, 1, 1); //white

    fillTriange(f, h, g);
    fillTriange(f, h, i);

    //outline
    glColor3f(0, 0, 0); //black outline
    plotMode(f, g);
    plotMode(g, h);
    plotMode(h, i);
    plotMode(i, f);

    //______LEFT WINDOW__________

    float j[2] = {350, 250};
    float k[2] = {400, 250};
    float l[2] = {400, 300};
    float m[2] = {350, 300};

    //filling in color
    glColor3f(1, 1, 1); //white

    fillTriange(j, l, k);
    fillTriange(j, l, m);

    //outline
    glColor3f(0, 0, 0); //black outline
    plotMode(j, k);
    plotMode(k, l);
    plotMode(l, m);
    plotMode(m, j);

    //______RIGHT WINDOW__________

    float n[2] = {600, 250};
    float o[2] = {650, 250};
    float p[2] = {650, 300};
    float q[2] = {600, 300};

    //filling in color
    glColor3f(1, 1, 1); //white

    fillTriange(n, p, o);
    fillTriange(n, p, q);

    //outline
    glColor3f(0, 0, 0); //black outline
    plotMode(n, o);
    plotMode(o, p);
    plotMode(p, q);
    plotMode(q, n);

    glutSwapBuffers();
    if (drawMode == 0)
        printf("Total DDA Mean Square Error = %f \n", DDA_MSE_TOTAL);
    else
        printf("Total BLD Mean Square Error = %f \n", BLD_MSE_TOTAL);

    DDA_MSE_TOTAL = 0;
    BLD_MSE_TOTAL = 0;
}

void select();
void keyboard(unsigned char key, int x, int y);
void timer(int)
{
    glutTimerFunc(33, timer, 0);
    glutKeyboardFunc(keyboard);
}

int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(800, 100);
    glutInitWindowSize(800, 800);

    glutCreateWindow("Lab 5 - Hexagon - CED18I057");
    myinit();
    glutDisplayFunc(hexagon);
    glutReshapeFunc(changeViewPort);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        glutDestroyWindow(glutGetWindow());
        if (drawMode == 0)
            printf("Displaying Hexagon with DDA Algorithm \n");
        else
            printf("Displaying Hexagon with BLD Algorithm \n");
        glutCreateWindow("Lab 5 - Hexagon - CED18I057");
        myinit();
        glutDisplayFunc(hexagon);
        break;

    case '2':
        glutDestroyWindow(glutGetWindow());
        if (drawMode == 0)
            printf("Displaying House with DDA Algorithm \n");
        else
            printf("Displaying House with BLD Algorithm \n");
        glutCreateWindow("Lab 5 - House - CED18I057");
        myinit();
        glutDisplayFunc(house);
        break;
    case '`':
        if (drawMode == 0)
        {
            drawMode = 1;
            printf("Draw Mode Changed to BLD Algorithm! \n");
        }
        else
        {
            drawMode = 0;
            printf("Draw Mode Changed to DDA Algorithm! \n");
        }
    }
    glutPostRedisplay();
}
