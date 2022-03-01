#include <stdlib.h>

#define _USE_MATH_DEFINES



void drawTeapot(char *string);

#include <cmath>
#include <math.h>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

void drawPlane(float size, string fileName) {
    float halfSize = size / 2;

    ofstream file(fileName);
    if (file.is_open()) {

        file << halfSize	<< " " << 0.0 << " " << halfSize	<< "\n";
        file << halfSize	<< " " << 0.0 << " " << -halfSize   << "\n";
        file << -halfSize	<< " " << 0.0 << " " << halfSize	<< "\n";

        file << halfSize	<< " " << 0.0 << " " << -halfSize   << "\n";
        file << -halfSize	<< " " << 0.0 << " " << -halfSize   << "\n";
        file << -halfSize	<< " " << 0.0 << " " << halfSize    << "\n";

        file << "---\n";

        file << 0 << " " << 1 << " " << 0 << "\n";
        file << 0 << " " << 1 << " " << 0 << "\n";
        file << 0 << " " << 1 << " " << 0 << "\n";

        file << 0 << " " << 1 << " " << 0 << "\n";
        file << 0 << " " << 1 << " " << 0 << "\n";
        file << 0 << " " << 1 << " " << 0 << "\n";

        file << "---\n";

        file << 1 << " " << 1 << "\n";
        file << 1 << " " << 0 << "\n";
        file << 0 << " " << 1 << "\n";

        file << 1 << " " << 0 << "\n";
        file << 0 << " " << 0 << "\n";
        file << 0 << " " << 1 << "\n";

        file << "---\n";
    }
    file.close();
}

