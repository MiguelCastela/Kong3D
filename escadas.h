#pragma once 
#ifndef ESCADAS_H
#define ESCADAS_H


class Ladder{
    public:
        Ladder(GLfloat ladderWidth, GLfloat ladderHeight, GLfloat ladderDepth, GLfloat height, GLint resY);
        void draw(int index);
        void setIndex(int idx);
        int getIndex() const;
        //void addLadderPosition(int levelIndex, float x, float y, float z);
        //LadderPosition getLadderPosition(int levelIndex) const;
        int escadasx, escadasy, escadasz;

    private:
        GLfloat ladderWidth, ladderHeight, ladderDepth, height;
        GLint resY, ladderOffset;
        int index, idx;
};
#endif // ESCADAS_H
