
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

loadMaterial(materialIndex);
 
glEnable(GL_TEXTURE_2D);

glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

global.platform_texture.bind(); 

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



int cubeCountX = 20; 
GLfloat cubeSizeX = dimensions.x / cubeCountX; 

for (int i = 0; i < cubeCountX; ++i) {
    glPushMatrix();
        GLfloat offsetX = -dimensions.x / 2 + (i + 0.5f) * cubeSizeX;
        glTranslatef(position.x + offsetX, position.y, position.z);
        glScalef(cubeSizeX, dimensions.y, dimensions.z);
        cube_texture_unit(2.0);
    glPopMatrix();
}

global.platform_texture.unbind(); 
glDisable(GL_TEXTURE_2D);
/*
//draw the outlines
loadMaterial(2); 

for (int i = 0; i < cubeCountX; ++i) {
    glPushMatrix();
        GLfloat offsetX = -dimensions.x / 2 + (i + 0.5f) * cubeSizeX;
        glTranslatef(position.x + offsetX, position.y, position.z);

        glScalef(cubeSizeX, dimensions.y, dimensions.z);

        cube_unit_outline(0.5);
    glPopMatrix();
    
}
*/
}

