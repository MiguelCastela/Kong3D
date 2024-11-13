#include <bits/stdc++.h>
#include "ofApp.h"
#include "escadas.h"
using namespace std;

Ladder::Ladder(GLfloat ladderWidth, GLfloat ladderHeight, GLfloat ladderDepth, GLfloat height, GLint resY) {
    this->ladderWidth = ladderWidth;
    this->ladderHeight = ladderHeight;
    this->ladderDepth = ladderDepth;
    if(height != 0){
        this->height = height;
    }else{
        this->height = 0;
    }
    this->resY = resY;
    int tmp = resY/2;
    this->ladderOffset = (rand() % resY) - tmp;
    this->escadasx = gw() * 0.5 + (((gw()/2)/resY)*ladderOffset);
    this->escadasy = ((gh() * 0.5) + (height * ladderHeight))- ladderHeight;
    this->escadasz = ladderDepth/2 + ladderDepth/resY;


}


void Ladder::draw(int index){
    glColor3f(0.5f, 0.2f, 0.0f);
    glPushMatrix();//ladder push
        glTranslatef(escadasx, escadasy, abs(index * ladderDepth)+escadasz);
        glScalef(ladderWidth/resY, ladderHeight, ladderDepth/resY);
        cube_unit(0.5);
    glPopMatrix();//ladder pop
}


void Ladder::setIndex(int idx) {
    index = idx;
    
}

int Ladder::getIndex() const {
    return index;
}

/*
void Platform::addLadderPosition(int levelIndex, float x, float y, float z) {
    LadderPosition newLadder = { levelIndex, x, y, z, levelWidth / resY, levelHeight, levelDepth / resY };
    ladderPositions.push_back(newLadder);
}

LadderPosition Platform::getLadderPosition(int levelIndex) const {
    for (const auto& ladder : ladderPositions) {
        if (ladder.levelIndex == levelIndex) {
            return ladder;
        }
    }
    return 1;
}
*/