#pragma once
#ifndef MARIO_H
#define MARIO_H

class Mario {
    public:
        Mario(GLfloat Size, GLfloat PositionHeight, GLfloat PositionWidth, GLfloat PositionDepth, GLfloat StartinglevelHeight, GLfloat resY);
        void draw();
    private:
        GLfloat size, PositionHeight, PositionWidth, PositionDepth,  StartinglevelHeight, resY;
};
#endif // MARIO_H