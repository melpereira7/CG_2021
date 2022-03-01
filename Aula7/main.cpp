#include "IL/il.h"
#define GL_SILENCE_DEPRECATION
#include<stdio.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#endif


#include <vector>
#include <cstdlib>
#include <iostream>
#include <vector>
#define ARVORES 400

using namespace std;

GLuint buffers[1];
int startX, startY, tracking = 0;


unsigned int t;
int tw, th;
ILubyte* imageData;

/* Guiao 5 */
struct Ponto {
    float x;
    float y;
    float z;
};

vector<Ponto> pontos;

float alpha = 0.0f, beta = 0.5f, radius = 200.0f;
float camX = 00, camY = 5, camZ = 40;
float r = 50;
float ri = 35;
float rc = 15;
float deslocacao = 0;

float h(int i, int j) {
    return imageData[i * tw + j];
}

float hf(float x, float z) {
    x += tw / 2.0f;
    z += tw / 2.0f;
    int x1 = floor(x);
    float x2 = x1 + 1;
    int z1 = floor(z);
    float z2 = z1 + 1;
    float fz = z - z1;
    float h_x1_z = h(x1, z1) * (1 - fz) + h(x1, z2) * fz;
    float h_x2_z = h(x2, z1) * (1 - fz) + h(x2, z2) * fz;
    float fx = x - x1;
    float height_xz = h_x1_z * (1 - fx) + h_x2_z * fx;
    return height_xz;
}

void drawDonut() {

    glPushMatrix();
    glTranslatef(0.0, 0.6, 0.0);
    glColor3f(1.0f, 0.0f, 1.0f);
    glTranslatef(0, hf(0, 0), 0);
    glutSolidTorus(0.5, 1.25, 8, 16);
    glPopMatrix();
}

void drawTrees() {

    for (int i = 0; i < pontos.size(); i++) {

        // Tronco
        glPushMatrix();
        glTranslatef(pontos[i].x, pontos[i].y, pontos[i].z);
        glRotatef(90, -1, 0, 0);
        glColor3f(1, 0.5, 0);
        glutSolidCone(1, 10, 6, 2);
        glPopMatrix();
        // Folhas
        glPushMatrix();
        glTranslatef(pontos[i].x, pontos[i].y + 5, pontos[i].z);
        glRotatef(90, -1, 0, 0);
        glColor3f(0.02, 0.41, 0.01);
        glutSolidCone(3, 10, 6, 2);
        glPopMatrix();
    }
}

void drawTeaPotBigCircle(int tPots) {
    float angle = 0.0f;
    float z;
    float x;
    for (int i = 0;i < tPots; i++) {
        angle = i * ((2.0f * M_PI) / tPots) + deslocacao * 0.5f;
        x = ri * sin(angle);
        z = ri * cos(angle);
        glPushMatrix();
        glTranslatef(x, hf(x, z) + 2, z);
        glRotatef(angle * (180 / M_PI), 0, 1, 0);
        glColor3f(1, 0, 0);
        glutSolidTeapot(2);
        glPopMatrix();

    }
}

void drawTeaPotSmallCircle(int tPots) {
    float angle = 0;
    float z;
    float x;
    for (int i = 0; i < tPots; i++) {
        angle = i * ((2 * M_PI) / tPots) - deslocacao;
        x = rc * sin(angle);
        z = rc * cos(angle);
        glPushMatrix();
        glTranslatef(x, hf(x, z) + 2, z);
        glRotatef((angle - M_PI / 2) * (180 / M_PI), 0, 1, 0);
        glColor3f(0, 0, 1);
        glutSolidTeapot(2);
        glPopMatrix();

    }
}

