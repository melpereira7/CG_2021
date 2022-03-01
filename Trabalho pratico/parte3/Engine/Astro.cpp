#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <GL/glew.h>

#include "Astro.h"

Astro::Astro() {
    filename = "";
    rotateAngle = 0.0f;
    translateX = 0.0f;
    translateY = 0.0f;
    translateZ = 0.0f;
    rotateX = 0.0f;
    rotateY = 0.0f;
    rotateZ = 0.0f;
    scaleX = 1.0f;
    scaleY = 1.0f;
    scaleZ = 1.0f;
    red = 0.0f;
    green = 0.0f;
    blue = 0.0f;
    anel = false;
    time = 0.1;
    buffer =  (GLuint*) malloc(sizeof(GLuint));
}

std::string Astro::getFilename() { return filename; }

std::vector<float> Astro::getPoints() { return points; }

std::vector<float *> Astro::getTranslate() { return translate; }

float Astro::getAngle() { return rotateAngle; }

float Astro::getRotateX() { return rotateX; }

float Astro::getRotateY() { return rotateY; }

float Astro::getRotateZ() { return rotateZ; }

float Astro::getScaleX() { return scaleX; }

float Astro::getScaleY() { return scaleY; }

float Astro::getScaleZ() { return scaleZ; }

float Astro::getRed() { return red; }

float Astro::getGreen() { return green; }

float Astro::getBlue() { return blue; }

bool Astro::getAnel() { return anel; }

float Astro::getTranslateX(){ return translateX; }
float Astro::getTranslateY(){ return translateY; }
float Astro::getTranslateZ(){ return translateZ; }

std::list<Astro> Astro::getLuas() { return luas; }

float Astro::getTime() { return Astro::time; }

void Astro::setFilename(const std::string &filename) {
    Astro::filename = filename;
}

void Astro::setColor(float red, float green, float blue) {
    Astro::red = red;
    Astro::green = green;
    Astro::blue = blue;
}

void Astro::setRotate(float angle, float x, float y, float z) {
    Astro::rotateAngle = angle;
    Astro::rotateX = x;
    Astro::rotateY = y;
    Astro::rotateZ = z;
}

void Astro::setScale(float x, float y, float z) {
    Astro::scaleX = x;
    Astro::scaleY = y;
    Astro::scaleZ = z;
}

void Astro::setAnel(bool anel) {
    Astro::anel = anel;
}

void Astro::setTime(float time) {
    Astro::time = time;
}

void Astro::setTranslate(float x, float y, float z) {
    Astro::translateX = x;
    Astro::translateY = y;
    Astro::translateZ = z;
}

void Astro::setPointsTranslate(std::vector<float *> translate) {
    Astro::translate = translate;
}

void Astro::readFile() {
    std::ifstream infile(filename);
    float x, y, z;

    if (!infile) {
        std::cout << "Ocorreu um erro na leitura do ficheiro." << std::endl;
        return;
    }

    while (infile >> x >> y >> z) {
        points.push_back(x);
        points.push_back(y);
        points.push_back(z);
    }
}

void Astro::add(Astro astro) {
    luas.push_back(astro);
}

void Astro::makeVBO() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glGenBuffers(1, buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);
}

void Astro::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, points.size());
} //glgeterror()
