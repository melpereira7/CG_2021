#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

float tx = 0.0, ty = 0.0, tz = 0.0,
		rx = 0.0, ry = 0.0, rz = 0.0,
		sx = 1.0, sy = 1.0, sz = 1.0;
float angle = 0.0f;

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


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	//gluLookAt(px, py, pz, lx, ly, lz, ux, uy, uz);
	// px,py,pz – camera position
	// lx,ly,lz – look at point
	// ux,uy,uz – camera tilt, by default use (0.0, 1.0, 0.0)

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


// put the geometric transformations here
	glTranslatef(tx, ty, tz); // moves the object
	glRotatef(angle, rx, ry, rz); // angle is in degrees
	glScalef(sx, sy, sz); // scale factors for each axis
	glutPostRedisplay();


// put drawing instructions here
	//glPolygonMode(GL_FRONT ou GL_BACK ou GL_FRONT_AND_BACK , GL_FILL ou GL_LINE ou GL_POINT);
	
	glBegin(GL_TRIANGLES);
		//base triangles
		glColor3f(0.1f, 0.1f, 0.1f);
			glVertex3f(1.0f, 0.0f, 1.0f);
			glVertex3f(-1.0f, 0.0f, 1.0f);
			glVertex3f(1.0f, 0.0f, -1.0f);
		glColor3f(0.2f, 0.2f, 0.2f);
			glVertex3f(-1.0f, 0.0f, 1.0f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(1.0f, 0.0f, -1.0f);
		//triangulo lado dreito
		glColor3f(0.8f, 0.5f, 0.5f);
			glVertex3f(1.0f, 0.0f, -1.0f);
			glVertex3f(0.0f, 2.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, 1.0f);
		//triangulo atras
		glColor3f(0.8f, 0.8f, 0.5f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(0.0f, 2.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, -1.0f);
		//trinagulo lado esquerdo
		glColor3f(0.5f, 0.8f, 0.5f);
			glVertex3f(-1.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 2.0f, 0.0f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
		//triangulo frente
		glColor3f(0.5f, 0.5f, 0.8f);
			glVertex3f(1.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 2.0f, 0.0f);
			glVertex3f(-1.0f, 0.0f, 1.0f);	
	glColor3f(0.0f, 0.0f, 0.0f);
	glEnd();

	// End of frame
	glutSwapBuffers();
}

// write function to process keyboard events
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a' : //translação no eixo dos x para a esquerda
		tx -= 0.1;
		break;
	case 'd': //translação no eixo dos x para a direita
		tx += 0.1;
		break;
	case 'w': //translação no eixo dos y para cima
		ty += 0.1;
		break;
	case 's': //translação no eixo dos y para baixo
		ty -= 0.1;
		break;
	case 'q': //translação no eixo dos z para a esquerda
		tz += 0.1f;
		break;
	case 'e': //translação no eixo dos z para a direita
		tz -= 0.1f;
		break;
	}
}

void keyboardSpecial(int key_code, int x, int y) {
	switch (key_code) {
	case GLUT_KEY_LEFT: //rotação no eixo dos y para a esquerda
		ry += 1.0f;
		angle--;
		break;
	case GLUT_KEY_RIGHT: //rotação no eixo dos y para a direita
		ry += 1.0f;
		angle++;
		break;
	case GLUT_KEY_UP: //escala maior no eixo dos y 
		sy += 0.1f;
		break;
	case GLUT_KEY_DOWN: //escala menor no eixo dos y 
		sy -= 0.1f;
		break;
	}
}

//void mouse(int button, int state, int x, int y) {}
//void mouseMotion(int x, int y) {}


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
	//glutMouseFunc(mouse);
	//glutMotionFunc(mouseMotion);
	//glutPassiveMotionFunc(mouseMotion);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT ou GL_BACK) -- aletar qual a face que queremos eliminar no cull_face
	//glFrontFace(GL_CW ou GL_CCW) -- alterar ordem de escrita dos vertices
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
