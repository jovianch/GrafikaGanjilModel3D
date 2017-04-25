
#include <GL/glut.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#define GLUT_DISABLE_ATEXIT_HACK
 GLfloat xRotated, yRotated, zRotated;

void init(void)
{
    glClearColor(0,0,1,0);

}

void DrawSemiCircle(float cx, float cy, float z, float r, int num_segments, int begindraw, int enddraw, float red, float green, float blue, float alpha) {
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(red, green, blue, alpha);
    for(int ii = begindraw; ii < enddraw; ii++)
    {
        float theta = 2.0 * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex3f(x + cx, y + cy, z);//output vertex
    }
    glEnd();
}

void DrawCube(float x1, float x2, float y1, float y2, float z1, float z2) {
    glBegin(GL_QUADS);        // Draw The Cube Using quads
        glColor3f(0.0f,0.0f,0.0f);    // Color Black
        glVertex3f(x2,y2,z2);    // FRONT
        glVertex3f(x1,y2,z2);
        glVertex3f(x1,y1,z2);
        glVertex3f(x2,y1,z2);

        glColor3f(1.0f,1.0f,1.0f);    // Color White
        glVertex3f(x2,y2,z1);    // BACK
        glVertex3f(x1,y2,z1);
        glVertex3f(x1,y1,z1);
        glVertex3f(x2,y1,z1);

        glColor3f(1.0f,1.0f,1.0f);    // Color White
        glVertex3f(x2, y2,z2);    // RIGHT
        glVertex3f(x1, y2,z2);
        glVertex3f(x1, y2,z1);
        glVertex3f(x2, y2,z1);

        glColor3f(1.0f,1.0f,1.0f);    // Color White
        glVertex3f(x2,y1,z1);    // LEFT
        glVertex3f(x1,y1,z1);
        glVertex3f(x1,y1,z2);
        glVertex3f(x2,y1,z2);

        glColor3f(1.0f,1.0f,1.0f);    // Color White
        glVertex3f(x1,y2, z1);   // TOP
        glVertex3f(x1,y2,z2);
        glVertex3f(x1,y1,z2);
        glVertex3f(x1,y1,z1);

        glColor3f(1.0f,1.0f,1.0f);    // Color White
        glVertex3f(x2,y2,z1);    // BOTTOM
        glVertex3f(x2,y2,z2);
        glVertex3f(x2,y1,z2);
        glVertex3f(x2,y1,z1);
    glEnd();            // End Drawing The Cube
}

void DrawPhone(void)
{
    float x1 = 0.0f;
    float x2 = 2.0f;
    float y1 = 0.0f;
    float y2 = 1.0f;
    float z1 = 0.0f;
    float z2 = 0.2f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);


    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-10.5);
    glRotatef(xRotated,1.0,0.0,0.0);

    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);

    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);

    // DRAW PHONE HERE
    DrawCube(x1, x2, y1, y2, z1, z2);
    DrawSemiCircle(0,0,0,1,1000,0,1000,0,0,0,1);

    glFlush();
}


void animation(void)
{
    yRotated += 0.01;
    xRotated += 0.02;
    DrawPhone();
}


void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0

    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void render(void) {
    DrawSemiCircle(0,0,0,1, 1000, 0, 1000, 0,0,0,1);
}


int main (int argc, char** argv) {
    glutInit(&argc, argv);
    //we initizlilze the glut. functions
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow(argv[0]);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    init();
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    //Set the function for the animation.
    glutIdleFunc(animation);
    glutMainLoop();
    return 0;
}
