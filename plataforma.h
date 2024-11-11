#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H
class Platform {
public:
    Platform(GLfloat levelWidth,GLfloat levelHeight,GLfloat levelDepth, GLfloat height, GLint resY);
    void draw();    
private:
    GLfloat levelWidth, levelHeight, levelDepth, height, resY;

    
};
#endif // PLATFORM_H