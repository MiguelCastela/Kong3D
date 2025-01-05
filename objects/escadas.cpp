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
        glScalef(dimension.x, dimension.y, dimension.z*0.000001);
        //cube_unit(0.5);
        //cube_unit_outline(0.5);
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        global.wood_texture.bind(); 

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        rect_texture_unit(1.0);
        global.wood_texture.unbind(); 
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //right side of the ladder
    glPushMatrix();
        glTranslatef(position.x + dimension.x*0.45, position.y, position.z+ dimension.z *0.75) ;
        glScalef(dimension.x*0.1, dimension.y, dimension.z*0.5);
        glEnable(GL_TEXTURE_2D);

        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        global.wood_texture2.bind(); 
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        cube_texture_unit(1.0);
        global.wood_texture2.unbind(); 
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //left side of the ladder
    glPushMatrix();
    glTranslatef(position.x - dimension.x*0.45, position.y, position.z + dimension.z*0.75);
    glScalef(dimension.x*0.1, dimension.y, dimension.z*0.5);
    glEnable(GL_TEXTURE_2D);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    global.wood_texture2.bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    cube_texture_unit(1.0);
    global.wood_texture2.unbind(); 
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

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
    loadMaterial(26);
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y, position.z + 1 );
        glScalef(dimension.x, dimension.y, dimension.z);
        //cube_unit(0.5);
        //cube_unit_outline(0.5);
        glEnable(GL_TEXTURE_2D);

        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        global.wood_texture3.bind(); 

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        rect_texture_unit(1.0);
        global.wood_texture3.unbind(); 
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();//ladder pop

    //right side of the ladder
    glPushMatrix();
        glTranslatef(position.x + dimension.x*0.45, position.y + dimension.y *1.25/8 , position.z+ dimension.z *0.70) ;
        glScalef(dimension.x*0.1, dimension.y * 5.5/8, dimension.z*0.50);
        glEnable(GL_TEXTURE_2D);

        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        global.wood_texture2.bind();
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        cube_texture_unit(1.0);
        global.wood_texture2.unbind(); 
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //left side of the ladder
    glPushMatrix();
    glTranslatef(position.x - dimension.x*0.45, position.y + dimension.y *1.25/8, position.z + dimension.z*0.70);
    glScalef(dimension.x*0.1, dimension.y * 5.5/8, dimension.z*0.425);
    glEnable(GL_TEXTURE_2D);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    global.wood_texture2.bind(); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    cube_texture_unit(1.0);
    global.wood_texture2.unbind(); 
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}




void Ladder::draw_golden(){
    loadMaterial(17);
    glPushMatrix();//ladder push
        glTranslatef(position.x, position.y, position.z + 1 );
        glScalef(dimension.x, dimension.y, dimension.z);
        //cube_unit(0.5);
        //cube_unit_outline(0.5);
        glEnable(GL_TEXTURE_2D);

        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        global.wood_texture.bind(); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        rect_texture_unit(1.0);
        global.wood_texture.unbind(); 
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //right side of the ladder
    glPushMatrix();
        glTranslatef(position.x + dimension.x*0.45, position.y, position.z+ dimension.z *0.75) ;
        glScalef(dimension.x*0.1, dimension.y, dimension.z*0.5);
        glEnable(GL_TEXTURE_2D);

        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        global.wood_texture2.bind(); 
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        cube_texture_unit(1.0);
        global.wood_texture2.unbind(); 
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //left side of the ladder
    glPushMatrix();
    glTranslatef(position.x - dimension.x*0.45, position.y, position.z + dimension.z*0.75);
    glScalef(dimension.x*0.1, dimension.y, dimension.z*0.5);
    glEnable(GL_TEXTURE_2D);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    global.wood_texture2.bind(); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    cube_texture_unit(1.0);
    global.wood_texture2.unbind();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}


