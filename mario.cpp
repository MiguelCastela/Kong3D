#include <bits/stdc++.h>
#include "ofApp.h"
#include "mario.h"
using namespace std;


Mario::Mario(GLfloat Mariosize, GLfloat MarioWidth, GLfloat MarioHeight, GLfloat PositionHeight, GLfloat MarioDepth, GLfloat StartinglevelHeight, GLint resY, GLfloat positionWidth, GLfloat LevelDepth) {
    this-> LevelDepth = LevelDepth;
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

bool Mario::climbLadder(bool isOnLadder, int index) {
    if (isOnLadder) {
        if (positionY <= 0.0f) {
            if (ofGetKeyPressed(OF_KEY_UP)) {
            positionY -= speed;
            }
    cout << "positionY: " << positionY << endl;
    } else {
        positionY = (0.0f);
        return false;
    }
    }
    return false;
}

void Mario::moveRight(bool isOnLadder) {
    if (!isOnLadder) {
        if (ofGetKeyPressed(OF_KEY_RIGHT)) {
            if(positionX < (resY-Mariosize)*2){
                    positionX += speed; 
            }else{
                positionX = (resY-Mariosize)*2;
            }
    }
    }
}
void Mario::moveLeft(bool isOnLadder) {
    if (!isOnLadder) {
       if (ofGetKeyPressed(OF_KEY_LEFT)) {
            if(positionX > 0){
                positionX -= speed; 
            }else{
                positionX = 0;
        }
       }
    }
}
void Mario::moveFront(bool isOnLadder, int index) {
    if (!isOnLadder) {
        if (ofGetKeyPressed(OF_KEY_UP)) {
            float upperLimit = ((resY - Mariosize) / resY) - Mariosize;
            float lowerLimit = ((-resY+Mariosize)/resY)+Mariosize ;
            float Depth = upperLimit - lowerLimit; 

            
                if (index == 0){
                    if(positionZ < upperLimit){
                    positionZ += speed; 
                    }else{
                    positionZ = upperLimit;
                }
                }else{


            float adjustedUpperLimit = upperLimit + (index * ((Depth) + (Depth/2) )- (Mariosize));

            cout << "upperLimit: " << adjustedUpperLimit << endl;
            if (positionZ < adjustedUpperLimit) {
                positionZ += speed;  
            } else {
                positionZ = adjustedUpperLimit; 
            }
        }
        }
    }
}

void Mario::moveBack(bool isOnLadder, int index) {
    if (!isOnLadder) {
        if (ofGetKeyPressed(OF_KEY_DOWN)) {
            float lowerLimit = ((-resY+Mariosize)/resY)+Mariosize ;
            float upperLimit = ((resY - Mariosize) / resY) - Mariosize;
            float Depth = upperLimit - lowerLimit; 

            if(index == 0){
                if(positionZ > lowerLimit){
                positionZ -= speed; // Move back
            }else{
                positionZ = lowerLimit;
            }
            }else{
                float adjustedLowerLimit = upperLimit + ((index-1) * ((Depth) + (Depth/2))) + (Mariosize*2);
                cout << "upperLimit: " << adjustedLowerLimit << endl;
            if(positionZ > adjustedLowerLimit){
            positionZ -= speed; // Move back
            }else{
            positionZ = adjustedLowerLimit;
        }
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
    float MarioPositionZ = positionZ * (((1/speed * 1/speed)/2)+ resY/2);

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