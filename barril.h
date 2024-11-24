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
        float next_position_y;
        bool leave_ladder;
        bool moving_x;
        bool moving_y;
        bool moving_z;
        bool moving_down;
        enum BarrelState { MOVING_X, MOVING_Z, MOVING_Y };
        BarrelState currentState;
        bool is_active; 

    

};
#endif // BARRIL_H