#pragma once
#ifndef MARIO_H
#define MARIO_H

class Mario {
    public:
        Mario(ofVec3f dimensions, ofVec3f position);
        void draw();
        void jump();
        void start_jump();
        void move_left();
        void move_right();
        void climb_up();
        void go_down();
        void climb_down();
        void draw_pov();
        void spawn_back();


        float respawnStartTime;  // Tracks the time when respawn was triggered.
        bool isRespawning; 

        // Positioning
        ofVec3f dimensions;
        ofVec3f position;
        ofVec3f marioLookAt;
    
        // Jumping
        GLfloat jump_vel_const;
        GLfloat pre_jump_y;
        bool isJumping;      // Is Mario currently jumping
        GLfloat jumpVelocity; // Initial velocity for the jump
        GLfloat gravity;     // Gravity factor to pull Mario down

        //movement
        GLfloat speed;
        bool on_ladder;
        bool is_climbing;
        GLfloat base_position_y;
        GLfloat next_position_y;



};  
#endif // MARIO_H