void drawBox(float x, float y, float z, int l, string fileName) { //TODO - rever texturas
    float xx = x / l;
    float yy = y / l;
    float zz = z / l;

    vector<float> n, t;

    ofstream file(fileName);
    if (file.is_open()) {
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < l; j++) {

                //Frente:
                file << i * xx		<< " " << j * yy		<< " " << z << "\n";
                n.push_back(0);
                n.push_back(0);
                n.push_back(1);
                t.push_back(i/l);
                t.push_back(j/l);

                file << i * xx + xx	<< " " << j * yy		<< " " << z << "\n";
                n.push_back(0);
                n.push_back(0);
                n.push_back(1);
                t.push_back((i+1)/l);
                t.push_back(j/l);

                file << i * xx + xx	<< " " << j * yy + yy	<< " " << z << "\n";
                n.push_back(0);
                n.push_back(0);
                n.push_back(1);
                t.push_back((i+1)/l);
                t.push_back((j+1)/l);


                file << i * xx		<< " " << j * yy		<< " " << z << "\n";
                n.push_back(0);
                n.push_back(0);
                n.push_back(1);
                t.push_back(i/l);
                t.push_back(j/l);

                file << i * xx + xx	<< " " << j * yy + yy	<< " " << z << "\n";
                n.push_back(0);
                n.push_back(0);
                n.push_back(1);
                t.push_back((1+i)/l);
                t.push_back((1+j)/l);

                file << i * xx		<< " " << j * yy + yy	<< " " << z << "\n";
                n.push_back(0);
                n.push_back(0);
                n.push_back(1);
                t.push_back(i/l);
                t.push_back((j+1)/l);

                //Tras:
                file << i * xx		<< " " << j * yy		<< " " << 0 << "\n";
                n.push_back(0);
                n.push_back(0);
                n.push_back(1);
                t.push_back(i/l);
                t.push_back(j/l);

                file << i * xx + xx	<< " " << j * yy + yy	<< " " << 0 << "\n";
                n.push_back(0);
                n.push_back(0);
                n.push_back(1);
                t.push_back((i+1)/l);
                t.push_back((j+1)/l);

                file << " " << i * xx + xx	<< " " << j * yy		<< " " << 0 << "\n";
                n.push_back(0);
                n.push_back(0);
                n.push_back(1);
                t.push_back((i+1)/l);
                t.push_back(j/l);

                file << i * xx		<< " " << j * yy		<< " " << 0 << "\n";
                n.push_back(0);
                n.push_back(0);
                n.push_back(1);
                t.push_back(i/l);
                t.push_back(j/l);

                file << i * xx		<< " " << j * yy + yy	<< " " << 0 << "\n";
                n.push_back(0);
                n.push_back(0);
                n.push_back(1);
                t.push_back(i/l);
                t.push_back((j+1)/l);

                file << i * xx + xx	<< " " << j * yy + yy	<< " " << 0 << "\n";
                n.push_back(0);
                n.push_back(0);
                n.push_back(1);
                t.push_back((i+1)/l);
                t.push_back((j+1)/l);

                //Cima:
                file << i * xx		<< " " << y << " " << j * zz		<< "\n";
                n.push_back(0);
                n.push_back(1);
                n.push_back(0);
                t.push_back(i/l);
                t.push_back(j/l);

                file << i * xx		<< " " << y << " " << j * zz + zz	<< "\n";
                n.push_back(0);
                n.push_back(1);
                n.push_back(0);
                t.push_back(i/l);
                t.push_back((j+1)/l);

                file << i * xx + xx	<< " " << y << " " << j * zz		<< "\n";
                n.push_back(0);
                n.push_back(1);
                n.push_back(0);
                t.push_back((i+1)/l);
                t.push_back(j/l);

                file << i * xx		<< " " << y << " " << j * zz + zz	<< "\n";
                n.push_back(0);
                n.push_back(1);
                n.push_back(0);
                t.push_back(i/l);
                t.push_back((j+1)/l);

                file << i * xx + xx	<< " " << y << " " << j * zz + zz	<< "\n";
                n.push_back(0);
                n.push_back(1);
                n.push_back(0);
                t.push_back((i+1)/l);
                t.push_back((j+1)/l);

                file  << i * xx + xx	<< " " << y << " " << j * zz		<< "\n";
                n.push_back(0);
                n.push_back(1);
                n.push_back(0);
                t.push_back((i+1)/l);
                t.push_back(j/l);

                //Baixo:
                file << i * xx		<< " " << 0 << " " << j * zz		<< "\n";
                n.push_back(0);
                n.push_back(1);
                n.push_back(0);
                t.push_back(i/l);
                t.push_back(j/l);

                file << i * xx + xx	<< " " << 0 << " " << j * zz		<< "\n";
                n.push_back(0);
                n.push_back(1);
                n.push_back(0);
                t.push_back((i+1)/l);
                t.push_back(j/l);

                file << i * xx		<< " " << 0 << " " << j * zz + zz	<< "\n";
                n.push_back(0);
                n.push_back(1);
                n.push_back(0);
                t.push_back(i/l);
                t.push_back((j+1)/l);

                file << i * xx		<< " " << 0 << " " << j * zz + zz	<< "\n";
                n.push_back(0);
                n.push_back(1);
                n.push_back(0);
                t.push_back(i/l);
                t.push_back((j+1)/l);

                file << i * xx + xx	<< " " << 0 << " " << j * zz		<< "\n";
                n.push_back(0);
                n.push_back(1);
                n.push_back(0);
                t.push_back((i+1)/l);
                t.push_back(j/l);

                file << i * xx + xx	<< " " << 0 << " " << j * zz + zz	<< "\n";
                n.push_back(0);
                n.push_back(1);
                n.push_back(0);
                t.push_back((i+1)/l);
                t.push_back((j+1)/l);

                //Direita:
                file << x << " " << j * yy		<< " " << i * zz		<< "\n";
                n.push_back(1);
                n.push_back(0);
                n.push_back(0);
                t.push_back(j/l);
                t.push_back(i/l);

                file << x << " " << j * yy + yy	<< " " << i * zz		<< "\n";
                n.push_back(1);
                n.push_back(0);
                n.push_back(0);
                t.push_back((j+1)/l);
                t.push_back(i/l);

                file << x << " " << j * yy		<< " " << i * zz + zz	<< "\n";
                n.push_back(1);
                n.push_back(0);
                n.push_back(0);
                t.push_back(j/l);
                t.push_back((j+1)/l);

                file << x << " " << j * yy + yy	<< " " << i * zz		<< "\n";
                n.push_back(1);
                n.push_back(0);
                n.push_back(0);
                t.push_back((j+1)/l);
                t.push_back(i/l);

                file << x << " " << j * yy + yy	<< " " << i * zz + zz	<< "\n";
                n.push_back(1);
                n.push_back(0);
                n.push_back(0);
                t.push_back((j+1)/l);
                t.push_back((i+1)/l);

                file << x << " " << j * yy		<< " " << i * zz + zz	<< "\n";
                n.push_back(1);
                n.push_back(0);
                n.push_back(0);
                t.push_back(j/l);
                t.push_back((i+1)/l);

                //Esquerda:
                file << 0 << " " << j * yy		<< " " << i * zz		<< "\n";
                n.push_back(1);
                n.push_back(0);
                n.push_back(0);
                t.push_back(j/l);
                t.push_back(i/l);

                file << 0 << " " << j * yy		<< " " << i * zz + zz	<< "\n";
                n.push_back(1);
                n.push_back(0);
                n.push_back(0);
                t.push_back(j/l);
                t.push_back((i+1)/l);

                file << 0 << " " << j * yy + yy	<< " " << i * zz		<< "\n";
                n.push_back(1);
                n.push_back(0);
                n.push_back(0);
                t.push_back((j+1)/l);
                t.push_back(i/l);

                file << 0 << " " << j * yy + yy	<< " " << i * zz + zz	<< "\n";
                n.push_back(1);
                n.push_back(0);
                n.push_back(0);
                t.push_back((j+1)/l);
                t.push_back((i+1)/l);

                file << 0 << " " << j * yy + yy	<< " " << i * zz		<< "\n";
                n.push_back(1);
                n.push_back(0);
                n.push_back(0);
                t.push_back((j+1)/l);
                t.push_back(i/l);

                file << 0 << " " << j * yy		<< " " << i * zz + zz	<< "\n";
                n.push_back(1);
                n.push_back(0);
                n.push_back(0);
                t.push_back(j/l);
                t.push_back((i+1)/l);
            }
        }

        file << "---\n";

        for(int i = 0; i < n.size(); i+=3){
            file << n.at(i) << " " << n.at(i+1) << " " << n.at(i+2);
        }

        file << "---\n";

        for(int i = 0; i < t.size(); i+=3){
            file << t.at(i) << " " << t.at(i+1) << " " << t.at(i+2);
        }

        file << "---\n";
    }
    file.close();
}

