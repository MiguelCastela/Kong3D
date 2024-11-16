#include <bits/stdc++.h>
#include "ofApp.h"
#include "escadas.h"
using namespace std;

Ladder::Ladder(GLfloat ladderWidth, GLfloat ladderHeight, GLfloat ladderDepth, GLfloat height, GLint resY, GLfloat ladderPosWidth) {
    this -> ladderPosWidth = ladderPosWidth;
    this->ladderWidth = ladderWidth/resY;
    this->ladderHeight = ladderHeight;
    this->ladderDepth = ladderDepth/resY;
    if(height != 0){
        this->height = height;
    }else{
        this->height = 0;
    }
    this->resY = resY;
    int tmp = resY/2;
    this->ladderOffset = (rand() % resY) - tmp;
    this->escadasx = 0.0f;
    this->escadasy = 0.0f;
    this->escadasz = 0.0f;
    this->adjustedescadasz = escadasz;


}


void Ladder::draw(int index){
    adjustedescadasz = abs(index * (ladderDepth*resY))+  (ladderDepth*resY)/2 + ladderDepth/2;
    escadasy = ((gh() * 0.5) + (height * ladderHeight))- ladderHeight;
    escadasx = gw() * 0.5 + (((gw()/2)/resY)*ladderOffset);
    //escadasx = ladderPosWidth + (((gw()/2)/resY)*ladderOffset);
    glColor3f(0.5f, 0.2f, 0.0f);
    glPushMatrix();//ladder push
        glTranslatef(escadasx, escadasy, escadasz + adjustedescadasz);
        glScalef(ladderWidth, ladderHeight, ladderDepth);
        cube_unit(0.5);
        cube_unit_outline(0.5);
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