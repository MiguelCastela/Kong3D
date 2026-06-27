#pragma once
#ifndef PARTICULAS_H
#define PARTICULAS_H

#include "global.h"


class Particle{
    public:
    Particle(ofVec3f position, ofVec3f dimensions, int materialIndex);
    void draw();
    void update();
    ~Particle();

    ofVec3f position;
    ofVec3f dimensions;
    ofVec3f velocity;
    float lifetime;
    bool isAlive;
    int materialIndex;



};
#endif // PARTICULAS_H