void drawSphere(float radius, int slices, int stacks, string fileName) {
    float phi = 0, deslocP = M_PI / stacks;
    float theta = 0, deslocT = (2 * M_PI) / slices;

    float ax, ay, az;
    float bx, by, bz;
    float cx, cy, cz;
    float dx, dy, dz;

    float saltoH = 1.0f/slices;
    float saltoV = 1.0f/stacks;

    vector<float> n;
    vector<float> t;

    ofstream file(fileName);
    if (file.is_open()) {
        for (int i = 0; i < slices; i++) {
            for (int j = 0; j < stacks; j++) {
                phi = j * deslocP;

                //inferior direito
                ax = radius * sin(theta) * sin(phi);
                ay = radius * cos(phi);
                az = radius * cos(theta) * sin(phi);

                //inferior esquerdo
                bx = radius * sin(theta + deslocT) * sin(phi);
                by = radius * cos(phi);
                bz = radius * cos(theta + deslocT) * sin(phi);

                //superior direito
                cx = radius * sin(theta) * sin(phi + deslocP);
                cy = radius * cos(phi + deslocP);
                cz = radius * cos(theta) * sin(phi + deslocP);

                //superior esquerdo
                dx = radius * sin(theta + deslocT) * sin(phi + deslocP);
                dy = radius * cos(phi + deslocP);
                dz = radius * cos(theta + deslocT) * sin(phi + deslocP);

                file << ax << " " << ay << " " << az << "\n";
                n.push_back(sin(theta) * sin(phi));
                n.push_back(cos(phi));
                n.push_back(cos(theta) * sin(phi));
                t.push_back(saltoH * i);
                t.push_back(saltoV * j);

                file << bx << " " << by << " " << bz << "\n";
                n.push_back(sin(theta + deslocT) * sin(phi));
                n.push_back(cos(phi));
                n.push_back(cos(theta + deslocT) * sin(phi));
                t.push_back(saltoH * i + saltoH);
                t.push_back(saltoV * j);

                file << cx << " " << cy << " " << cz << "\n";
                n.push_back(sin(theta) * sin(phi + deslocP));
                n.push_back(cos(phi + deslocP));
                n.push_back(cos(theta) * sin(phi + deslocP));
                t.push_back(saltoH * i);
                t.push_back(saltoV * j + saltoV);

                file << bx << " " << by << " " << bz << "\n";
                n.push_back(sin(theta + deslocT) * sin(phi));
                n.push_back(cos(phi));
                n.push_back(cos(theta + deslocT) * sin(phi));
                t.push_back(saltoH * i + saltoH);
                t.push_back(saltoV * j);

                file << dx << " " << dy << " " << dz << "\n";
                n.push_back(sin(theta + deslocT) * sin(phi + deslocP));
                n.push_back(cos(phi + deslocP));
                n.push_back(cos(theta + deslocT) * sin(phi + deslocP));
                t.push_back(saltoH * i + saltoH);
                t.push_back(saltoV * j + saltoV);

                file << cx << " " << cy << " " << cz << "\n";
                n.push_back(sin(theta) * sin(phi + deslocP));
                n.push_back(cos(phi + deslocP));
                n.push_back(cos(theta) * sin(phi + deslocP));
                t.push_back(saltoH * i);
                t.push_back(saltoV * j + saltoV);
            }
            theta += deslocT;
        }

        file << "---\n";

        for (int i = 0; i < n.size(); i += 3) {
            file << n[i] << " " << n[i + 1] << " " << n[i + 2] << "\n";
        }

        file << "---\n";

        for (int i = 0; i < t.size(); i += 2) {
            file << t[i] << " " << t[i + 1] << "\n";
        }

        file << "---\n";
    }


    file.close();
}

