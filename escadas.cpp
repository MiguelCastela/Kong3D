#include <algorithm>
#include <cmath>
#include <vector>
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
        glTranslatef(position.x, position.y, position.z + 1 );
        glScalef(dimension.x, dimension.y, dimension.z);
        cube_unit(0.5);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glColor3f(0.7f, 0.3f, 0.0f);
        glTranslatef(position.x, position.y, position.z + 1 + dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z *1.1);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glColor3f(0.7f, 0.3f, 0.0f);
        glTranslatef(position.x, position.y + dimension.y*0.2, position.z + 1 + dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glColor3f(0.7f, 0.3f, 0.0f);
        glTranslatef(position.x, position.y + dimension.y*0.4, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glColor3f(0.7f, 0.3f, 0.0f);
        glTranslatef(position.x, position.y - dimension.y*0.2, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glColor3f(0.7f, 0.3f, 0.0f);
        glTranslatef(position.x, position.y - dimension.y*0.4, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop

}

void Ladder::draw_hitbox(){
    glColor3f(0.6f, 0.3f, 0.0f);
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z+1);
        glScalef(dimension.x, dimension.y, dimension.z);
        cube_unit_outline(0.5);
    glPopMatrix();
}

void Ladder::draw_fake_lad(){
   glColor3f(0.6f, 0.3f, 0.0f);
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y, position.z + 1 );
        glScalef(dimension.x, dimension.y, dimension.z);
        cube_unit(0.5);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glColor3f(0.7f, 0.3f, 0.0f);
        glTranslatef(position.x, position.y, position.z + 1 + dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z *1.1);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glColor3f(0.7f, 0.3f, 0.0f);
        glTranslatef(position.x, position.y + dimension.y*0.2, position.z + 1 + dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glColor3f(0.7f, 0.3f, 0.0f);
        glTranslatef(position.x, position.y + dimension.y*0.4, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glColor3f(0,0,0);
        glTranslatef(position.x, position.y - dimension.y*0.2, position.z + 1);
        glScalef(dimension.x*1.05, dimension.y*0.2, dimension.z*1.1);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glColor3f(0.7f, 0.3f, 0.0f);
        glTranslatef(position.x, position.y - dimension.y*0.4, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop

}

void Ladder::draw_golden(){
    glColor3f(0.9f, 0.9f, 0.0f);
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z+1);
        glScalef(dimension.x, dimension.y, dimension.z);
        cube_unit(0.5);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
        glPushMatrix();//ladder push
        glTranslatef(position.x, position.y, position.z + 1 + dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z *1.1);
        glColor3f(1.0f, 1.0f, 0.0f);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y + dimension.y*0.2, position.z + 1 + dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        glColor3f(1.0f, 1.0f, 0.0f);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y + dimension.y*0.4, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        glColor3f(1.0f, 1.0f, 0.0f);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y - dimension.y*0.2, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        glColor3f(1.0f, 1.0f, 0.0f);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y - dimension.y*0.4, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        glColor3f(1.0f, 1.0f, 0.0f);
        cube_unit(0.5);
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop

}

