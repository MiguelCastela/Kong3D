#include <bits/stdc++.h>
#include "ofApp.h"
#include "mario.h"
using namespace std;


Mario::Mario(GLfloat Mariosize, GLfloat MarioWidth, GLfloat MarioHeight, GLfloat PositionHeight, GLfloat MarioDepth, GLfloat StartinglevelHeight, GLint resY) {
    this->Mariosize = Mariosize;
    this->PositionHeight = PositionHeight;
    this->MarioWidth = MarioWidth;
    this->MarioDepth = MarioDepth;
    this->MarioHeight = MarioHeight;
    if(StartinglevelHeight != 0){
        this->StartinglevelHeight = StartinglevelHeight;
    }else{
        this->StartinglevelHeight = 0;
    }
    this->positionX = 0.0f;
    this->positionY = 0.0f;
    this->positionZ = 0.0f;
    this->speed = 0.1f;
    this->resY = resY;
    this->jumpVelocity = 0.13f; 
    this->gravity = 0.01f;   
    this->groundLevel = (gh() * 0.5) + (StartinglevelHeight * PositionHeight) + ((PositionHeight / 2) - (Mariosize * PositionHeight / 2));
    this->isJumping = false;
}

void Mario::draw() {
    glColor3f(1, 0, 0);
    glPushMatrix();//base push
    glTranslatef(gw() * 0.5, groundLevel , 0);
    glScalef(MarioWidth, MarioHeight, MarioDepth);
    glTranslatef(positionX, positionY, positionZ);
    cube_unit(Mariosize);
    cube_unit_outline(Mariosize);
    glPopMatrix();//level pop
    glColor3f(0, 0, 0);
}
void Mario::setPerspective(int perspective) {
    if (currentPerspective != perspective) {
        // Adjust Mario's position based on the new perspective
        if (perspective == 1) {
            // For perspective 1, ensure Mario's position is correct
            positionX = abs(positionX);  // Ensure Mario is in the positive X direction
        } else if (perspective == 2) {
            // For perspective 2, invert Mario's X position
            positionX = -abs(positionX);  // Ensure Mario is in the negative X direction
        }
    }
    currentPerspective = perspective;
}

void Mario::moveRight() {
        if (ofGetKeyPressed(OF_KEY_RIGHT)) {
            if(currentPerspective == 1){
                    positionX += speed; 
            }else if(currentPerspective == 2){
            positionX -= speed;
            }
            if(positionX < -resY+Mariosize){
                positionX = -resY+Mariosize;
            }
        }
}
void Mario::moveLeft() {
       if (ofGetKeyPressed(OF_KEY_LEFT)) {
            if(currentPerspective == 1){

                positionX -= speed; 
            }else if(currentPerspective == 2){
            positionX += speed;   
            }
            if(positionX > resY-Mariosize){
                positionX = resY-Mariosize;
        }
       }
}
void Mario::moveFront() {
        if (ofGetKeyPressed(OF_KEY_UP)) {
            positionZ -= speed; // Move front  
        if(positionZ < ((-resY+Mariosize)/resY)+Mariosize){
            positionZ = ((-resY+Mariosize)/resY)+Mariosize;

        }
}
}
void Mario::moveBack() {
        if (ofGetKeyPressed(OF_KEY_DOWN)) {
            positionZ += speed; // Move back

        if(positionZ > ((resY-Mariosize)/resY)-Mariosize){
            positionZ = ((resY-Mariosize)/resY)-Mariosize;
        }
        }
}
    

void Mario::jumpKey() {
    if (ofGetKeyPressed(' ') && !isJumping) { // Jump only if Mario is not already jumping
        isJumping = true;
        jumpVelocity = 0.13f; // Reset jump velocity
    }
}

// Handle jump logic
void Mario::jump() {
    if (isJumping) {
        positionY -= jumpVelocity;     
        jumpVelocity -= gravity;        

        if (positionY >= 0.0f) { 
            positionY = 0.0f;    
            isJumping = false;         
            jumpVelocity = 0.13f;        
        }
    }
}