void drawCone(float radius, float height, int slices, int stacks, string fileName) {
    float alfa = 0, deslocA = 2*M_PI / slices;
    float hStack = height / stacks;
    float rStack = radius / stacks;

    float ax, ay, az;
    float bx, by, bz;
    float cx, cy, cz;
    float dx, dy, dz;

    vector<float> n, t;

    ofstream file(fileName);
    if (file.is_open()) {
        for (int i = 0; i < slices; i++) {

            float base = 0.0f;
            //base
            file << " " << 0.0f << " " << base << " " << 0.0f << "\n";
            n.push_back(0);
            n.push_back(1);
            n.push_back(0);
            t.push_back(0.5);
            t.push_back(0.5);

            file << " " << radius * sin(alfa + deslocA) << " " << base << " " << radius * cos(alfa + deslocA) << "\n";
            n.push_back(0);
            n.push_back(1);
            n.push_back(0);
            t.push_back(0.5+0.5*sin(alfa + deslocA));
            t.push_back(0.5+0.5*cos(alfa + deslocA));

            file << " " << radius * sin(alfa) << " " << base << " " << radius * cos(alfa) << "\n";
            n.push_back(0);
            n.push_back(1);
            n.push_back(0);
            t.push_back(0.5+0.5*sin(alfa));
            t.push_back(0.5+0.5*cos(alfa));

            for (int j = 0; j < stacks; j++) {
                float rInferior = radius - rStack * j;
                float rSuperior = radius - rStack * (j + 1);

                //inferior esquerdo
                ax = rInferior * sin(alfa);
                ay = base;
                az = rInferior * cos(alfa);

                //inferior direito
                bx = rInferior * sin(alfa + deslocA);
                by = base;
                bz = rInferior * cos(alfa + deslocA);

                //superior direito
                cx = rSuperior * sin(alfa + deslocA);
                cy = base + hStack;
                cz = rSuperior * cos(alfa + deslocA);

                //superior esquerdo
                dx = rSuperior * sin(alfa);
                dy = base + hStack;
                dz = rSuperior * cos(alfa);


                file << " " << ax << " " << ay << " " << az << "\n";
                n.push_back(sin(alfa));
                n.push_back(base);
                n.push_back(cos(alfa));
                t.push_back((i*1.0)/slices);
                t.push_back((j*1.0)/stacks);

                file << " " << bx << " " << by << " " << bz << "\n";
                n.push_back(sin(alfa + deslocA));
                n.push_back(base);
                n.push_back(cos(alfa + deslocA));
                t.push_back((i+1.0)/slices);
                t.push_back((j*1.0)/stacks);

                file << " " << cx << " " << cy << " " << cz << "\n";
                n.push_back(sin(alfa+deslocA));
                n.push_back(base+hStack);
                n.push_back(cos(alfa+deslocA));
                t.push_back((i+1.0)/slices);
                t.push_back((j+1.0)/stacks);

                file << " " << ax << " " << ay << " " << az << "\n";
                n.push_back(sin(alfa));
                n.push_back(base);
                n.push_back(cos(alfa));
                t.push_back((i*1.0)/slices);
                t.push_back((j*1.0)/stacks);

                file << " " << cx << " " << cy << " " << cz << "\n";
                n.push_back(sin(alfa+deslocA));
                n.push_back(base+hStack);
                n.push_back(cos(alfa+deslocA));
                t.push_back((i+1.0)/slices);
                t.push_back((j+1.0)/stacks);

                file << " " << dx << " " << dy << " " << dz << "\n";
                n.push_back(sin(alfa));
                n.push_back(base+hStack);
                n.push_back(cos(alfa));
                t.push_back((i*1.0)/slices);
                t.push_back((j+1.0)/stacks);

                base += hStack;
            }
            alfa += deslocA;
        }
        file << "---\n";

        for (int i = 0; i < n.size(); i += 3) {
            file << n[i] << " " << n[i + 1] << " " << n[i + 2] << "\n";
        }

        file << "---\n";

        for (int i = 0; i < t.size(); i += 2) {
            file << t[i] << " " << t[i + 1] << "\n";
        }

        file << "---\n";
    }



    file.close();
}

