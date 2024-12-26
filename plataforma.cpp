
#include <algorithm>
#include <cmath>
#include <vector>
#include "ofApp.h"
#include "plataforma.h"
#include "materials.h"
#include "global.h"
using namespace std;

Platform::Platform(ofVec3f dimensions, ofVec3f position, int materialIndex) {
    this->dimensions = dimensions;
    this->position = position;
    this->materialIndex = materialIndex;

}

void Platform::draw() {
 // Set the material for the cubes

loadMaterial(materialIndex);
 
glEnable(GL_TEXTURE_2D);
//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

global.platform_texture.bind(); // Bind the texture to the cubes

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


int cubeCountX = 9; // Number of partitions along the X-axis
GLfloat cubeSizeX = dimensions.x / cubeCountX; 

// Loop through the vertical partitions along the X-axis (from left to right)
for (int i = 0; i < cubeCountX; ++i) {
    glPushMatrix();
    // Position each smaller cube along the X-axis
    GLfloat offsetX = -dimensions.x / 2 + (i + 0.5f) * cubeSizeX;
    glTranslatef(position.x + offsetX, position.y, position.z);

    // Scale to match the size of each partition (along X)
    glScalef(cubeSizeX, dimensions.y, dimensions.z);

    // Draw the cube for this partition
    cube_texture_unit(2.0);

    glPopMatrix();
}

global.platform_texture.unbind(); // Unbind the texture from the cubes
glDisable(GL_TEXTURE_2D);
/*
// Now, draw the outlines
loadMaterial(2); // Change material for the outlines

// Loop through the vertical partitions along the X-axis (same as above)
for (int i = 0; i < cubeCountX; ++i) {
    glPushMatrix();
    // Position each smaller cube along the X-axis
    GLfloat offsetX = -dimensions.x / 2 + (i + 0.5f) * cubeSizeX;
    glTranslatef(position.x + offsetX, position.y, position.z);

    // Scale to match the size of each partition (along X)
    glScalef(cubeSizeX, dimensions.y, dimensions.z);

    // Draw the outline for this partition
    cube_unit_outline(0.5);
    glPopMatrix();
    
}
*/
}

