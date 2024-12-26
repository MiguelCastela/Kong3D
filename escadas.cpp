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
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        global.wood_texture.bind(); // Bind the texture to the cubes

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        rect_texture_unit(1.0);
        global.wood_texture.unbind(); // Unbind the texture from the cubes
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();//ladder pop

    glPushMatrix();
        glTranslatef(position.x + dimension.x*0.45, position.y, position.z+ dimension.z *0.75) ;
        glScalef(dimension.x*0.1, dimension.y, dimension.z*0.5);
        glEnable(GL_TEXTURE_2D);
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        global.wood_texture2.bind(); // Bind the texture to the cubes
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        cube_texture_unit(1.0);
        global.wood_texture2.unbind(); // Unbind the texture from the cubes
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //for the right side of the ladder

    glPushMatrix();
    glTranslatef(position.x - dimension.x*0.45, position.y, position.z + dimension.z*0.75);
    glScalef(dimension.x*0.1, dimension.y, dimension.z*0.5);
    glEnable(GL_TEXTURE_2D);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    global.wood_texture2.bind(); // Bind the texture to the cubes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    cube_texture_unit(1.0);
    global.wood_texture2.unbind(); // Unbind the texture from the cubes
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
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        global.wood_texture3.bind(); // Bind the texture to the cubes

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        rect_texture_unit(1.0);
        global.wood_texture3.unbind(); // Unbind the texture from the cubes
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();//ladder pop

    glPushMatrix();
        glTranslatef(position.x + dimension.x*0.45, position.y + dimension.y *1.25/8 , position.z+ dimension.z *0.75) ;
        glScalef(dimension.x*0.1, dimension.y * 5.5/8, dimension.z*0.5);
        glEnable(GL_TEXTURE_2D);
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        global.wood_texture2.bind(); // Bind the texture to the cubes
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        cube_texture_unit(1.0);
        global.wood_texture2.unbind(); // Unbind the texture from the cubes
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //for the right side of the ladder

    glPushMatrix();
    glTranslatef(position.x - dimension.x*0.45, position.y + dimension.y *1.25/8, position.z + dimension.z*0.75);
    glScalef(dimension.x*0.1, dimension.y * 5.5/8, dimension.z*0.5);
    glEnable(GL_TEXTURE_2D);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    global.wood_texture2.bind(); // Bind the texture to the cubes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    cube_texture_unit(1.0);
    global.wood_texture2.unbind(); // Unbind the texture from the cubes
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
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        global.wood_texture.bind(); // Bind the texture to the cubes

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        rect_texture_unit(1.0);
        global.wood_texture.unbind(); // Unbind the texture from the cubes
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();//ladder pop

    glPushMatrix();
        glTranslatef(position.x + dimension.x*0.45, position.y, position.z+ dimension.z *0.75) ;
        glScalef(dimension.x*0.1, dimension.y, dimension.z*0.5);
        glEnable(GL_TEXTURE_2D);
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        global.wood_texture2.bind(); // Bind the texture to the cubes
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        cube_texture_unit(1.0);
        global.wood_texture2.unbind(); // Unbind the texture from the cubes
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //for the right side of the ladder

    glPushMatrix();
    glTranslatef(position.x - dimension.x*0.45, position.y, position.z + dimension.z*0.75);
    glScalef(dimension.x*0.1, dimension.y, dimension.z*0.5);
    glEnable(GL_TEXTURE_2D);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    global.wood_texture2.bind(); // Bind the texture to the cubes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    cube_texture_unit(1.0);
    global.wood_texture2.unbind(); // Unbind the texture from the cubes
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}


