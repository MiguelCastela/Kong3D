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
        void jump();
        void jumpKey();
        std::vector<float> getMarioPosition();
    private:
        GLfloat Mariosize, PositionHeight, MarioWidth, MarioDepth, MarioHeight,  StartinglevelHeight, resY;
        GLfloat positionX;
        GLfloat positionY;
        GLfloat positionZ;
        GLfloat speed;
        GLint currentPerspective;
        // Jumping variables
        bool isJumping;      // Is Mario currently jumping
        GLfloat jumpVelocity; // Initial velocity for the jump
        GLfloat gravity;     // Gravity factor to pull Mario down
        GLfloat groundLevel;


};  
#endif // MARIO_H