#include "pauline.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include "global.h"
#include "ofApp.h"

using namespace std;

Pauline::Pauline(ofVec3f dimensions, ofVec3f position) {
    this->dimensions = dimensions;
    this->position = position;
    this->winState = false;

    this->isJumping = false;
    this->jumpStartY = position.y;  
    this->jumpVelocity = 0.0f * (60.0 / ofGetFrameRate());      
    this->gravity = -0.9f * (60.0 / ofGetFrameRate());          
    this->jumpHeight = 1.5f;        
}


void Pauline::draw() {
    update();
    //global push because of winstate
    glPushMatrix();  
        if(winState){
            glTranslatef(position.x, position.y, position.z); 
            glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);  
            glTranslatef(-position.x, -position.y, -position.z); 
            }
            glColor3f(1.0, 0.6, 0.8);
        glPushMatrix();
            glTranslatef(position.x, position.y, position.z);
            glScalef(dimensions.x, dimensions.y, dimensions.z);
            cube_unit(0.5);
            cube_unit_outline(0.5);
        glPopMatrix();
        //left arm
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.5, position.y, position.z);  
            glScalef(dimensions.x * 0.5, dimensions.y * 0.5, dimensions.z * 0.25);  
            if (winState) {
                glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
            }
            glColor3f(1.0, 0.6, 0.8);
            cube_unit(0.5);  
            glColor3f(0.0, 0.0, 0.0);
            cube_unit_outline(0.5);  
        glPopMatrix();  
        //draw left hand
        glPushMatrix(); 
            glTranslatef(position.x - dimensions.x * 0.5, position.y, position.z);  
            if (winState) {
                glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
            }
            glTranslatef(0, -dimensions.y * 0.30, 0); 
            glScalef(dimensions.x * 0.4, dimensions.y * 0.05, dimensions.z * 0.15);
            glColor3f(1.0, 0.8, 0.6);  
            cube_unit(0.5);
            glColor3f(0.0, 0.0, 0.0);
            cube_unit_outline(0.5);  
        glPopMatrix(); 
        //draw right arm
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.5, position.y, position.z);
            if (winState) {
                glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
            }
            glScalef(dimensions.x * 0.5, dimensions.y * 0.5, dimensions.z * 0.25); 
            glColor3f(1.0, 0.6, 0.8);
            cube_unit(0.5);  
            glColor3f(0.0, 0.0, 0.0);
            cube_unit_outline(0.5);  
        glPopMatrix(); 
        //right hand
        glPushMatrix(); 
            glTranslatef(position.x + dimensions.x * 0.5, position.y, position.z); 
            if (winState) {
                glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
            }
            glTranslatef(0, -dimensions.y * 0.30, 0);  
            glScalef(dimensions.x * 0.4, dimensions.y * 0.05, dimensions.z * 0.15);  
            glColor3f(1.0, 0.8, 0.6);  
            cube_unit(0.5); 
            glColor3f(0.0, 0.0, 0.0);
            cube_unit_outline(0.5);  
        glPopMatrix();  
        // Draw the head
        glPushMatrix();
            glTranslatef(position.x, position.y + dimensions.y * 0.5, position.z);  
            glScalef(dimensions.x * 0.75, dimensions.y, dimensions.z * 0.75); 
            glColor3f(1.0, 0.8, 0.6);  
            cube_unit(0.5);  
            cube_unit_outline(0.5);  
        glPopMatrix(); 
        //draw blonde hair 
        glPushMatrix();
            glTranslatef(position.x , position.y + 0.2 + dimensions.y * 0.5, position.z); 
            glScalef(dimensions.x *0.95 , dimensions.y * 1.2, dimensions.z *0.74); 
            glColor3f(1.0, 1.0, 0.0);
            cube_unit(0.5); 
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
        glPopMatrix();  // Reset transformations for the right pupil
    glPopMatrix();  // Reset the global transformation state


}

void Pauline::update() {
    if (winState && !isJumping) {
        isJumping = true;
        jumpVelocity = 1.5f * (60.0 / ofGetFrameRate());  
    }

    if (isJumping) {
        position.y += jumpVelocity;
        jumpVelocity += gravity;  
        
        
        if (position.y <= jumpStartY) {
            position.y = jumpStartY;
            isJumping = false;        
            jumpVelocity = 0.0f * (60.0 / ofGetFrameRate());     
        }
    }
}
