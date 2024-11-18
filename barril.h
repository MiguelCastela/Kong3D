#pragma once
#ifndef BARRIL_H
#define BARRIL_H


class Barrel{
    public:
        Barrel(ofVec3f dimensions, ofVec3f position);
        void draw();
        void move_front();
        void move_back();
        void move_down();
        ofVec3f dimensions;
        ofVec3f position;
        bool on_ladder;
        bool is_moving_left;
        float position_x_on_impact;
        float speed;
        float next_position_z;
    

};
#endif // BARRIL_H