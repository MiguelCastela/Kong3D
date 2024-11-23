#pragma once
#ifndef DONKEY_KONG_H
#define DONKEY_KONG_H

#include "ofMain.h"

class Kong {
    public:
        Kong(ofVec3f dimensions, ofVec3f position);
        void draw();
        ofVec3f dimensions;
        ofVec3f position;
};

#endif // DONKEY_KONG_H


