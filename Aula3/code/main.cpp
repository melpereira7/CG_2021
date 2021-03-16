#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alpha = M_PI / 4, beta = M_PI / 4;
float cameraRadius = 5.0f;

float radius = 0.5f;
float height = 1.0f;
int slices = 25;
int stacks = 10;

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

void drawCylinder(float radius, float height, int slices) {

	float angleC = 0, deslocA = 2*M_PI / slices;
	float halfH = height / 2;

	glPolygonMode(GL_FRONT, GL_LINE);

	for (int i = 0; i < slices; i++) {

		glBegin(GL_TRIANGLES);


		glColor3f(0.5f, 0.5f, 0.8f);
			glVertex3f(0.0f, halfH, 0.0f);
			glVertex3f(sin(angleC) * radius, halfH, cos(angleC) * radius);
			glVertex3f(sin(angleC + deslocA) * radius, halfH, cos(angleC + deslocA) * radius);
			
		glColor3f(0.8f, 0.5f, 0.8f);
			glVertex3f(sin(angleC + deslocA) * radius, halfH, cos(angleC + deslocA) * radius);
			glVertex3f(sin(angleC) * radius, halfH, cos(angleC) * radius);
			glVertex3f(sin(angleC) * radius, -halfH, cos(angleC) * radius);
		
			glVertex3f(sin(angleC + deslocA) * radius, halfH, cos(angleC + deslocA) * radius);
			glVertex3f(sin(angleC) * radius, -halfH, cos(angleC) * radius);
			glVertex3f(sin(angleC + deslocA) * radius, -halfH, cos(angleC + deslocA) * radius);
			
		glColor3f(0.5f, 0.5f, 0.8f);
			glVertex3f(0.0f, -halfH, 0.0f);
			glVertex3f(sin(angleC + deslocA) * radius, -halfH, cos(angleC + deslocA) * radius);
			glVertex3f(sin(angleC) * radius, -halfH, cos(angleC) * radius);

		glEnd();
		angleC += deslocA;
	}

}

void drawCone(float radius, float height, int slices, int stacks) {
	float angleC = 0, deslocA = 2 * M_PI / slices;
	float hStack = height / stacks;
	float rStack = radius / stacks;

	glPolygonMode(GL_FRONT, GL_LINE);

	for (int i = 0; i < slices; i++) {

		float base = 0.0f;
		glBegin(GL_TRIANGLES);

		glColor3f(0.5f, 0.5f, 0.8f);

			glVertex3f(0.0f, base, 0.0f);
			glVertex3f(sin(angleC + deslocA) * radius, base, cos(angleC + deslocA) * radius);
			glVertex3f(sin(angleC) * radius, base, cos(angleC) * radius);

		for (int j = 0; j < stacks; j++) {

			float rInferior = radius - rStack * j;
			float rSuperior = radius - rStack * (j + 1);

			glColor3f(0.8f, 0.5f, 0.8f);

				glVertex3f(sin(angleC) * rInferior, base , cos(angleC) * rInferior);
				glVertex3f(sin(angleC + deslocA) * rInferior, base, cos(angleC + deslocA) * rInferior);
				glVertex3f(sin(angleC + deslocA) * rSuperior, base + hStack, cos(angleC + deslocA) * rSuperior);

				glVertex3f(sin(angleC) * rInferior, base, cos(angleC) * rInferior);
				glVertex3f(sin(angleC + deslocA) * rSuperior, base + hStack, cos(angleC + deslocA) * rSuperior);
				glVertex3f(sin(angleC) * rSuperior, base + hStack, cos(angleC) * rSuperior);

				base += hStack;
		}

		glEnd();
		angleC += deslocA;
	}
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(sin(beta) * cos(alpha) * cameraRadius, sin(alpha)*cameraRadius,cos(beta)*cos(alpha)*cameraRadius,
		      0.0f,0.0f,0.0f,
			  0.0f,1.0f,0.0f);
/*
	glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-100.0f, 0.0f, 0.0f);
			glVertex3f(100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, -100.0f, 0.0f);
			glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, -100.0f);
			glVertex3f(0.0f, 0.0f, 100.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
	glEnd();
	*/

// put the geometric transformations here
	glutPostRedisplay();

// put drawing instructions here
	drawCylinder(radius, height, slices);
	drawCone(radius,height,slices,stacks);

	// End of frame
	glutSwapBuffers();
}


// write function to process keyboard events
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		cameraRadius--;
		break;
	case 's':
		cameraRadius++;
		break;
	}
}

void keyboardSpecial(int key_code, int x, int y) {
	switch (key_code) {
	case GLUT_KEY_LEFT:
		beta -= 0.1f;
		break;
	case GLUT_KEY_RIGHT:
		beta += 0.1f;
		break;
	case GLUT_KEY_UP:
		alpha += 0.1f;
		break;
	case GLUT_KEY_DOWN:
		alpha -= 0.1f;
		break;
	}
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

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
