#include "donkey_kong.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include "global.h"
#include "ofApp.h"

using namespace std;

Kong::Kong(ofVec3f dimensions, ofVec3f position) {
    this->dimensions = dimensions;
    this->position = position;
}

void Kong::draw() {
    //rotate kong
    glPushMatrix();  
        glTranslatef(position.x, position.y, position.z);  
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); 
        glTranslatef(-position.x, -position.y, -position.z); 
        // Draw body
        glPushMatrix();
            glColor3f(0.5, 0.35, 0.05);
            glTranslatef(position.x, position.y, position.z);  
            glScalef(dimensions.x, dimensions.y, dimensions.z);  
            cube_unit(0.5); 
            glColor3f(0.0, 0.0, 0.0);
            cube_unit_outline(0.5);
        glPopMatrix();  
        //draw left arm
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.5, position.y , position.z + dimensions.z *0.5);  
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glScalef(dimensions.x * 0.5, dimensions.y , dimensions.z * 0.25); 
            glColor3f(0.5, 0.35, 0.05); 
            cube_unit(0.5);  
            glColor3f(0.0, 0.0, 0.0);
            cube_unit_outline(0.5);  
            //left hand
            glPushMatrix();
                glTranslatef(0.0f, 0.05f, 0.0f); 
                glScalef(0.7f, 1.05f, 0.7f);  
                glColor3f(0.55, 0.35, 0.05); 
                cube_unit(0.5);  
                glColor3f(0.0, 0.0, 0.0);  
                cube_unit_outline(0.5);  
            glPopMatrix();
        glPopMatrix(); 
        //draw right arm
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.5, position.y  , position.z + dimensions.z*0.5);  
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glScalef(dimensions.x * 0.5, dimensions.y, dimensions.z * 0.25); 
            glColor3f(0.5, 0.35, 0.05); 
            cube_unit(0.5);  
            glColor3f(0.0, 0.0, 0.0);
            cube_unit_outline(0.5); 
            //right hand 
            glPushMatrix();
                glTranslatef(0.0f, 0.05f, 0.0f);  
                glScalef(0.7f, 1.05f, 0.7f);  
                glColor3f(0.55, 0.35, 0.05);  
                cube_unit(0.5);  
                glColor3f(0.0, 0.0, 0.0);  
                cube_unit_outline(0.5);  
            glPopMatrix();
        glPopMatrix();  
        // Draw head
        glPushMatrix();
            glTranslatef(position.x, position.y + dimensions.y * 0.5, position.z);  
            glScalef(dimensions.x * 0.75, dimensions.y, dimensions.z * 0.75);  
            glColor3f(0.5, 0.35, 0.05); 
            cube_unit(0.5);  
            glColor3f(0.0, 0.0, 0.0);
            cube_unit_outline(0.5);  
        glPopMatrix(); 
        // Draw left eye
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.4);  
            glScalef(dimensions.x * 0.2, dimensions.y * 0.2, dimensions.z * 0.2);  
            glColor3f(1.0, 1.0, 1.0); 
            cube_unit(0.5);  
        glPopMatrix(); 

        // Draw right eye
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.4);  
            glScalef(dimensions.x * 0.2, dimensions.y * 0.2, dimensions.z * 0.2);  
            glColor3f(1.0, 1.0, 1.0); 
            cube_unit(0.5); 
        glPopMatrix();  
        // Draw left pupil
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.5);
            glScalef(dimensions.x * 0.1, dimensions.y * 0.1, dimensions.z * 0.1); 
            glColor3f(0.0, 0.0, 0.0);  
            cube_unit(0.5);  
        glPopMatrix();  
        // Draw right pupil
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.5);
            glScalef(dimensions.x * 0.1, dimensions.y * 0.1, dimensions.z * 0.1);  
            glColor3f(0.0, 0.0, 0.0);  
            cube_unit(0.5);  
        glPopMatrix();  

        //draw belly
        glPushMatrix();
            glTranslatef(position.x, position.y, position.z + dimensions.z*0.05);  
            glScalef(dimensions.x*0.6 , dimensions.y*0.6 , dimensions.z);  
            glColor3f(0.75, 0.5, 0.1);  
            cube_unit(0.5); 
        glPopMatrix();  
    glPopMatrix();//global pop
}
