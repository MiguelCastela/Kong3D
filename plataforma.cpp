
#include <algorithm>
#include <cmath>
#include <vector>
#include "ofApp.h"
#include "plataforma.h"
#include "materials.h"
using namespace std;

Platform::Platform(ofVec3f dimensions, ofVec3f position) {
    this->dimensions = dimensions;
    this->position = position;

}

void Platform::draw() {
loadMaterial(25);
glPushMatrix(); // Base push

// Define the number of cubes along each axis
int cubeCountX = 20; // Number of smaller cubes along the X-axis
int cubeCountZ = 20; // Number of smaller cubes along the Z-axis
GLfloat cubeSizeX = dimensions.x / cubeCountX; // Size of each smaller cube along X
GLfloat cubeSizeZ = dimensions.z / cubeCountZ; // Size of each smaller cube along Z

// Loop to create a grid of smaller cubes
for (int i = 0; i < cubeCountX; ++i) {
    for (int j = 0; j < cubeCountZ; ++j) {
        glPushMatrix();
        // Position each smaller cube
        GLfloat offsetX = -dimensions.x / 2 + (i + 0.5f) * cubeSizeX;
        GLfloat offsetZ = -dimensions.z / 2 + (j + 0.5f) * cubeSizeZ;
        glTranslatef(position.x + offsetX, position.y, position.z + offsetZ);

        // Scale the cube to the smaller size
        glScalef(cubeSizeX, dimensions.y, cubeSizeZ);

        // Draw the cube
        cube_unit(0.5);
        glPopMatrix();
    }
}
/*
loadMaterial(2);
for (int i = 0; i < cubeCountX; ++i) {
    for (int j = 0; j < cubeCountZ; ++j) {
        glPushMatrix();
        GLfloat offsetX = -dimensions.x / 2 + (i + 0.5f) * cubeSizeX;
        GLfloat offsetZ = -dimensions.z / 2 + (j + 0.5f) * cubeSizeZ;
        glTranslatef(position.x + offsetX, position.y, position.z + offsetZ);
        glScalef(cubeSizeX, dimensions.y, cubeSizeZ);
        cube_unit_outline(0.5);
        glPopMatrix();
    }
}
*/
glPopMatrix(); // Base pop
}

