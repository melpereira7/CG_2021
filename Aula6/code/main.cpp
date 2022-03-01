#include<stdio.h>
#include<stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <IL/il.h>
#include <GL/glew.h>
#include <GL/glut.h>
#endif


#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <vector>

using namespace std;


GLuint buffer[1];

unsigned int t, tw, th;
unsigned char *imageData;
float* vertexB;

float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

int alpha = 0, beta = 45, r = 50;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawTerrain() {
    // colocar aqui o código de desenho do terreno usando VBOs com TRIANGLE_STRIPS
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    int h;
    for (int i = 0; i < th - 1; i++) {
        glDrawArrays(GL_LINE_STRIP, tw * 2 * i, tw * 2);
    }
}

void renderScene(void) {

    float pos[4] = {-1.0, 1.0, 1.0, 0.0};

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

    drawTerrain();
    // just so that it renders something before the terrain is built
    // to erase when the terrain is ready

// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy) {

// put code to process regular keys in here
}

void processMouseButtons(int button, int state, int xx, int yy) {
	
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}

void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
}

float h(int i, int j) {
    float height = imageData[i * tw + j];
    return height * (60.0 / 255.0);
}

void generatePoints() {
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring)"terreno.jpg");
    ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    if(tw==256 && th==256)
        imageData = ilGetData();

    int size = tw * 2 * 3 * (th - 1);
    vertexB = (float*)malloc(sizeof(float) * size);
    int v = 0;

    float rx = (tw - 1) / 2.0;
    float rz = (th - 1) / 2.0;


    for (float i = 0; i < th - 1; i++) {
        for (float j = 0; j < tw; j++) {
            vertexB[v++] = j - rx;
            vertexB[v++] = h(i, j);
            vertexB[v++] = i - rz;

            vertexB[v++] = j - rx;
            vertexB[v++] = h(i + 1, j);
            vertexB[v++] = i + 1 - rz;
        }
    }
    glGenBuffers(1, buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertexB, GL_STATIC_DRAW);

}

void init() {

// 	Load the height map "terreno.jpg"
    glEnableClientState(GL_VERTEX_ARRAY);
    ilInit();
    glewInit();

    generatePoints();
// 	Build the vertex arrays

// 	OpenGL settings
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("CG@DI-UM");

// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	glewInit();
    ilInit();

    init();

// enter GLUT's main cycle
	glutMainLoop();

	
	return 0;
}

