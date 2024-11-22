#include <bits/stdc++.h>
#include "ofApp.h"
#include "mario.h"
#include "global.h"

using namespace std;


Mario::Mario(ofVec3f dimensions, ofVec3f position) {
    this->gravity = 0.015f * (60.0 / ofGetFrameRate());   
    this->isJumping = false;
    this->dimensions = dimensions;
    this->position = position;
    this->speed = 1.0 * (60.0 / ofGetFrameRate());

    this->on_ladder = false; 
    this->is_climbing = false;
    this->jump_vel_const = 0.5f * (60.0 / ofGetFrameRate());
    this->jumpVelocity = jump_vel_const;
    this->pre_jump_y = 0;

    this->base_position_y = 0;
    this->next_position_y = 0;

    this->isRespawning = false;
    

    this->marioLookAt = ofVec3f(global.right_limit*2, position.y, position.z);
}

void Mario::draw() {
    jump();
    glColor3f(1, 0, 0);
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(dimensions.x, dimensions.y, dimensions.z);
        //if(camera.camFlag = true){
            cube_unit(0.5);
        //}
        cube_unit_outline(0.5);
    glPopMatrix();
}

void Mario::draw_pov(){
    jump();
    glColor3f(1, 0, 0);
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(dimensions.x, dimensions.y, dimensions.z);
        cube_unit(0.5);
        cube_unit_outline(0.5);
    glPopMatrix();
}

void Mario::spawn_back() {
    float currentTime = ofGetElapsedTimef();

    if (!isRespawning) {
        // Start the respawn timer
        respawnStartTime = currentTime;
        isRespawning = true;
        return;
    }

    if (currentTime - respawnStartTime >= 5.0f && position != global.marioPos) {
        // Move Mario to the respawn position after 5 seconds
        position = global.marioPos;
        is_climbing = false;
        on_ladder = false;
        isJumping = false;
        pre_jump_y = 0;
        base_position_y = 0;
        next_position_y = 0;

        // Update the timer to track the additional 1 second in respawning state
        respawnStartTime = currentTime;
    }

    if (currentTime - respawnStartTime >= 1.0f && position == global.marioPos) {
        // Exit the respawning state after 1 second at the respawn position
        isRespawning = false;
    }
}


void Mario::start_jump() {
    if (!isJumping && !is_climbing) { // Jump only if Mario is not already jumping
        isJumping = true;
        jumpVelocity = jump_vel_const; // Reset jump velocity
        pre_jump_y = position.y;
    }
}

void Mario::jump() {
    if (isJumping && !is_climbing) {
        position.y += jumpVelocity;     
        jumpVelocity -= gravity;        

        if (position.y <= pre_jump_y) { 
            position.y = pre_jump_y;    
            isJumping = false;         
            jumpVelocity = jump_vel_const;        
        }
    }
}

void Mario::move_left(){
    marioLookAt = ofVec3f(global.left_limit*2, position.y, position.z);
    if (position.x > global.left_limit){
        position.x -= speed;
    }else{
        position.x = global.left_limit;
    }
}

void Mario::move_right(){
    marioLookAt = ofVec3f(global.right_limit*2, position.y, position.z);

    if (position.x < global.right_limit){
        position.x += speed;
    }else{
        position.x = global.right_limit;
    }
}

void Mario::climb_up(){
    is_climbing = true;
    marioLookAt.y = position.y + 50;
    marioLookAt.x = position.x;
    marioLookAt.z = position.z - 20;


    position.y += speed;
    if(position.y >= next_position_y){
        base_position_y = next_position_y;
        is_climbing = false;
        position.z -= global.platDim.z;
    }

}
void Mario::climb_down(){
    is_climbing = true;
    marioLookAt.y = position.y - 1;
    marioLookAt.x = position.x;
    marioLookAt.z = position.z + 2;
    
    
    position.y -= 0.5;
    if(position.y <= base_position_y){
        position.y = base_position_y;
        is_climbing = false;
    }
}

void Mario::go_down(){
    //cout << "going down" << endl;
    position.y = base_position_y;
}

