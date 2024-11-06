#include <bits/stdc++.h>
#include "ofApp.h"
#include "mario.h"
using namespace std;

Mario::Mario(GLfloat size, GLfloat PositionHeight, GLfloat PositionWidth, GLfloat PositionDepth, GLfloat StartinglevelHeight, GLfloat resY) {
    this->size = size;
    this->PositionHeight = PositionHeight;
    this->PositionWidth = PositionWidth;
    this->PositionDepth = PositionDepth;
    if(StartinglevelHeight != 0){
        this->StartinglevelHeight = (resY / 2) / StartinglevelHeight;
    }else{
        this->StartinglevelHeight = 0;
    }
}

void Mario::draw() {
    glColor3f(1, 1, 0);
    glPushMatrix();//base push
    glTranslatef(gw() * 0.5, (gh() * 0.5) + (PositionHeight * StartinglevelHeight) , 0);
    glScalef(PositionWidth, PositionHeight, PositionDepth);
    cube_unit(0.5);
    glPopMatrix();//level pop
}