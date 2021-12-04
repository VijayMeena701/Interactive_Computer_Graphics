/* Question: Using OpenGL, reflect the word "EWJH" over the line x*cos(theta)+y*sin(theta)=r.
The line is represented using the ploar coordinate system (r, theta), where r is the length of the perpendicular,
from the origin over the given line and theta is the angle made by the perpendicular with the positive x-axis in the counter-clockwise direction.
The user should take random inputs for (r, theta). After reflection, fill the reflected shapes using Scan Line Poly Fill Algorithm.
You can directly use the Scan Line Poly Fill Algorithm that was asked in Lab-11.
The dimensions of the various components in the word can be considered as you wish, but the overall word should be the same as asked in the question.*/

#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <bits/stdc++.h>
#include <math.h>
#define maxHt 1280
#define maxWd 800
#define maxVer 10000
using namespace std;

#define PI 3.1415926535
bool fullscreen = false;
int p = 0, q = 0, r = 0, s = 0, t = 0;
float slope;
int intercept;

int fillFlag = 0;

FILE *fp;
typedef struct edgebucket
{
    int ymax;
    float xofymin;
    float slopeinverse;
} EdgeBucket;

typedef struct edgetabletup
{
    int countEdgeBucket;
    EdgeBucket buckets[maxVer];
} EdgeTableTuple;

EdgeTableTuple EdgeTable[maxHt], ActiveEdgeTuple;

void initEdgeTable()
{
    int i;
    for (i = 0; i < maxHt; i++)
    {
        EdgeTable[i].countEdgeBucket = 0;
    }

    ActiveEdgeTuple.countEdgeBucket = 0;
}

void printTuple(EdgeTableTuple *tup)
{
    int j;

    if (tup->countEdgeBucket)
        printf("\nCount %d-----\n", tup->countEdgeBucket);

    for (j = 0; j < tup->countEdgeBucket; j++)
    {
        printf(" %d+%.2f+%.2f",
               tup->buckets[j].ymax, tup->buckets[j].xofymin, tup->buckets[j].slopeinverse);
    }
}

void printTable()
{
    int i, j;

    for (i = 0; i < maxHt; i++)
    {
        if (EdgeTable[i].countEdgeBucket)

            printTuple(&EdgeTable[i]);
    }
}

void insertionSort(EdgeTableTuple *ett)
{
    int i, j;
    EdgeBucket temp;

    for (i = 1; i < ett->countEdgeBucket; i++)
    {
        temp.ymax = ett->buckets[i].ymax;
        temp.xofymin = ett->buckets[i].xofymin;
        temp.slopeinverse = ett->buckets[i].slopeinverse;
        j = i - 1;

        while ((temp.xofymin < ett->buckets[j].xofymin) && (j >= 0))
        {
            ett->buckets[j + 1].ymax = ett->buckets[j].ymax;
            ett->buckets[j + 1].xofymin = ett->buckets[j].xofymin;
            ett->buckets[j + 1].slopeinverse = ett->buckets[j].slopeinverse;
            j = j - 1;
        }
        ett->buckets[j + 1].ymax = temp.ymax;
        ett->buckets[j + 1].xofymin = temp.xofymin;
        ett->buckets[j + 1].slopeinverse = temp.slopeinverse;
    }
}

void storeEdgeInTuple(EdgeTableTuple *receiver, int ym, int xm, float slopInv)
{
    (receiver->buckets[(receiver)->countEdgeBucket]).ymax = ym;
    (receiver->buckets[(receiver)->countEdgeBucket]).xofymin = (float)xm;
    (receiver->buckets[(receiver)->countEdgeBucket]).slopeinverse = slopInv;

    insertionSort(receiver);

    (receiver->countEdgeBucket)++;
}

void storeEdgeInTable(int x1, int y1, int x2, int y2)
{
    float m, minv;
    int ymaxTS, xwithyminTS, scanline;

    if (x2 == x1)
    {
        minv = 0.000000;
    }
    else
    {
        m = ((float)(y2 - y1)) / ((float)(x2 - x1));
        if (y2 == y1)
            return;

        minv = (float)1.0 / m;
    }

    if (y1 > y2)
    {
        scanline = y2;
        ymaxTS = y1;
        xwithyminTS = x2;
    }
    else
    {
        scanline = y1;
        ymaxTS = y2;
        xwithyminTS = x1;
    }
    storeEdgeInTuple(&EdgeTable[scanline], ymaxTS, xwithyminTS, minv);
}

void removeEdgeByYmax(EdgeTableTuple *Tup, int yy)
{
    int i, j;
    for (i = 0; i < Tup->countEdgeBucket; i++)
    {
        if (Tup->buckets[i].ymax == yy)
        {
            for (j = i; j < Tup->countEdgeBucket - 1; j++)
            {
                Tup->buckets[j].ymax = Tup->buckets[j + 1].ymax;
                Tup->buckets[j].xofymin = Tup->buckets[j + 1].xofymin;
                Tup->buckets[j].slopeinverse = Tup->buckets[j + 1].slopeinverse;
            }
            Tup->countEdgeBucket--;
            i--;
        }
    }
}

