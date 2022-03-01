#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include "tinyxml2.h"
#include "Astro.h"
#include <list>

using namespace std;
using namespace tinyxml2;

float cx=0.0f;
float cy=0.0f;
float cz=0.0f;
float angle = 0.0f;
float angle2 = 0.0f;
float size = 1.0f;

list< Astro > lista;

// angle of rotation for the camera direction
float angle_=0.0;
// actual vector representing the camera's direction
float lx=2.5f,ly=0.0f,lz=0.0f;
// XZ position of the camera
float x=2.5f,y=0.0f,z=13.0f;

void readGroup(XMLElement *pElement, Astro astro);

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
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
	gluPerspective(45.0f, ratio, 0.10f, 100.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void draw(Astro astro, boolean b){
    float x,y,z;
    glPolygonMode(GL_FRONT, GL_FILL);

    glPushMatrix();
    glColor3f(astro.getRed(),astro.getGreen(),astro.getBlue());
    glTranslatef(astro.getTranslateX(), astro.getTranslateY(), astro.getTranslateZ());
    glScalef(astro.getScaleX(), astro.getScaleY(), astro.getScaleZ());
    glRotatef(astro.getAngle(), astro.getRotateX(), astro.getRotateY(), astro.getRotateZ());
    list <float> points = astro.getPoints();
    glBegin(GL_TRIANGLES);
        for(auto itPoints = points.begin(); itPoints != points.end(); itPoints++) {
            x = *(itPoints++);
            y = *(itPoints++);
            z = *itPoints;
            glVertex3f(x, y, z);
        }
    glEnd();

    for(Astro lua : astro.getLuas()){
        draw(lua, FALSE);
    }

    if(b) {
        glRotatef(90.0f,1,0,0);
        glColor3f(0.5f,0.5f,0.5f);
        glutSolidTorus(0.1,3.5,20,20);
    }
    glPopMatrix();
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
    gluLookAt(x,y,z,lx,ly,lz,0.0f,1.0f,0.0f);


    /*  glBegin(GL_LINES);
            // X axis in red
            glColor3f(1.0f, 0.0f, 0.0f);
                glVertex3f(-100.0f, 0.0f, 0.0f);
                glVertex3f(5000000.0f, 0.0f, 0.0f);
            // Y Axis in Green
            glColor3f(0.0f, 1.0f, 0.0f);
                glVertex3f(0.0f, -100.0f, 0.0f);
                glVertex3f(0.0f, 5000000.0f, 0.0f);
            // Z Axis in Blue
            glColor3f(0.0f, 0.0f, 1.0f);
                glVertex3f(0.0f, 0.0f, -100.0f);
                glVertex3f(0.0f, 0.0f, 5000000.0f);
            glColor3f(0.0f, 0.0f, 0.0f);
        glEnd(); */


	// put the geometric transformations here
    glTranslatef(cx, cy, cz);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glRotatef(angle2, 0.0f, 0.0f, 1.0f);
    glScalef(size, size, size);

    boolean b = false;
    int count = 0;

	// put drawing instructions here
    for(Astro a : lista) {
        draw(a, b);
        count++;
        if (count==6) b = true;
        else b =  false;
    }



	// End of frame
	glutSwapBuffers();
}

Astro readGroup(XMLElement *group, Astro astro, boolean original) {
    Astro lua = Astro();
    XMLElement *colour = group->FirstChildElement("colour");
    if (colour != nullptr) {
        float r = atof(colour->Attribute("R"));
        float g = atof(colour->Attribute("G"));
        float b = atof(colour->Attribute("B"));
        printf("colour-%f %f %f\n",r,g,b);
        lua.setColor(r,g,b);
    }
    XMLElement *translate = group->FirstChildElement("translate");
    if (translate != nullptr) {
        float tx = atof(translate->Attribute("X"));
        float ty = atof(translate->Attribute("Y"));
        float tz = atof(translate->Attribute("Z"));
        if(tx>0)
            tx = log(tx)-8;
        if (ty>0)
            ty = log(ty)-8;
        if (tz>0)
            tz = log(tz)-8;
        printf("translate-%f %f %f\n",tx,ty,tz);
        lua.setTranslate(tx, ty, tz);
    }
    XMLElement *rotate = group->FirstChildElement("rotate");
    if (rotate != nullptr) {
        float a = atof(rotate->Attribute("angle"));
        float rx = atof(rotate->Attribute("axisX"));
        float ry = atof(rotate->Attribute("axisY"));
        float rz = atof(rotate->Attribute("axisZ"));
        printf("rotate-%f %f %f\n",rx,ry,rz);
        lua.setRotate(a, rx, ry, rz);
    }
    XMLElement *scale = group->FirstChildElement("scale");
    if (scale != nullptr) {
        float sx = atof(scale->Attribute("X"));
        float sy = atof(scale->Attribute("Y"));
        float sz = atof(scale->Attribute("Z"));
        printf("scale-%f %f %f\n",sx,sy,sz);
        lua.setScale(sx, sy, sz);
    }
    XMLElement *models = group->FirstChildElement("models");
    for (XMLElement *model = models->FirstChildElement("model");
         model != nullptr; model = model->NextSiblingElement("model")) {
         string file3d = model->Attribute("file");
         lua.setFilename(file3d);
         lua.readFile();
    }
    if(original){
        astro=lua;
    }else{
        astro.add(lua);
    }

    for(XMLElement *childGroup = group->FirstChildElement("group");
        childGroup!=nullptr; childGroup = childGroup->NextSiblingElement("group")){
        astro = readGroup(childGroup, astro, FALSE);
    }
    return astro;
}

bool readXML(string file) {
	XMLDocument doc;
	XMLElement* firstElem;
	printf("%s\n",file.c_str());
	if (!doc.LoadFile(file.c_str())) {
		firstElem = doc.FirstChildElement("scene");
		for (XMLElement* group = firstElem->FirstChildElement("group"); group != nullptr; group = group->NextSiblingElement("group")) {
		    Astro astro = Astro();
		    astro = readGroup(group, astro, TRUE);
		    lista.push_back(astro);
		}
		return true;
	}
	else {
		cout << "Ocorreu um erro na leitura do ficheiro XML." << endl;
	    return false;
	}

}

void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {
        case GLUT_KEY_LEFT :
            x -= 0.05f;
            lx -= 0.05f;
            break;
        case GLUT_KEY_RIGHT :
            x += 0.05f;
            lx += 0.05f;
            break;
        case GLUT_KEY_UP :
            z -= 0.05f;
            lz -= 0.05f;
            break;
        case GLUT_KEY_DOWN :
            z += 0.05f;
            lz += 0.05f;
            break;
        case GLUT_KEY_PAGE_UP:
            y += 0.05f;
            ly += 0.05f;
            break;
        case GLUT_KEY_PAGE_DOWN:
            y -= 0.05f;
            ly -= 0.05f;
            break;
    }

    glutPostRedisplay();
}

// write function to process keyboard events
void keyFunction(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'x':	cx -= 0.2f; break;

        case 'X':	cx += 0.2f; break;

        case 'y':	cy -= 0.2f; break;

        case 'Y':	cy += 0.2f; break;

        case 'z':	cz -= 0.2f; break;

        case 'Z':	cz += 0.2f; break;

        case 'r':	angle -= 10.0f; break;

        case 'R':	angle += 10.0f; break;

        case 'T':	angle2 += 10.0f; break;

        case 't':	angle2 -= 10.0f; break;

        case '+':	size += 0.05f; break;

        case '-':	size -= 0.05f; break;

    }

    if (size > 0)
        glFrontFace(GL_CCW);
    else
        glFrontFace(GL_CW);

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    if(argc>2){cout << "Too many arguments! Expected 1 argument!" << endl; return -1;}
    if(argc<2){cout << "Not enough arguments! Expected 1 argument!" << endl; return -1;}

    string path = "../";
    string file = argv[1];

    if(!readXML(path + file + ".xml")){
        cout << "Ficheiro nao lido." << endl;
        return -1;
    }

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

    glutKeyboardFunc(keyFunction);
    glutSpecialFunc(processSpecialKeys);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
