#pragma once

#ifndef PLATFORM_H
#define PLATFORM_H
#include <vector>

class Platform {
public:
    Platform(ofVec3f position,ofVec3f dimensions);
    void draw();
    ofVec3f position;
    ofVec3f dimensions;

};

#endif // PLATFORM_H