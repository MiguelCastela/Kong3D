#include <bits/stdc++.h>
#include "ofApp.h"
#include "barril.h"
#include "global.h"

using namespace std;


Barrel::Barrel(ofVec3f dimensions, ofVec3f position) {
    this -> dimensions = dimensions;
    this -> position = position;
    this -> on_ladder = false;
    this -> is_moving_left = true;
    this -> position_x_on_impact = 0;
    this -> speed = 0.5;
    this -> next_position_z = 0;
    this -> next_position_y = 0;
    this->moving_x = true;
    this->moving_y = false;
    this->moving_z = false;
    this->moving_down = false;
    this->currentState = MOVING_X;
}

void Barrel::draw(){
    glColor3f(0, 0, 1);
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(dimensions.x, dimensions.y, dimensions.z);
        sphere_unit(0.5, 32, 16);
        //cube_unit(0.5);
        //cube_unit_outline(0.5);
    glPopMatrix();
}

void Barrel::move_front(){
    if (position.x < global.right_limit + global.barrelDim.x) {
        //cout << "Moving front" << endl;
    is_moving_left = false;
    position.x += speed;
    }else{
        position.y -= speed;
    }
}
void Barrel::move_back(){
    if (position.x > global.left_limit - global.barrelDim.x) {
    //cout << "Moving back" << endl;
    is_moving_left = true;
    position.x -= speed;   
    }else{
        position.y -= speed;
    }   
}
void Barrel::move_down(){
        if(next_position_z == 0){
            next_position_z = position.z + global.platDim.z;
        }
        if(next_position_y == 0){
            next_position_y = position.y - global.ladDim.y + 1;
        }
        if (position_x_on_impact == 0){
            position_x_on_impact = position.x;
        }
        float target_x;
        if(is_moving_left){
            target_x= position_x_on_impact - (global.ladDim.x*0.5) - (global.barrelDim.x*0.5);
        }else{
            target_x = position_x_on_impact + (global.ladDim.x*0.5) + (global.barrelDim.x*0.5);
        }
        /*
        if (moving_x && !moving_y && !moving_z){
        if(is_moving_left){
            if(position.x > target_x){
                position.x -= speed;
            }
        }else{
            if(position.x < target_x){
                position.x += speed;
        }
        }
        moving_z = true;
        moving_x = false;
        }
        if (!moving_x && !moving_y && moving_z){
        if (position.z < next_position_z){
            position.z += speed;
            //position.z = next_position_z;
        }
        moving_z = false;
        moving_y = true;
        }
        if (!moving_x && moving_y && !moving_z){
        if (position.y > next_position_y){
            position.y -= speed;
            //position.y = next_position_y;
        }
        moving_x = true;
        moving_y = false;
        }
        */
         switch (currentState) {
        case MOVING_X: {
            // Move in X direction
            if (is_moving_left) {
                if (position.x > target_x) {
                    //position.x -= speed;
                    position.x = std::max(position.x - speed, target_x);
                } else {
                    currentState = MOVING_Z; // Transition to Z movement
                }
            } else {
                if (position.x < target_x) {
                    //position.x += speed;
                    position.x = std::min(position.x + speed, target_x);                   
                } else {
                    currentState = MOVING_Z; // Transition to Z movement
                }
            }
            break;
        }

        case MOVING_Z: {
            // Move in Z direction
            if (position.z < next_position_z) {
                //position.z += speed;
                position.z = std::min(position.z + speed, next_position_z);
            } else {
                currentState = MOVING_Y; // Transition to Y movement
            }
            break;
        }

        case MOVING_Y: {
            // Move in Y direction
            if (position.y > next_position_y) {
                //position.y -= speed;
                position.y = std::max(position.y - speed, next_position_y);
            }
        }
         }

        if ((position.x == target_x) && (position.y == next_position_y)){
            position.y -= 1;
            
            if (rand() % 100 < 75) {
                is_moving_left = !is_moving_left;

            }

            //cout << "Direction switched. Now moving " << (is_moving_left ? "left" : "right") << endl;


            // The barrel is no longer on the ladder
            leave_ladder = true;
            moving_x = true;
            moving_y = false;
            moving_z = false;
            currentState = MOVING_X;

            // Reset the impact position for the next ladder
            position_x_on_impact = 0;
            next_position_z = 0;
            next_position_y = 0;

            
        }
    }

