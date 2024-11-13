#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H
#include <vector>

struct LadderPosition {
    int levelIndex;
    float x, y, z; 
    float width, height, depth;
};


class Platform {
public:
    Platform(GLfloat levelWidth,GLfloat levelHeight,GLfloat levelDepth, GLfloat height, GLint resY);
    void draw(int index);    
    void setIndex(int idx);
    int getIndex() const;
private:
    GLfloat levelWidth, levelHeight, levelDepth, height;
    GLint resY;
    int index, idx;
    int ladderOffset;
    std::vector<LadderPosition> ladderPositions;

    
};
#endif // PLATFORM_H