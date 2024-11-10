#pragma once
#ifndef MARIO_H
#define MARIO_H

class Mario {
    public:
        Mario(GLfloat Mariosize, GLfloat MarioWidth, GLfloat MarioHeight, GLfloat PositionHeight, GLfloat MarioDepth, GLfloat StartinglevelHeight, GLint resY);
        void draw();
        void moveLeft();
        void moveRight();
        void moveFront();
        void moveBack();
        void setPerspective(int perspective);
    private:
        GLfloat Mariosize, PositionHeight, MarioWidth, MarioDepth, MarioHeight,  StartinglevelHeight, resY;
        GLfloat positionX = 0.0f;
        GLfloat positionY = 0.0f;
        GLfloat positionZ = 0.0f;
        GLfloat speed = 0.1f;
        GLint currentPerspective;
};  
#endif // MARIO_H