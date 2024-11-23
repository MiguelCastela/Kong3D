#pragma once
#ifndef PARTICULAS_H
#define PARTICULAS_H

#include "global.h"


class Particle{
    public:
    Particle(ofVec3f position, ofVec3f dimensions, ofVec3f color);
    void draw();
    void update();

    ofVec3f position;
    ofVec3f dimensions;
    ofVec3f color;
    ofVec3f velocity;



};
#endif // PARTICULAS_H