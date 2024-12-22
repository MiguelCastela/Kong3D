#include <algorithm>
#include <cmath>
#include <vector>
#include "ofApp.h"
#include "escadas.h"
#include "materials.h"
using namespace std;

Ladder::Ladder(ofVec3f dimension, ofVec3f position) {
    this->dimension = dimension;
    this->position = position;
}


void Ladder::draw(){
    loadMaterial(26);
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y, position.z + 1 );
        glScalef(dimension.x, dimension.y, dimension.z);
        cube_unit(0.5);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        loadMaterial(20);
        glTranslatef(position.x, position.y, position.z + 1 + dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z *1.1);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        loadMaterial(20);
        glTranslatef(position.x, position.y + dimension.y*0.2, position.z + 1 + dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        loadMaterial(20);
        glTranslatef(position.x, position.y + dimension.y*0.4, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        loadMaterial(20);
        glTranslatef(position.x, position.y - dimension.y*0.2, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        loadMaterial(20);
        glTranslatef(position.x, position.y - dimension.y*0.4, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop

}

void Ladder::draw_hitbox(){
    loadMaterial(2);
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z+1);
        glScalef(dimension.x, dimension.y, dimension.z);
        cube_unit_outline(0.5);
    glPopMatrix();
}

void Ladder::draw_fake_lad(){
   loadMaterial(7);
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y, position.z + 1 );
        glScalef(dimension.x, dimension.y, dimension.z);
        cube_unit(0.5);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        loadMaterial(20);
        glTranslatef(position.x, position.y, position.z + 1 + dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z *1.1);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        loadMaterial(20);
        glTranslatef(position.x, position.y + dimension.y*0.2, position.z + 1 + dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        loadMaterial(20);
        glTranslatef(position.x, position.y + dimension.y*0.4, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        loadMaterial(24);
        glTranslatef(position.x, position.y - dimension.y*0.2, position.z + 1);
        glScalef(dimension.x*1.05, dimension.y*0.2, dimension.z*1.1);
        cube_unit(0.5);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        loadMaterial(20);
        glTranslatef(position.x, position.y - dimension.y*0.4, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop

}

void Ladder::draw_golden(){
    loadMaterial(10);
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z+1);
        glScalef(dimension.x, dimension.y, dimension.z);
        cube_unit(0.5);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y, position.z + 1 + dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z *1.1);
        loadMaterial(17);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y + dimension.y*0.2, position.z + 1 + dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        loadMaterial(17);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y + dimension.y*0.4, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        loadMaterial(17);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y - dimension.y*0.2, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        loadMaterial(17);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y - dimension.y*0.4, position.z + 1+ dimension.z*0.5);
        glScalef(dimension.x, dimension.y*0.1, dimension.z*1.1);
        loadMaterial(17);
        cube_unit(0.5);
        loadMaterial(2);
        cube_unit_outline(0.5);
    glPopMatrix();//ladder pop

}

