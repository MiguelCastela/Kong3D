#pragma once

#ifndef PLATFORM_H
#define PLATFORM_H
#include <vector>

class Platform {
public:
    Platform(ofVec3f position,ofVec3f dimensions,ofVec3f color);
    void draw();
    ofVec3f position;
    ofVec3f dimensions;
    ofVec3f color;

};

#endif // PLATFORM_H