void calculaPontos() {

    float alpha;
    float rr;
    float x, z;
    int i = 0;
    Ponto p;
    while (i < ARVORES) {

        rr = rand() * (sqrt(2 * pow(100, 2))) / RAND_MAX;
        alpha = rand() * 2.0 * M_PI / RAND_MAX;

        x = sin(alpha) * (rr + r);
        z = cos(alpha) * (rr + r);

        if (fabs(x) < 100 && fabs(z) < 100) {
            p.x = x;
            p.y = hf(z, x);
            p.z = z;

            pontos.push_back(p);
            i++;
        }
    }
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective
    gluPerspective(45, ratio, 1, 1000);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void drawTerreno() {
    // colocar aqui o código de desnho do terreno usando VBOs com TRIANGLE_STRIPS

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    for (int i = 0;i < th - 1;i++) {

        glColor3f(0.26, 0.66, 0.02);
        glDrawArrays(GL_TRIANGLE_STRIP, tw * 2 * i, tw * 2);
    }
}

void drawGrid(int rx, int rz, float* array) {
    int c = 0;

    for (float i = 0;i < th - 1;i++) {
        for (float j = 0;j < tw;j++) {
            array[c++] = j - rx;
            array[c++] = h(i, j);
            array[c++] = i - rz;

            array[c++] = j - rx;
            array[c++] = h(i + 1, j);
            array[c++] = i + 1 - rz;
        }
    }
}

void terreno() {

    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring)"terreno.jpg");
    ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    imageData = ilGetData();

    int rx = tw / 2.0f;
    int rz = th / 2.0f;

    int size = 2 * 3 * tw * th;
    float* array = new float[size];

    drawGrid(rx, rz, array);
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), array, GL_STATIC_DRAW);

}

void renderScene(void) {

    //float pos[4] = { -1.0, 1.0, 1.0, 0.0 };

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(camX, camY + hf(camZ, camX), camZ,
        camX + sin(alpha), camY + hf(camZ, camX), camZ + cos(alpha),
        0.0f, 1.0f, 0.0f);

    drawTerreno();
    drawTrees();
    drawDonut();
    drawTeaPotBigCircle(16);
    drawTeaPotSmallCircle(8);
    deslocacao += 0.03;

    // End of frame
    glutSwapBuffers();
}

// escrever fun��o de processamento do teclado
void processKeys(unsigned char key, int xx, int yy) {
    float dx, dy = 0, dz, rx, rz;
    float upx = 0, upy = 1, upz = 0;
    float speed = 2;
    switch (key) {
        case 'w': {
            dx = sin(alpha);
            dz = cos(alpha);
            camX = camX + speed * dx;
            camZ = camZ + speed * dz;
            break;
        }
        case 's': {
            dx = sin(alpha);
            dz = cos(alpha);
            camX = camX + (-speed) * dx;
            camZ = camZ + (-speed) * dz;

            break;
        }
        case 'a': {
            dx = sin(alpha);
            dz = cos(alpha);
            rx = dy * upz - cos(alpha) * upy;
            rz = sin(alpha) * upy - dy * upx;
            camX = camX + (-speed) * rx;
            camZ = camZ + (-speed) * rz;

            break;
        }
        case 'd': {
            dx = sin(alpha);
            dz = cos(alpha);
            rx = dy * upz - cos(alpha) * upy;
            rz = sin(alpha) * upy - dy * upx;
            camX = camX + speed * rx;
            camZ = camZ + speed * rz;

            break;
        }
    }

}

void processSpecialKeys(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            alpha -= 0.1; break;
        case GLUT_KEY_LEFT:
            alpha += 0.1; break;
    }
}

void init() {
    // Colocar aqui load da imagem que representa o mapa de alturas

    glEnableClientState(GL_VERTEX_ARRAY);

    ilInit();
#ifndef __APPLE__
    glewInit();
#endif
    terreno();
    // alguns settings para OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    calculaPontos();
}

int main(int argc, char** argv) {


    // inicializa��o
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("CG@DI-UM");


    // registo de fun��es
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    // p�r aqui registo da fun��es do teclado e rato

    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    init();

    // entrar no ciclo do GLUT
    glutMainLoop();

    return 0;
}
