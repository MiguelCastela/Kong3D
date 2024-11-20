#include <bits/stdc++.h>
#include "ofApp.h"
#include "escadas.h"
using namespace std;

Ladder::Ladder(ofVec3f dimension, ofVec3f position) {
    this->dimension = dimension;
    this->position = position;
}


void Ladder::draw(){
    glColor3f(0.6f, 0.3f, 0.0f);
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y, position.z + 1);
        glScalef(dimension.x, dimension.y, dimension.z);
        cube_unit(0.5);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
}

void Ladder::draw_hitbox(){
    glColor3f(0.6f, 0.3f, 0.0f);
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z+1);
        glScalef(dimension.x, dimension.y, dimension.z);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
}

void Ladder::draw_fake_lad(){
    glColor3f(1.0f, 0.3f, 0.0f);
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z+1);
        glScalef(dimension.x, dimension.y, dimension.z);
        cube_unit(0.5);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
}

