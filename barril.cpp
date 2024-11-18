#include <bits/stdc++.h>
#include "ofApp.h"
#include "barril.h"
#include "global.h"

using namespace std;


Barrel::Barrel(ofVec3f dimensions, ofVec3f position) {
    this -> dimensions = dimensions;
    this -> position = position;
    this -> on_ladder = false;
    this -> is_moving_left = false;
    this -> position_x_on_impact = 0;
    this -> speed = 0.005;
    this -> next_position_z = position.z + global.platDim.z;
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
    if(!on_ladder){
    is_moving_left = false;
    position.x += speed;
}
}

void Barrel::move_back(){
    if(!on_ladder){
    is_moving_left = true;
    position.x -= speed;
    }
}

void Barrel::move_down(){
    if (on_ladder){
        if (position_x_on_impact == 0){
            position_x_on_impact = position.x;
        }
        float target_x;
        if(is_moving_left){
            target_x= position_x_on_impact - (global.ladDim.x*0.5) - (global.barrelDim.x*0.5);
        }else{
            target_x = position_x_on_impact + (global.ladDim.x*0.5) + (global.barrelDim.x*0.5);
        }
    
        cout << "Position x on impact: " << position_x_on_impact << endl;
        cout << "Target x: " << target_x << endl;
        cout << "Current x: " << position.x << endl;
        if(is_moving_left){
            if(position.x > target_x){
                position.x -= speed;
            }else{
            position.x = target_x;
            }
        }else{
            if(position.x < target_x){
                position.x += speed;
            }else{
            position.x = target_x;
            }
        }
        if (position.z < next_position_z){
            position.z += speed;
        }
        }
    }