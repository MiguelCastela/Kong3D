#pragma once
#ifndef MARIO_H
#define MARIO_H

class Mario {
    public:
        Mario(GLfloat Mariosize, GLfloat MarioWidth, GLfloat MarioHeight, GLfloat PositionHeight, GLfloat MarioDepth, GLfloat StartinglevelHeight, GLint resY, GLfloat positionWidth, GLfloat LevelDepth);
        void draw();
        void moveLeft(bool isOnLadder);
        void moveRight(bool isOnLadder);
        void moveFront(bool isOnLadder, int index);
        bool climbLadder(bool isOnLadder, int index);
        void moveBack(bool isOnLadder, int index);
        void jump();
        void jumpKey(bool isOnLadder);
        std::vector<float> getMarioPosition();
        int MarioOnLevel; 
        int getMarioOnLevel() const { return MarioOnLevel; }
    private:
        bool climbing; // Flag for whether Mario is climbing
        float climbingStartY; // Mario's starting Y position when climbing
        float climbMaxHeight; // Maximum height Mario can climb
        GLfloat Mariosize, PositionHeight, MarioWidth, MarioDepth, MarioHeight,  StartinglevelHeight, resY;
        bool isOnLadder;
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
        GLfloat positionWidth;
        GLfloat LevelDepth;



};  
#endif // MARIO_H