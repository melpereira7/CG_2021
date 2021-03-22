#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <tuple>
#include <list>
#include <vector>

using namespace std;

float alfa = 0.0f, beta = 0.5f, radius = 200.0f;
float camX, camY, camZ;

float alphaC = 0.0f;
float alphaI = 2*M_PI;


vector<tuple<double,double>> pontos;

void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void generateTrees(int n, int r) {
    for(int i=0; i<n; i++){
        double x = (rand()/(RAND_MAX/200))-100;
        double z = (rand()/(RAND_MAX/200))-100;

        if(sqrt(pow(x,2)+pow(z,2))>r) {
            pontos.emplace_back(x,z);
        }else i--;
    }
}

void drawTrees(){

    for(auto it = pontos.begin(); it != pontos.end(); it++){
        double x = get<0>(*it);
        double z = get<1>(*it);

        glPushMatrix();
        glTranslatef(x, 0.0f, z);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.4f, 0.26f, 0.13f);
        glutSolidCone(0.5f, 5.0f, 10, 10);

        glTranslatef(0.0f, 0.0f, 1.0f);
        glColor3f(0.1f, 0.3f, 0.1f);
        glutSolidCone(2.0f, 7.0f, 10, 10);
        glPopMatrix();
    }

}

void drawCowboys(int n, double r){

    double deslocAngleCowboys = (2*M_PI)/n;

    for(int i=0; i<n; i++){
        double x = r*sin(i*deslocAngleCowboys);
        double z = r*cos(i*deslocAngleCowboys);

        glColor3f(0.0f, 0.0f, 1.0f);
        glPushMatrix();
        glTranslated(x,1.0,z);
        glRotated((-90+deslocAngleCowboys*i*180/M_PI),0.0,1.0,0.0);
        glutSolidTeapot(2.0f);
        glPopMatrix();
    }
}

void drawIndians(int n, double r){

    double deslocAngleIndians = (2*M_PI)/n;

    for(int i=0; i<n; i++){
        double x = r*sin(i*deslocAngleIndians);
        double z = r*cos(i*deslocAngleIndians);

        glColor3f(1.0f, 0.0f, 0.0f);
        glPushMatrix();
        glTranslated(x,1.0,z);
        glRotated((i*deslocAngleIndians*180/M_PI), 0.0, 1.0, 0.0);
        glutSolidTeapot(2.0f);
        glPopMatrix();
    }
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);

	glEnd();
	// End of frame


	// put code to draw scene in here
    glColor3f(1.0f, 0.5f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f,0.5f,0.0f);
    glutSolidTorus(1.0f, 3.0f, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glRotatef(alphaC,0.0f,1.0f,0.0f);
    drawCowboys(8,10);
    alphaC-=1.0f;
    glPopMatrix();

    glPushMatrix();
    glRotatef(alphaI,0.0f,1.0f,0.0f);
    drawIndians(16,35);
    alphaI+=1.0f;
    glPopMatrix();

    drawTrees();

	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");

// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	generateTrees(500, 45);

	spherical2Cartesian();

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
