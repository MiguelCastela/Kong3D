#include <algorithm>
#include <cmath>
#include <vector>
#include "ofApp.h"
#include "background.h"
#include "materials.h"
using namespace std;


Background::Background() {
}

void Background::draw() {
    global.background_texture.bind();
        loadMaterial(5);

    glPushMatrix();//ladder push
        glTranslatef(0,0,0 );
        glScalef(gw()*2, gh()*2, 1);
        //cube_unit(0.5);
        //cube_unit_outline(0.5);
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        global.background_texture.bind(); 

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        rect_texture_unit(1.0);
        global.background_texture.unbind(); 
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}