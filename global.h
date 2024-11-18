#pragma once

#include "ofMain.h"

class Global{
    public:
        Global();

        ofVec3f platDim;
        ofVec3f ladDim;
        ofVec3f ladHitBoxDim;
        ofVec3f marioDim;
        ofVec3f barrelDim;

        GLfloat left_limit;
        GLfloat right_limit;

        GLfloat empty_space;
};

extern Global global;