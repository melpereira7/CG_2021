#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>

#endif



#include <cmath>
#include <iostream>
#include <string>
#include "tinyxml2.h"
#include "Objeto.h"
#include <vector>

using namespace std;
using namespace tinyxml2;

float cx = 0.0f;
float cy = 0.0f;
float cz = 0.0f;
float angle = 0.0f;
float angle2 = 0.0f;
float size = 1.0f;

vector<Objeto> lista;
int point_count = 0;

string tipoLuz;
float luzx,luzy,luzz;

float alpha = 0.75f, beta = 1.0f;
float cameraRadius = 15.0f;

float xmove = 0;

float camX, camY, camZ;

float isPoint = 0.0;

void spherical2Cartesian() {

    camX = cameraRadius * cos(beta) * sin(alpha);
    camY = cameraRadius * sin(beta);
    camZ = cameraRadius * cos(beta) * cos(alpha);
}

void buildRotMatrix(float *x, float *y, float *z, float *m) {

    m[0] = x[0];
    m[1] = x[1];
    m[2] = x[2];
    m[3] = 0;
    m[4] = y[0];
    m[5] = y[1];
    m[6] = y[2];
    m[7] = 0;
    m[8] = z[0];
    m[9] = z[1];
    m[10] = z[2];
    m[11] = 0;
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void cross(float *a, float *b, float *res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(float *a) {

    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

    // catmull-rom matrix
    float m[4][4] = {{-0.5f, 1.5f, -1.5f, 0.5f},
                     {1.0f,  -2.5f, 2.0f, -0.5f},
                     {-0.5f, 0.0f, 0.5f,  0.0f},
                     {0.0f,  1.0f, 0.0f,  0.0f}};


    // Compute A = M * P
    float a[4][3];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            a[i][j] = m[i][0] * p0[j] + m[i][1] * p1[j] + m[i][2] * p2[j] + m[i][3] * p3[j];
        }
    }

    // Compute pos = T * A
    float mt[4] = {(float) pow(t, 3), (float) pow(t, 2), t, 1};
    for (int i = 0; i < 3; i++) {
        pos[i] = 0;
        for (int j = 0; j < 4; j++) {
            pos[i] += mt[j] * a[j][i];
        }
    }

    // Compute deriv = T' * A
    float d[4] = {(float) (3 * pow(t, 2)), 2 * t, 1, 0};
    for (int i = 0; i < 3; i++) {
        deriv[i] = 0;
        for (int j = 0; j < 4; j++) {
            deriv[i] += d[j] * a[j][i];
        }
    }
}

void getGlobalCatmullRomPoint(float gt, vector<float *> p, float *pos, float *deriv) {

    float t = gt * point_count; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + point_count - 1) % point_count;
    indices[1] = (indices[0] + 1) % point_count;
    indices[2] = (indices[1] + 1) % point_count;
    indices[3] = (indices[2] + 1) % point_count;

    getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}

