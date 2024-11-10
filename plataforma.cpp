
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
    

}

void Platform::draw() {
    glColor3f(1, 1, 0);
	glPushMatrix();//base push
    glTranslatef(gw() * 0.5, (gh() * 0.5) + (height * levelHeight) , 0);
	glScalef(levelWidth, levelHeight, levelDepth);
	cube_unit(0.5);
	glPopMatrix();//level pop
}

