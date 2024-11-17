#pragma once

#include "ofMain.h"

class Global{
    public:
        Global();

        ofVec3f platDim;
        ofVec3f ladDim;
        ofVec3f marioDim;

        GLfloat left_limit;
        GLfloat right_limit;

        GLfloat empty_space;
};

extern Global global;