void renderCatmullRomCurve(float time, vector<float *> pontosTranslate) {

    // draw curve using line segments with GL_LINE_LOOP
    glColor3f(.9f, .9f, .9f);
    glBegin(GL_LINE_LOOP);
    float pos[3];
    float deriv[3];

    for (int i = 0; i < 100; i++) {
        if(i%2)
            glColor3f(.3f, .3f, .3f);
        else
            glColor3f(.05f, 0.05f, 0.05f);
        getGlobalCatmullRomPoint(i/100.0f, pontosTranslate, pos, deriv);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();

}

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

void draw(Objeto objeto) {
    if(objeto.getTime() != 0) {
        float t = glutGet(GLUT_ELAPSED_TIME) % (int) (objeto.getTime() * 1000);
        float tempo = t / (objeto.getTime() * 1000.0);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glPushMatrix();

        if ((point_count = objeto.getTranslate().size()) > 0) {
            renderCatmullRomCurve(tempo, objeto.getTranslate());
            float X[3];
            static float Y[3] = {0, 1, 0};
            float Z[3];
            float pos[4];
            //glPushMatrix();
            getGlobalCatmullRomPoint(tempo, objeto.getTranslate(), pos, X);
            glTranslatef(pos[0], pos[1], pos[2]);

            cross(X, Y, Z);
            cross(Z, X, Y);
            normalize(X);
            normalize(Y);
            normalize(Z);
            float m[16];
            buildRotMatrix(X, Y, Z, m);
            glMultMatrixf(m);
        }
    }else{
        glTranslatef(objeto.getTranslateX(), objeto.getTranslateY(), objeto.getTranslateZ());
    }

    glColor3f(objeto.getRed(), objeto.getGreen(), objeto.getBlue());
    glScalef(objeto.getScaleX(), objeto.getScaleY(), objeto.getScaleZ());
    glRotatef(objeto.getAngle(), objeto.getRotateX(), objeto.getRotateY(), objeto.getRotateZ());

    objeto.draw();
    for (Objeto lua : objeto.getDependencias()) {
        draw(lua);
    }

    glPushMatrix();
    if (objeto.getAnel()) {
        glRotatef(90.0f, 1, 0, 0);
        glColor3f(0.5f, 0.5f, 0.5f);
        glutSolidTorus(0.1, 3.5, 20, 20);
    }

    glPopMatrix();
    glPopMatrix();
}

void renderScene(void) {

    // clear buffers
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

    GLfloat pos[4] = { luzx, luzy, luzz, isPoint };

    glLightfv(GL_LIGHT0,GL_POSITION,pos);

    // put drawing instructions here
    int i = 0;
    for (Objeto a : lista) {
        draw(a);
        i++;
    }

    // End of frame
    glutSwapBuffers();
}

Objeto readGroup(XMLElement *group, Objeto objeto, boolean original) {
    Objeto novo = Objeto();
    XMLElement *colour = group->FirstChildElement("colour");
    if (colour != nullptr) {
        float r = atof(colour->Attribute("R"));
        float g = atof(colour->Attribute("G"));
        float b = atof(colour->Attribute("B"));
        novo.setColor(r, g, b);
    }
    XMLElement *translate = group->FirstChildElement("translate");
    if (translate != nullptr) {
        float time = atof(translate->Attribute("time"));
        float tx = atof(translate->Attribute("X"));
        float ty = atof(translate->Attribute("Y"));
        float tz = atof(translate->Attribute("Z"));
        novo.setTime(time);

        if(time) {
            vector<float *> translatePoints;
            int i = 0;
            for (XMLElement *point = translate->FirstChildElement("point");
                 point != nullptr; point = point->NextSiblingElement("point")) {
                float px = atof(point->Attribute("X"));
                float py = atof(point->Attribute("Y"));
                float pz = atof(point->Attribute("Z"));
                float *pontos = new float[3];
                pontos[0] = px;
                pontos[1] = py;
                pontos[2] = pz;
                translatePoints.push_back(pontos);
                i++;
            }
            novo.setPointsTranslate(translatePoints);
        }else{
            novo.setTranslate(tx, ty, tz);
        }
    }
    XMLElement *rotate = group->FirstChildElement("rotate");
    if (rotate != nullptr) {
        float a = atof(rotate->Attribute("angle"));
        float rx = atof(rotate->Attribute("axisX"));
        float ry = atof(rotate->Attribute("axisY"));
        float rz = atof(rotate->Attribute("axisZ"));
        novo.setRotate(a, rx, ry, rz);
    }
    XMLElement *scale = group->FirstChildElement("scale");
    if (scale != nullptr) {
        float sx = atof(scale->Attribute("X"));
        float sy = atof(scale->Attribute("Y"));
        float sz = atof(scale->Attribute("Z"));
        novo.setScale(sx, sy, sz);
    }
    XMLElement *ring = group->FirstChildElement("ring");
    if (ring != nullptr) {
        novo.setAnel(TRUE);
    }
    XMLElement *models = group->FirstChildElement("models");
    for (XMLElement *model = models->FirstChildElement("model");
        model != nullptr; model = model->NextSiblingElement("model")) {
        string file3d = model->Attribute("file");
        novo.setFilename(file3d);
        if(model->Attribute("texture")) {
            string texFile = model->Attribute("texture");
            novo.setTexfilename(texFile);
        }
        novo.readFile();

        if(model->Attribute("diffR")) {
            string diffR = model->Attribute("diffR");
            novo.setDiffR(atof(diffR.c_str()));
        }
        if(model->Attribute("diffG")) {
            string diffG = model->Attribute("diffG");
            novo.setDiffG(atof(diffG.c_str()));
        }
        if(model->Attribute("diffB")) {
            string diffB = model->Attribute("diffB");
            novo.setDiffB(atof(diffB.c_str()));
        }
        if(model->Attribute("specR")) {
            string specR = model->Attribute("specR");
            novo.setSpecR(atof(specR.c_str()));
        }
        if(model->Attribute("specG")) {
            string specG = model->Attribute("specG");
            novo.setSpecG(atof(specG.c_str()));
        }
        if(model->Attribute("specB")) {
            string specB = model->Attribute("specB");
            novo.setSpecB(atof(specB.c_str()));
        }
        if(model->Attribute("emiR")) {
            string emiR = model->Attribute("emiR");
            novo.setEmiR(atof(emiR.c_str()));
        }
        if(model->Attribute("emiG")) {
            string emiG = model->Attribute("emiG");
            novo.setEmiG(atof(emiG.c_str()));
        }
        if(model->Attribute("emiB")) {
            string emiB = model->Attribute("emiB");
            novo.setEmiB(atof(emiB.c_str()));
        }
        if(model->Attribute("ambR")) {
            string ambR = model->Attribute("ambR");
            novo.setAmbR(atof(ambR.c_str()));
        }
        if(model->Attribute("ambG")) {
            string ambG = model->Attribute("ambG");
            novo.setAmbG(atof(ambG.c_str()));
        }
        if(model->Attribute("ambB")) {
            string ambB = model->Attribute("ambB");
            novo.setAmbB(atof(ambB.c_str()));
        }
    }
    if (original) {
        objeto = novo;
    } else {
        objeto.add(novo);
    }

    for (XMLElement *childGroup = group->FirstChildElement("group");
         childGroup != nullptr; childGroup = childGroup->NextSiblingElement("group")) {
        objeto = readGroup(childGroup, objeto, FALSE);
    }
    return objeto;
}

bool readXML(string file) {
    XMLDocument doc;
    XMLElement *firstElem;
    if (!doc.LoadFile(file.c_str())) {
        firstElem = doc.FirstChildElement("scene");
        XMLElement *lights = firstElem->FirstChildElement("lights");
        if(lights){
            for (XMLElement *light = lights->FirstChildElement("light");
                light != nullptr; light = light->NextSiblingElement("light")) {
                tipoLuz = light->Attribute("type");
                if(tipoLuz=="POINT") isPoint=0.0; else isPoint=1.0;
                luzx = atof(light->Attribute("posX"));
                luzy = atof(light->Attribute("posY"));
                luzx = atof(light->Attribute("posZ"));
            }

            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
        }

        for (XMLElement *group = firstElem->FirstChildElement("group");
            group != nullptr; group = group->NextSiblingElement("group")) {
            Objeto astro = Objeto();
            astro = readGroup(group, astro, TRUE);
            lista.push_back(astro);
        }

        return true;
    } else {
        cout << "Ocorreu um erro na leitura do ficheiro XML." << endl;
        return false;
    }

}

void processSpecialKeys(int key, int xx, int yy) {
    switch (key) {

        case GLUT_KEY_RIGHT:
            alpha -= 0.1;
            break;

        case GLUT_KEY_LEFT:
            alpha += 0.1;
            break;

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

        case GLUT_KEY_PAGE_DOWN:
            cameraRadius -= 1.0f;
            if (cameraRadius < 1.0f)
                cameraRadius = 1.0f;
            break;

        case GLUT_KEY_PAGE_UP:
            cameraRadius += 1.0f;
            break;
    }
    spherical2Cartesian();
    glutPostRedisplay();

}

void keyFunction(unsigned char key, int xx, int yy) {

    switch (key) {
        case 'w':
            cameraRadius--;
            break;
        case 's':
            cameraRadius++;
            break;
        case 'a':
            xmove += 0.1f;
            break;
        case 'd':
            xmove -= 0.1f;
            break;
    }

    glutPostRedisplay();
}

void initGL() {

// alguns settings para OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE_MODE);

    glEnable(GL_RESCALE_NORMAL);

    spherical2Cartesian();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glClearColor(0, 0, 0, 0);

    glEnable(GL_TEXTURE_2D);

}

int main(int argc, char **argv) {
    if (argc > 2) {
        cout << "Too many arguments! Expected 1 argument!" << endl;
        return -1;
    }
    if (argc < 2) {
        cout << "Not enough arguments! Expected 1 argument!" << endl;
        return -1;
    }

    string path = "../";
    string file = argv[1];


    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glutKeyboardFunc(keyFunction);
    glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
    glewInit();
    initGL();

    if (!readXML(path + file + ".xml")) {
        cout << "Ficheiro nao lido." << endl;
        return -1;
    }



    spherical2Cartesian();

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