void updatexbyslopeinv(EdgeTableTuple *Tup)
{
    int i;

    for (i = 0; i < Tup->countEdgeBucket; i++)
    {
        (Tup->buckets[i]).xofymin = (Tup->buckets[i]).xofymin + (Tup->buckets[i]).slopeinverse;
    }
}

void ScanlineFill()
{

    int i, j, x1, ymax1, x2, ymax2, FillFlag = 0, coordCount;
    for (i = 0; i < maxHt; i++)
    {
        for (j = 0; j < EdgeTable[i].countEdgeBucket; j++)
        {
            storeEdgeInTuple(&ActiveEdgeTuple, EdgeTable[i].buckets[j].ymax, EdgeTable[i].buckets[j].xofymin,
                             EdgeTable[i].buckets[j].slopeinverse);
        }
        // printTuple(&ActiveEdgeTuple);
        removeEdgeByYmax(&ActiveEdgeTuple, i);
        insertionSort(&ActiveEdgeTuple);

        // printTuple(&ActiveEdgeTuple);
        j = 0;
        FillFlag = 0;
        coordCount = 0;
        x1 = 0;
        x2 = 0;
        ymax1 = 0;
        ymax2 = 0;
        while (j < ActiveEdgeTuple.countEdgeBucket)
        {
            if (coordCount % 2 == 0)
            {
                x1 = (int)(ActiveEdgeTuple.buckets[j].xofymin);
                ymax1 = ActiveEdgeTuple.buckets[j].ymax;
                if (x1 == x2)
                {
                    if (((x1 == ymax1) && (x2 != ymax2)) || ((x1 != ymax1) && (x2 == ymax2)))
                    {
                        x2 = x1;
                        ymax2 = ymax1;
                    }

                    else
                    {
                        coordCount++;
                    }
                }

                else
                {
                    coordCount++;
                }
            }
            else
            {
                x2 = (int)ActiveEdgeTuple.buckets[j].xofymin;
                ymax2 = ActiveEdgeTuple.buckets[j].ymax;

                FillFlag = 0;
                if (x1 == x2)
                {
                    if (((x1 == ymax1) && (x2 != ymax2)) || ((x1 != ymax1) && (x2 == ymax2)))
                    {
                        x1 = x2;
                        ymax1 = ymax2;
                    }
                    else
                    {
                        coordCount++;
                        FillFlag = 1;
                    }
                }
                else
                {
                    coordCount++;
                    FillFlag = 1;
                }

                if (FillFlag)
                {
                    glColor3f(0.0f, 0.7f, 0.0f);

                    glBegin(GL_LINES);
                    glVertex2i(x1, i);
                    glVertex2i(x2, i);
                    glEnd();
                    glFlush();
                }
            }

            j++;
        }
        updatexbyslopeinv(&ActiveEdgeTuple);
    }

    printf("\nScanline filling complete");
}

void myInit(void)
{

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluOrtho2D(0, maxHt, 0, maxWd);
    glClear(GL_COLOR_BUFFER_BIT);
}

void drawPoly()
{

    glColor3f(1.0f, 0.0f, 0.0f);
    int count = 0, x1, y1, x2, y2;
    rewind(fp);
    while (!feof(fp))
    {
        count++;
        if (count > 2)
        {
            x1 = x2;
            y1 = y2;
            count = 2;
        }
        if (count == 1)
        {
            fscanf(fp, "%d,%d", &x1, &y1);
        }
        else
        {
            fscanf(fp, "%d,%d", &x2, &y2);
            glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
            glEnd();
            storeEdgeInTable(x1, y1, x2, y2);

            glFlush();
        }
    }
}

void reflect_line(int x1, int y1, int x2, int y2)
{
    int x11, y11, x22, y22;

    x11 = (((1 - slope * slope) * x1) + (2 * slope * (y1 - intercept))) / (1 + slope * slope);
    y11 = (((slope * slope - 1) * y1) + (2 * slope * x1) + 2 * intercept) / (1 + slope * slope);
    x22 = (((1 - slope * slope) * x2) + (2 * slope * (y2 - intercept))) / (1 + slope * slope);
    y22 = (((slope * slope - 1) * y2) + (2 * slope * x2) + 2 * intercept) / (1 + slope * slope);
    glColor3f(0.3, 0.3, 1.0);
    // drawline(x11, y11, x22, y22);
}

void display(void)
{
    initEdgeTable();
    drawPoly();
    ScanlineFill();
}

int main(int argc, char **argv)
{
    fp = fopen("word.txt", "r");
    if (fp == NULL)
    {
        printf("Could not open file");
        return 0;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(maxHt, maxWd);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("CED18I057 Lab Exam");
    myInit();
    glutDisplayFunc(display);

    glutMainLoop();
    fclose(fp);
    return 0;
}
