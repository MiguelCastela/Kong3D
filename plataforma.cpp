
#include <bits/stdc++.h>
#include "ofApp.h"
#include "plataforma.h"
using namespace std;

Platform::Platform(GLfloat levelWidth, GLfloat levelHeight, GLfloat levelDepth, GLfloat height, GLint resY) {
    this->levelWidth = levelWidth;
    this->levelHeight = levelHeight;
    this->levelDepth = levelDepth;
    if(height != 0){
        this->height = height;
    }else{
        this->height = 0;
    }
    this->resY = resY;
    int tmp = resY/2;
    this->ladderOffset = (rand() % resY) - tmp;

    

}

void Platform::draw(int index) {
    glColor3f(0.0f, 0.0f, 0.4f); // Set color to yellow for regular platforms
	glPushMatrix();//base push
        glTranslatef(gw() * 0.5, ((gh() * 0.5) + (height * levelHeight)) , abs(index * levelDepth));
        glScalef(levelWidth, levelHeight, levelDepth);
        cube_unit(0.5);
        cube_unit_outline(0.5);
	glPopMatrix();//level pop
    
}

void Platform::setIndex(int idx) {
    index = idx;
    
}

int Platform::getIndex() const {
    return index;
}