float* bezierFormula(float t, float* p0, float* p1, float* p2, float *p3){
    float* result = new float[3];

    float aux = (1-t);

    float x0 = aux * aux * aux;
    float x1 = 3 * (aux * aux) * t;
    float x2 = 3 * aux * (t * t);
    float x3 = t * t * t;


    result[0] = x0 * p0[0] + x1 * p1[0] + x2 * p2[0] + x3 * p3[0];
    result[1] = x0 * p0[1] + x1 * p1[1] + x2 * p2[1] + x3 * p3[1];
    result[2] = x0 * p0[2] + x1 * p1[2] + x2 * p2[2] + x3 * p3[2];

    return result;


}

float* bezier(float n, float m, vector<float> points, int* index){
    int i;
    float* point;
    float* result;
    int j = 0;
    int N = 0;
    float pointsAcumulator[4][3];
    float bezierAcumulator[4][3];

    for(i=0; i < 16; i++){
        pointsAcumulator[j][0] = points.at(3 * index[i] + 0);
        pointsAcumulator[j][1] = points.at(3 * index[i] + 1);
        pointsAcumulator[j][2] = points.at(3 * index[i] + 2);

        j++;

        if(j % 4 == 0){
            point = bezierFormula(n, pointsAcumulator[0], pointsAcumulator[1], pointsAcumulator[2], pointsAcumulator[3]);
//            printf("RESULT: %f , %f, %f\n", point[0], point[1], point[2]);
            bezierAcumulator[N][0] = point[0];
            bezierAcumulator[N][1] = point[1];
            bezierAcumulator[N][2] = point[2];
            j = 0;
            N++;
        }
    }
    result = bezierFormula(m, bezierAcumulator[0], bezierAcumulator[1], bezierAcumulator[2], bezierAcumulator[3]);

  //  printf("RESULT: %f , %f, %f\n", result[0], result[1], result[2]);

    return result;
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


void multMatrixVector(float *m, float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}

float* derivateUBezier(vector<float>& patch_points, float u, float v, float* vector) {

    float M[16] = { -1, 3, -3, 1, 3, -6, 3, 0, -3, 3, 0, 0, 1, 0, 0, 0 };

    float U[4] = { 3 * u * u, 2 * u, 1, 0 };
    float V[4] = { v * v * v, v * v, v, 1 };

    float UM[4];
    float MV[4];
    float UMPontos[3][4];

    //U x M
    multMatrixVector(M, U, UM);
    //M x V
    multMatrixVector(M, V, MV);

    for (int j = 0; j < 4; j++) {
        UMPontos[0][j] = UM[0] * patch_points[3 * j * 4 + 0] + UM[1] * patch_points[3 * j * 4 + 3]
                         + UM[2] * patch_points[3 * j * 4 + 6] + UM[3] * patch_points[3 * j * 4 + 9];
        UMPontos[1][j] = UM[0] * patch_points[3 * j * 4 + 0 + 1] + UM[1] * patch_points[3 * j * 4 + 3 + 1]
                         + UM[2] * patch_points[3 * j * 4 + 6 + 1] + UM[3] * patch_points[3 * j * 4 + 9 + 1];
        UMPontos[2][j] = UM[0] * patch_points[3 * j * 4 + 0 + 2] + UM[1] * patch_points[3 * j * 4 + 3 + 2]
                         + UM[2] * patch_points[3 * j * 4 + 6 + 2] + UM[3] * patch_points[3 * j * 4 + 9 + 2];
    }

    //UMcoordenadasXYZ x MV
    for (int i = 0; i < 3; i++) {
        vector[i] = UMPontos[i][0] * MV[0] + UMPontos[i][1] * MV[1] + UMPontos[i][2] * MV[2] + UMPontos[i][3] * MV[3];
    }

    return vector;
}

float* derivateVBezier(vector<float>& patch_points, float u, float v, float* vector) {

    float M[16] = { -1, 3, -3, 1, 3, -6, 3, 0, -3, 3, 0, 0, 1, 0, 0, 0 };

    float U[4] = { 3 * u * u, 2 * u, 1, 0 };
    float V[4] = { v * v * v, v * v, v, 1 };

    float UM[4];
    float MV[4];
    float UMPontos[3][4];

    //U x M
    multMatrixVector(M, U, UM);
    //M x V
    multMatrixVector(M, V, MV);

    for (int j = 0; j < 4; j++) {
        UMPontos[0][j] = UM[0] * patch_points[3 * j * 4 + 0] + UM[1] * patch_points[3 * j * 4 + 3]
                         + UM[2] * patch_points[3 * j * 4 + 6] + UM[3] * patch_points[3 * j * 4 + 9];
        UMPontos[1][j] = UM[0] * patch_points[3 * j * 4 + 0 + 1] + UM[1] * patch_points[3 * j * 4 + 3 + 1]
                         + UM[2] * patch_points[3 * j * 4 + 6 + 1] + UM[3] * patch_points[3 * j * 4 + 9 + 1];
        UMPontos[2][j] = UM[0] * patch_points[3 * j * 4 + 0 + 2] + UM[1] * patch_points[3 * j * 4 + 3 + 2]
                         + UM[2] * patch_points[3 * j * 4 + 6 + 2] + UM[3] * patch_points[3 * j * 4 + 9 + 2];
    }

    //UMcoordenadasXYZ x MV
    for (int i = 0; i < 3; i++) {
        vector[i] = UMPontos[i][0] * MV[0] + UMPontos[i][1] * MV[1] + UMPontos[i][2] * MV[2] + UMPontos[i][3] * MV[3];
    }

    return vector;
}

float* normalBezier(vector<float>& patch_points, float u, float v) {

    float* vetorU = new float[3];
    float* vetorV = new float[3];
    float* normal = new float[3];

    for(int i=0;i<3;i++){
        vetorU[i]=0.0f;
        vetorV[i]=0.0f;
        normal[i]=0.0f;
    }

    vetorU = derivateUBezier(patch_points, u, v,vetorU);
    vetorV = derivateVBezier(patch_points, u, v,vetorV);

    // normaliza os vetores
    normalize(vetorU);
    normalize(vetorV);

    // calcula o produto vetorial
    cross(vetorU, vetorV, normal);

    // normaliza a normal
    normalize(normal);

    return normal;

}

void drawTeapot(string str, int tessellation) {
    std::ifstream infile(str);

    float x, y, z;
    int patches;

    vector<float> n, t;

    if (!infile) {
        std::cout << "Ocorreu um erro na leitura do ficheiro." << std::endl;
        return;
    }
    string buffer;
    getline(infile, buffer);
    patches = atoi(buffer.c_str());
    string delimiter = ",";

    int matrizIndices[patches][16];
    for(int i = 0; i < patches; i++){
        getline(infile, buffer);
        for(int j = 0; j < 16; j++) {
            int pos = buffer.find(delimiter);
            string token = buffer.substr(0, pos);
            matrizIndices[i][j] = std::atoi(token.c_str());
            buffer.erase(0, pos + delimiter.length());
        }
    }

    getline(infile, buffer);
    int lines = atoi(buffer.c_str());

    vector<float> pontos;

    for(int i = 0; i < lines; i++){
        getline(infile, buffer);
        for(int j = 0; j<3; j++){
            int pos = buffer.find(delimiter);
            string token = buffer.substr(0, pos);
            pontos.push_back(atof(token.c_str()));
            buffer.erase(0, pos + delimiter.length());
        }
    }

    // vamos escrever:

    ofstream write("teapot.3d");
    vector<float*> resultPoints;
    float increment = 1.0/tessellation;

    for(int i = 0; i < patches; i++){
        for(int xx = 0; xx < tessellation; xx++ ) {
            for(int yy = 0; yy < tessellation; yy++) {
                float x1 = increment * xx;
                float x2 = increment * ( xx+1 );

                float y1 = increment * yy;
                float y2 = increment * ( yy+1 );

                resultPoints.push_back(bezier(x1, y1, pontos, matrizIndices[i]));
                resultPoints.push_back(bezier(x1, y2, pontos, matrizIndices[i]));
                resultPoints.push_back(bezier(x2, y1, pontos, matrizIndices[i]));
                resultPoints.push_back(bezier(x2, y2, pontos, matrizIndices[i]));


                write << resultPoints.at(0)[0] << " " << resultPoints.at(0)[1] << " " << resultPoints.at(0)[2] << endl;
                n.push_back(normalBezier(pontos,x1,y1)[0]);
                n.push_back(normalBezier(pontos,x1,y1)[1]);
                n.push_back(normalBezier(pontos,x1,y1)[2]);
                t.push_back(x1);
                t.push_back(y1);


                write << resultPoints.at(2)[0] << " " << resultPoints.at(2)[1] << " " << resultPoints.at(2)[2] << endl;
                n.push_back(normalBezier(pontos,x2,y1)[0]);
                n.push_back(normalBezier(pontos,x2,y1)[1]);
                n.push_back(normalBezier(pontos,x2,y1)[2]);
                t.push_back(x2);
                t.push_back(y1);
                write << resultPoints.at(3)[0] << " " << resultPoints.at(3)[1] << " " << resultPoints.at(3)[2] << endl;
                n.push_back(normalBezier(pontos,x2,y2)[0]);
                n.push_back(normalBezier(pontos,x2,y2)[1]);
                n.push_back(normalBezier(pontos,x2,y2)[2]);
                t.push_back(x2);
                t.push_back(y2);

                write << resultPoints.at(0)[0] << " " << resultPoints.at(0)[1] << " " << resultPoints.at(0)[2] << endl;
                n.push_back(normalBezier(pontos,x1,y1)[0]);
                n.push_back(normalBezier(pontos,x1,y1)[1]);
                n.push_back(normalBezier(pontos,x1,y1)[2]);
                t.push_back(x1);
                t.push_back(y1);
                write << resultPoints.at(3)[0] << " " << resultPoints.at(3)[1] << " " << resultPoints.at(3)[2] << endl;
                n.push_back(normalBezier(pontos,x2,y2)[0]);
                n.push_back(normalBezier(pontos,x2,y2)[1]);
                n.push_back(normalBezier(pontos,x2,y2)[2]);
                t.push_back(x2);
                t.push_back(y2);
                write << resultPoints.at(1)[0] << " " << resultPoints.at(1)[1] << " " << resultPoints.at(1)[2] << endl;
                n.push_back(normalBezier(pontos,x1,y2)[0]);
                n.push_back(normalBezier(pontos,x1,y2)[1]);
                n.push_back(normalBezier(pontos,x1,y2)[2]);
                t.push_back(x1);
                t.push_back(y2);

                resultPoints.pop_back();
                resultPoints.pop_back();
                resultPoints.pop_back();
                resultPoints.pop_back();
            }
        }
    }

    write << "---\n";

    for (int i = 0; i < n.size(); i += 3) {
        write << n[i] << " " << n[i + 1] << " " << n[i + 2] << "\n";
    }

    write << "---\n";

    for (int i = 0; i < t.size(); i += 2) {
        write << t[i] << " " << t[i + 1] << "\n";
    }

    write << "---\n";

    write.close();
}

int main(int argc, char **argv) {

    if (strcmp(argv[1], "teapot") == 0 && argc == 3){
        string path = "../";
        string extension = ".patch";
        path += argv[1] + extension;

        drawTeapot(path, atoi(argv[2]));
    }

    else if (strcmp(argv[1], "plane") == 0 && argc == 4)
        drawPlane(atof(argv[2]), argv[3]);

    else if (strcmp(argv[1], "box") == 0 && argc == 6)
        drawBox(atof(argv[2]), atof(argv[3]), atof(argv[4]), 1, argv[5]);
    else if (strcmp(argv[1], "box") == 0 && argc == 7)
        drawBox(atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]), argv[6]);

    else if (strcmp(argv[1], "sphere") == 0 && argc == 6)
        drawSphere(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);

    else if (strcmp(argv[1], "cone") == 0 && argc == 7)
        drawCone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);

    else printf("Invalid input format\n");

    return 1;
}



