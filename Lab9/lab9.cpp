#include <GL/freeglut.h>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

struct setforLine
{
    int a[2], b[2];
    int viewingWindow[2][2];
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
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

void liangBarskyLC(setforLine L)
{
    int dx = L.b[0] - L.a[0];
    int dy = L.b[1] - L.a[1];
    int p[4] = {-dx,
                dx,
                -dy,
                dy};

    int q[4] = {L.a[0] - L.viewingWindow[0][0],
                L.viewingWindow[1][0] - L.a[0],
                L.a[1] - L.viewingWindow[0][1],
                L.viewingWindow[1][1] - L.a[1]};

    float u, u1, u2;
    vector<float> m1, m2;

    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(L.a[0], L.a[1]);
    glVertex2f(L.b[0], L.b[1]);
    glEnd();

    int accept = 0;
    m1.push_back(0);
    m2.push_back(1);
    for (int i = 0; i < 4; i++)
    {
        if (!(p[i] == 0 && q[i] < 0))
        {
            u = (float)q[i] / (float)p[i];
            if (p[i] < 0)
                m1.push_back(u);
            else if (p[i] > 0)
                m2.push_back(u);
        }
    }

    u1 = *max_element(m1.begin(), m1.end());
    u2 = *min_element(m2.begin(), m2.end());

    if (!(u1 > u2))
    {
        // cout << "Line from Point:" << L.a[0] << " " << L.a[1] << " to Point " << L.b[0] << " " << L.b[1] << " is clipped" << endl;

        int _x1 = L.a[0] + u1 * dx;
        int _y1 = L.a[1] + u1 * dy;

        int _x2 = L.a[0] + u2 * dx;
        int _y2 = L.a[1] + u2 * dy;

        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
        glVertex2f(_x1, _y1);
        glVertex2f(_x2, _y2);
        glEnd();

        // cout << "Plotted Lines are from :" << _x1 << " " << _y1 << " to Point " << _x2 << " " << _y2 << endl;
    }
}

int regionCode(int x, int y, int X_min, int Y_min, int X_max, int Y_max)
{
    int code = 0;
    code |= (y > Y_max) ? 8 : 0;
    code |= (y < Y_min) ? 4 : 0;
    code |= (x > X_max) ? 2 : 0;
    code |= (x < X_min) ? 1 : 0;
    return code;
}

void cohenSutherlandLC(setforLine L)
{
    int x1orig = L.a[0], x2orig = L.b[0], y1orig = L.a[1], y2orig = L.b[1];
    int code1 = regionCode(L.a[0], L.a[1], L.viewingWindow[0][0], L.viewingWindow[0][1], L.viewingWindow[1][0], L.viewingWindow[1][1]);
    int code2 = regionCode(L.b[0], L.b[1], L.viewingWindow[0][0], L.viewingWindow[0][1], L.viewingWindow[1][0], L.viewingWindow[1][1]);
    int x, y;
    int accept = 0;
    int clipped = 0;
    while (1)
    {
        if ((code1 == 0) && (code2 == 0))
        {
            accept = 1;
            break;
        }
        else if ((code1 & code2) == 0)
        {
            clipped = 1;
            int code3 = 0;
            if (code1 != 0)
                code3 = code1;
            else if (code2 != 0)
                code3 = code2;

            if (code3 == 0)
                break;

            if (code3 & 8)
            {
                x = L.a[0] + (L.b[0] - L.a[0]) * (L.viewingWindow[1][1] - L.a[1]) / (L.b[1] - L.a[1]);
                y = L.viewingWindow[1][1];
            }
            else if (code3 & 4)
            {
                x = L.a[0] + (L.b[0] - L.a[0]) * (L.viewingWindow[0][1] - L.a[1]) / (L.b[1] - L.a[1]);
                y = L.viewingWindow[0][1];
            }
            else if (code3 & 2)
            {
                y = L.a[1] + (L.b[1] - L.a[1]) * (L.viewingWindow[1][0] - L.a[0]) / (L.b[0] - L.a[0]);
                x = L.viewingWindow[1][0];
            }
            else
            {
                y = L.a[1] + (L.b[1] - L.a[1]) * (L.viewingWindow[0][0] - L.a[0]) / (L.b[0] - L.a[0]);
                x = L.viewingWindow[0][0];
            }

            if (code3 == code1)
            {
                L.a[0] = x;
                L.a[1] = y;
                code1 = regionCode(L.a[0], L.a[1], L.viewingWindow[0][0], L.viewingWindow[0][1], L.viewingWindow[1][0], L.viewingWindow[1][1]);
            }
            else if (code3 == code2)
            {
                L.b[0] = x;
                L.b[1] = y;
                code2 = regionCode(L.b[0], L.b[1], L.viewingWindow[0][0], L.viewingWindow[0][1], L.viewingWindow[1][0], L.viewingWindow[1][1]);
            }
        }
        else
        {
            break;
        }
    }
    if (accept == 1)
    {
        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex2f(L.a[0], L.a[1]);
        glVertex2f(L.b[0], L.b[1]);
        glEnd();

        // cout << "Line from Point: (" << L.a[0] << "," << L.a[1] << ") to Point (" << L.b[0] << "," << L.b[1] << ") is clipped if(either x or y value is changed)" << endl;
        // cout << "Plotted Lines are from :" << L.a[0] << " " << L.a[1] << " to Point " << L.b[0] << " " << L.b[1] << endl;
    }
    if (accept == 1 && clipped == 1)
    {
        // cout << "Line from Point: (" << x1orig << "," << y1orig << ") to Point (" << x2orig << "," << y2orig << ") was out of bounds and thus clipped" << endl;
        // cout << "(" << L.viewingWindow[0][0] << "," << L.viewingWindow[0][1] << ") && (" << L.viewingWindow[1][0] << "," << L.viewingWindow[1][1] << ")";

        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(x1orig, y1orig);
        glVertex2f(x2orig, y2orig);
        glEnd();
        glColor3f(1, 1, 0);
        glBegin(GL_LINES);
        glVertex2f(L.a[0], L.a[1]);
        glVertex2f(L.b[0], L.b[1]);
        glEnd();

        // cout << "Line from Point: (" << L.a[0] << "," << L.a[1] << ") to Point (" << L.b[0] << "," << L.b[1] << ") is clipped" << endl;
        // cout << "Plotted Lines are from :" << L.a[0] << " " << L.a[1] << " to Point " << L.b[0] << " " << L.b[1] << endl;
    }
    else
    {
        // cout << "Line from Point: (" << L.a[0] << "," << L.a[1] << ") to Point (" << L.b[0] << "," << L.b[1] << ") is out of bounds" << endl;
        // cout << "(" << L.viewingWindow[0][0] << "," << L.viewingWindow[0][1] << ") && (" << L.viewingWindow[1][0] << "," << L.viewingWindow[1][1] << ")";

        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(L.a[0], L.a[1]);
        glVertex2f(L.b[0], L.b[1]);
        glEnd();
    }
}

void displayUsingCohenSutherland(setforLine L)
{
    glLineWidth(3);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP); // Drawing the Green Coloured Viewing Window.
    glColor3f(0, 1, 0);
    glVertex2i(L.viewingWindow[0][0], L.viewingWindow[0][1]);
    glVertex2i(L.viewingWindow[1][0], L.viewingWindow[0][1]);
    glVertex2i(L.viewingWindow[1][0], L.viewingWindow[1][1]);
    glVertex2i(L.viewingWindow[0][0], L.viewingWindow[1][1]);
    glEnd();
    glLineWidth(3);
    cohenSutherlandLC(L);
}

