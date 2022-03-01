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
    }
    file.close();
}

void drawBox(float x, float y, float z, int n, string fileName) {
    float xx = x / n;
    float yy = y / n;
    float zz = z / n;

    ofstream file(fileName);
    if (file.is_open()) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                //Frente:
                file << " " << i * xx		<< " " << j * yy		<< " " << z << "\n";
                file << " " << i * xx + xx	<< " " << j * yy		<< " " << z << "\n";
                file << " " << i * xx + xx	<< " " << j * yy + yy	<< " " << z << "\n";

                file << " " << i * xx		<< " " << j * yy		<< " " << z << "\n";
                file << " " << i * xx + xx	<< " " << j * yy + yy	<< " " << z << "\n";
                file << " " << i * xx		<< " " << j * yy + yy	<< " " << z << "\n";

                //Tras:
                file << " " << i * xx		<< " " << j * yy		<< " " << 0 << "\n";
                file << " " << i * xx + xx	<< " " << j * yy + yy	<< " " << 0 << "\n";
                file << " " << i * xx + xx	<< " " << j * yy		<< " " << 0 << "\n";

                file << " " << i * xx		<< " " << j * yy		<< " " << 0 << "\n";
                file << " " << i * xx		<< " " << j * yy + yy	<< " " << 0 << "\n";
                file << " " << i * xx + xx	<< " " << j * yy + yy	<< " " << 0 << "\n";

                //Cima:
                file << " " << i * xx		<< " " << y << " " << j * zz		<< "\n";
                file << " " << i * xx		<< " " << y << " " << j * zz + zz	<< "\n";
                file << " " << i * xx + xx	<< " " << y << " " << j * zz		<< "\n";

                file << " " << i * xx		<< " " << y << " " << j * zz + zz	<< "\n";
                file << " " << i * xx + xx	<< " " << y << " " << j * zz + zz	<< "\n";
                file << " " << i * xx + xx	<< " " << y << " " << j * zz		<< "\n";

                //Baixo:
                file << " " << i * xx		<< " " << 0 << " " << j * zz		<< "\n";
                file << " " << i * xx + xx	<< " " << 0 << " " << j * zz		<< "\n";
                file << " " << i * xx		<< " " << 0 << " " << j * zz + zz	<< "\n";

                file << " " << i * xx		<< " " << 0 << " " << j * zz + zz	<< "\n";
                file << " " << i * xx + xx	<< " " << 0 << " " << j * zz		<< "\n";
                file << " " << i * xx + xx	<< " " << 0 << " " << j * zz + zz	<< "\n";

                //Direita:
                file << " " << x << " " << j * yy		<< " " << i * zz		<< "\n";
                file << " " << x << " " << j * yy + yy	<< " " << i * zz		<< "\n";
                file << " " << x << " " << j * yy		<< " " << i * zz + zz	<< "\n";

                file << " " << x << " " << j * yy + yy	<< " " << i * zz		<< "\n";
                file << " " << x << " " << j * yy + yy	<< " " << i * zz + zz	<< "\n";
                file << " " << x << " " << j * yy		<< " " << i * zz + zz	<< "\n";

                //Esquerda:
                file << " " << 0 << " " << j * yy		<< " " << i * zz		<< "\n";
                file << " " << 0 << " " << j * yy		<< " " << i * zz + zz	<< "\n";
                file << " " << 0 << " " << j * yy + yy	<< " " << i * zz		<< "\n";

                file << " " << 0 << " " << j * yy + yy	<< " " << i * zz + zz	<< "\n";
                file << " " << 0 << " " << j * yy + yy	<< " " << i * zz		<< "\n";
                file << " " << 0 << " " << j * yy		<< " " << i * zz + zz	<< "\n";

            }
        }
    }
    file.close();
}

void drawSphere(float radius, int slices, int stacks, string fileName) {
    float phi = 0, deslocP = M_PI / stacks;
    float theta = M_PI/2, deslocT = 2 * M_PI / slices;

    float ax, ay, az;
    float bx, by, bz;
    float cx, cy, cz;
    float dx, dy, dz;

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

                file << " " << ax << " " << ay << " " << az << "\n";
                file << " " << dx << " " << dy << " " << dz << "\n";
                file << " " << bx << " " << by << " " << bz << "\n";

                file << " " << ax << " " << ay << " " << az << "\n";
                file << " " << cx << " " << cy << " " << cz << "\n";
                file << " " << dx << " " << dy << " " << dz << "\n";
            }
            theta -= deslocT;
        }
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

    ofstream file(fileName);
    if (file.is_open()) {
        for (int i = 0; i < slices; i++) {

            float base = 0.0f;
            //base
            file << " " << 0.0f << " " << base << " " << 0.0f << "\n";
            file << " " << radius * sin(alfa + deslocA) << " " << base << " " << radius * cos(alfa + deslocA) << "\n";
            file << " " << radius * sin(alfa) << " " << base << " " << radius * cos(alfa) << "\n";

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
                file << " " << bx << " " << by << " " << bz << "\n";
                file << " " << cx << " " << cy << " " << cz << "\n";

                file << " " << ax << " " << ay << " " << az << "\n";
                file << " " << cx << " " << cy << " " << cz << "\n";
                file << " " << dx << " " << dy << " " << dz << "\n";

                base += hStack;
            }
            alfa += deslocA;
        }
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

void drawTeapot(string str, int tessellation) {
    std::ifstream infile(str);

    float x, y, z;
    int patches;

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
                write << resultPoints.at(2)[0] << " " << resultPoints.at(2)[1] << " " << resultPoints.at(2)[2] << endl;
                write << resultPoints.at(3)[0] << " " << resultPoints.at(3)[1] << " " << resultPoints.at(3)[2] << endl;

                write << resultPoints.at(0)[0] << " " << resultPoints.at(0)[1] << " " << resultPoints.at(0)[2] << endl;
                write << resultPoints.at(3)[0] << " " << resultPoints.at(3)[1] << " " << resultPoints.at(3)[2] << endl;
                write << resultPoints.at(1)[0] << " " << resultPoints.at(1)[1] << " " << resultPoints.at(1)[2] << endl;

                resultPoints.pop_back();
                resultPoints.pop_back();
                resultPoints.pop_back();
                resultPoints.pop_back();
            }
        }
    }
    write.close();
}

int main(int argc, char **argv) {

    if (strcmp(argv[1], "teapot.patch") == 0 && argc == 3){
        string path = "../";
        path += argv[1];

        drawTeapot(path, atoi(argv[2]));
    }

    else if (strcmp(argv[1], "plane.xml") == 0 && argc == 4)
        drawPlane(atof(argv[2]), argv[3]);

    else if (strcmp(argv[1], "box") == 0 && argc == 6)
        drawBox(atof(argv[2]), atof(argv[3]), atof(argv[4]), 1, argv[5]);
    else if (strcmp(argv[1], "box") == 0 && argc == 7)
        drawBox(atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]), argv[6]);

    else if (strcmp(argv[1], "sphere") == 0 && argc == 6)
        drawSphere(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);

    else if (strcmp(argv[1], "cone.xml") == 0 && argc == 7)
        drawCone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);

    else printf("Invalid input format\n");

    return 1;
}



