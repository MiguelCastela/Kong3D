
#include <algorithm>
#include <cmath>
#include <vector>
#include "ofApp.h"
#include "plataforma.h"
#include "materials.h"
using namespace std;

Platform::Platform(ofVec3f dimensions, ofVec3f position, ofVec3f color) {
    this->dimensions = dimensions;
    this->position = position;
    this->color = color;

}

void Platform::draw() {
    loadMaterial(21);
	glPushMatrix();//base push
        glTranslatef(position.x ,position.y,  position.z );
        glScalef(dimensions.x, dimensions.y , dimensions.z);
        cube_unit(0.5);
        cube_unit_outline(0.5);
	glPopMatrix();//level pop
    
}

