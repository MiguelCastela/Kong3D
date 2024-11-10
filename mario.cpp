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
}

void Mario::draw() {
    glColor3f(0, 1, 1);
    glPushMatrix();//base push
    glTranslatef(gw() * 0.5, (gh() * 0.5) + (StartinglevelHeight * PositionHeight) + (MarioHeight/2) , 0);
    glScalef(MarioWidth, MarioHeight, MarioDepth);
    glTranslatef(positionX, positionY, positionZ);
    cube_unit(Mariosize);
    glPopMatrix();//level pop
}

void Mario::moveRight() {
        if (ofGetKeyPressed(OF_KEY_RIGHT)) {
            if(currentPerspective == 1){
                positionX += speed; 
            }else if(currentPerspective == 2){
            positionX -= speed; 
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
        }
}
void Mario::moveFront() {
        if (ofGetKeyPressed(OF_KEY_UP)) {
            positionZ -= speed; // Move front
    }
}
void Mario::moveBack() {
        if (ofGetKeyPressed(OF_KEY_DOWN)) {
            positionZ += speed; // Move back
    }
}
/*
void Movement::jump()
{
    if (impulse)
    {
        if (jumpImpulseFrameCounter > jumpImpulseNumFrames)
        {
            impulse = false;
        }
        jumpImpulseFrameCounter++;
    }
    else
    {
        jumpForce = 0.;
    }

    if (jumping)
    {
        avatarAccelMod = (jumpForce + Fg) / float(avatarMass);
        avatarVelMod += avatarAccelMod;

        // testCollision with floor
        if ((avatarPos.y + avatarVelMod - avatarSize * 0.5) <= -gh() * 0.5)
        {
            avatarPos.y = -gh() * 0.5 + avatarSize * 0.5;
            avatarAccelMod = 0.;
            avatarVelMod = 0.;
            jumpForce = 0.;
            impulse = false;
            jumping = false;
        }
        else
        {
            avatarPos.y += avatarVelMod;
        }
    }
}
*/
void Mario::setPerspective(int perspective) {
    currentPerspective = perspective;
}
