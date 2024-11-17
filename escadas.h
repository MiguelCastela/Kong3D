#pragma once 
#ifndef ESCADAS_H
#define ESCADAS_H


class Ladder{
    public:
        Ladder(ofVec3f dimension, ofVec3f position);
        void draw();
        ofVec3f dimension;
        ofVec3f position;
};
#endif // ESCADAS_H