void displayUsingLiangBarsky(setforLine L)
{
    glLineWidth(3);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP); // Drawing the Cyan Coloured Viewing Window.
    glColor3f(0, 1, 1);
    glVertex2i(L.viewingWindow[0][0], L.viewingWindow[0][1]);
    glVertex2i(L.viewingWindow[1][0], L.viewingWindow[0][1]);
    glVertex2i(L.viewingWindow[1][0], L.viewingWindow[1][1]);
    glVertex2i(L.viewingWindow[0][0], L.viewingWindow[1][1]);
    glEnd();
    glLineWidth(3);
    liangBarskyLC(L);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //making a viewing Window
    int X_min, X_max, Y_min, Y_max, x, y, choice, n;
    X_min = rand() % 400;
    X_max = rand() % 400;
    if (X_min > X_max)
        swap(X_min, X_max);
    Y_min = rand() % 400;
    Y_max = rand() % 400;
    if (Y_min > Y_max)
        swap(Y_min, Y_max);

    choice = 1; //choice to switch between LBLC and CSLC
    n = 5;      //No of Lines

    if (choice == 0)
    {
        //Randomly generate Lines
        for (int i = 0; i < n; i++)
        {
            setforLine L = {
                {x = rand() % (int)X_min, y = rand() % (int)Y_min}, {(int)(x + rand() % 1000) % 1000, (int)(y + rand() % 1000) % 1000}, {{X_min, Y_min}, {X_max, Y_max}}};
            displayUsingCohenSutherland(L);
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            setforLine L = {
                {x = rand() % (int)X_min, y = rand() % (int)Y_min}, {(int)(x + rand() % 1000) % 1000, (int)(y + rand() % 1000) % 1000}, {{X_min, Y_min}, {X_max, Y_max}}};
            displayUsingLiangBarsky(L);
        }
    }

    cout << "\nNOTE:Lines drawn in red are out of bound lines.\nGreen lines are drawn using Cohen-Sutherland Line Clipping Algorithm and the viewing window is green colored\nBlue lines are drawn using Liang-Barsky Line Clipping Algorithm and the viewing window is cyan\n";
    glFinish();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 9 - Point and Line Clipping - CED18I057");
    myinit();
    glutDisplayFunc(display);
    glutReshapeFunc(changeViewPort);
    glutMainLoop();
}