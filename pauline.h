#pragma once
#ifndef PAULINE_H
#define PAULINE_H

#include "ofMain.h"

class Pauline {
    public:
        Pauline(ofVec3f dimensions, ofVec3f position);
        void draw();
        void update();
        ofVec3f dimensions;
        ofVec3f position;
        bool winState;
        bool isJumping;
        GLfloat jumpVelocity;
        GLfloat gravity;
        GLfloat jumpHeight;
        GLfloat jumpStartY;
        


        
};


#endif // PAULINE_H


