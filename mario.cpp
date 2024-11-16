#include <bits/stdc++.h>
#include "ofApp.h"
#include "mario.h"
using namespace std;


Mario::Mario(GLfloat Mariosize, GLfloat MarioWidth, GLfloat MarioHeight, GLfloat PositionHeight, GLfloat MarioDepth, GLfloat StartinglevelHeight, GLint resY, GLfloat positionWidth) {
    this->Mariosize = Mariosize;
    this->MarioOnLevel = 0;
    this->PositionHeight = PositionHeight;
    this->MarioWidth = MarioWidth;
    this->MarioDepth = MarioDepth;
    this->MarioHeight = MarioHeight;
    this->positionWidth  = positionWidth;
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
        glTranslatef(positionWidth, groundLevel , 0);
        glScalef(MarioWidth, MarioHeight, MarioDepth);
        glTranslatef(positionX, positionY, positionZ);
        cube_unit(Mariosize);
        cube_unit_outline(Mariosize);
    glPopMatrix();//level pop
    glColor3f(0, 0, 0);
}

bool Mario::climbLadder(bool isOnLadder) {
    if (isOnLadder) {
        if (positionY <= 0.0f) {
            if (ofGetKeyPressed(OF_KEY_UP)) {
            positionY -= speed;
            }
            if (ofGetKeyPressed(OF_KEY_DOWN)) {
                positionY += speed;
            }
    } else {
        positionY = 0.0f;
        return false;
    }
    }
    return false;
}

void Mario::moveRight() {
        if (ofGetKeyPressed(OF_KEY_RIGHT)) {
            if(positionX < (resY-Mariosize)*2){
                    positionX += speed; 
            }else{
                positionX = (resY-Mariosize)*2;
            }
    }
}
void Mario::moveLeft() {
       if (ofGetKeyPressed(OF_KEY_LEFT)) {
            if(positionX > 0){
                positionX -= speed; 
            }else{
                positionX = 0;
        }
    }
}
void Mario::moveFront(bool isOnLadder) {
    if (!isOnLadder) {
        if (ofGetKeyPressed(OF_KEY_UP)) {
            if(positionZ < ((resY-Mariosize)/resY)-Mariosize){
            positionZ += (speed); // Move front  
        }
        else{
            positionZ = ((resY-Mariosize)/resY)-Mariosize;

        }
        }
    }
}
void Mario::moveBack(bool isOnLadder) {
    if (!isOnLadder) {
        if (ofGetKeyPressed(OF_KEY_DOWN)) {
            if(positionZ > ((-resY+Mariosize)/resY)+Mariosize){
            positionZ -= speed; // Move back
        }else{
            positionZ = ((-resY+Mariosize)/resY)+Mariosize;
        }
        }
    }
}

void Mario::jumpKey(bool isOnLadder) {
    if (!isOnLadder && ofGetKeyPressed(' ') && !isJumping) { // Jump only if Mario is not already jumping
        isJumping = true;
        jumpVelocity = 0.13f; // Reset jump velocity
    }
}
std::vector<float> Mario::getMarioPosition() {

    float MarioPositionX = (positionX * (((1/speed * 1/speed)/2)+ resY/2)) + (gw()/4);
    float MarioPositionY = (positionY * (((1/speed * 1/speed)/2)+ resY/2)) + groundLevel;
    float MarioPositionZ = positionZ * (resY * resY);

    return {MarioPositionX, MarioPositionY, MarioPositionZ};
}

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