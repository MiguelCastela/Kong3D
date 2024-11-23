#pragma once
#ifndef PAULINE_H
#define PAULINE_H

#include "ofMain.h"

class Pauline {
    public:
        Pauline(ofVec3f dimensions, ofVec3f position);
        void draw();
        ofVec3f dimensions;
        ofVec3f position;
};


#endif // PAULINE_H


