#include <algorithm>
#include <cmath>
#include <vector>
#include "ofApp.h"
#include "mario.h"
#include "global.h"
#include "materials.h"

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
    this->times_dead = 0;

    this->going_up = false;
    this->target_y = 0;
    this->target_z = 0;

    this->dead = false;
    this->winState = false;

    this-> currentDirection = FRONT;
    this->marioLookAt = ofVec3f(global.right_limit*2, position.y, position.z);
}

void Mario::draw() {
    jump();
    glPushMatrix();  
    
        //global translation for Mario's position
        glTranslatef(position.x, position.y, position.z);  
        
        // local rotation for orientation
        if (currentDirection == RIGHT) {
            glRotatef(90, 0, 1, 0);  // Face left
        } else if (currentDirection == LEFT) {
            glRotatef(-90, 0, 1, 0);  // Face right
        }else if (currentDirection == UP) {
            glRotatef(180, 0, 1, 0);  // Face up
        }else if (currentDirection == DOWN) {
            glRotatef(0, 0, 1, 0);  // Face down
        }else if (currentDirection == BACK) {
            glRotatef(180, 0, 1, 0);  // Face back
        }
        // Return to origin after rotation
        glTranslatef(-position.x, -position.y, -position.z);  
        //body
        glPushMatrix();
            glTranslatef(position.x, position.y, position.z);
            glScalef(dimensions.x, dimensions.y, dimensions.z);
            loadMaterial(22);
            cube_unit(0.5);
            loadMaterial(24);
            cube_unit_outline(0.5);
        glPopMatrix();
        //draw left arm
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.5, position.y, position.z);  
            if (currentDirection == UP) {
                glRotatef(90, 1, 0, 0);  
            }
            glScalef(dimensions.x * 0.5, dimensions.y * 0.5, dimensions.z * 0.25); 
            loadMaterial(21);
            cube_unit(0.5); 
            loadMaterial(24);
            cube_unit_outline(0.5);  
        glPopMatrix();  
        //draw left hand
        glPushMatrix(); 
            glTranslatef(position.x - dimensions.x * 0.5, position.y, position.z); 
            if (currentDirection == UP) {
                glRotatef(-90, 1, 0, 0); 
            }
            glTranslatef(0, -dimensions.y * 0.30, 0);  

            glScalef(dimensions.x * 0.4, dimensions.y * 0.05, dimensions.z * 0.15); 
            loadMaterial(18);  
            cube_unit(0.5); 
            loadMaterial(24);
            cube_unit_outline(0.5); 
        glPopMatrix(); 
        //draw right arm
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.5, position.y, position.z); 
            if (currentDirection == UP) {
                glRotatef(90, 1, 0, 0); 
            }
            glScalef(dimensions.x * 0.5, dimensions.y * 0.5, dimensions.z * 0.25);  
            loadMaterial(21);
            cube_unit(0.5);  
            loadMaterial(24);
            cube_unit_outline(0.5);
        glPopMatrix();  
        //right hand
        glPushMatrix();   
            glTranslatef(position.x + dimensions.x * 0.5, position.y, position.z);  
            if (currentDirection == UP) {
                glRotatef(-90, 1, 0, 0);  
            }
            glTranslatef(0, -dimensions.y * 0.30, 0);  
            glScalef(dimensions.x * 0.4, dimensions.y * 0.05, dimensions.z * 0.15);  
            loadMaterial(18);  
            cube_unit(0.5);  
            loadMaterial(24);
            cube_unit_outline(0.5); 
        glPopMatrix();  
        // Draw the head
        glPushMatrix();
            glTranslatef(position.x, position.y + dimensions.y * 0.5, position.z); 
            if(currentDirection == UP){
                glRotatef(-45, 1, 0, 0);
            }else if (currentDirection == DOWN) {
                glRotatef(45, 1, 0, 0); 
            }
            glScalef(dimensions.x * 0.75, dimensions.y, dimensions.z * 0.75); 
            loadMaterial(18);  
            cube_unit(0.5);  
            loadMaterial(24);
            cube_unit_outline(0.5);
        glPopMatrix();  
        //draw hat
        glPushMatrix(); 
            glTranslatef(position.x, position.y + dimensions.y * 0.5, position.z); 
            if (currentDirection == UP) {
                glRotatef(-45, 1, 0, 0);
            }else if (currentDirection == DOWN) {
                glRotatef(45, 1, 0, 0);
            }
            glTranslatef(0, dimensions.y * 0.55, dimensions.z * 0.25); 

            glScalef(dimensions.x * 0.75, dimensions.y * 0.1, dimensions.z * 1.25);
            loadMaterial(22);
            cube_unit(0.5); 
            loadMaterial(24);
            cube_unit_outline(0.5); 
        glPopMatrix(); 
        //hat part 2
        glPushMatrix(); 
            glTranslatef(position.x, position.y + dimensions.y * 0.5, position.z); 
            if (currentDirection == UP) {
                glRotatef(-45, 1, 0, 0);
            }else if (currentDirection == DOWN) {
                glRotatef(45, 1, 0, 0); 
            }

            glTranslatef(0, dimensions.y * 0.7, 0); 

            glScalef(dimensions.x * 0.75, dimensions.y * 0.2, dimensions.z * 0.75);
            loadMaterial(22);
            cube_unit(0.5); 
            loadMaterial(24);
            cube_unit_outline(0.5); 
        glPopMatrix(); 
        // Draw left eye
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.4);  // Position the left eye
            if(currentDirection == UP){
                glRotatef(-45, 1, 0, 0);
            }else if (currentDirection == DOWN) {
                glRotatef(45, 1, 0, 0); 
            }

            glScalef(dimensions.x * 0.2, dimensions.y * 0.2, dimensions.z * 0.2);  
            loadMaterial(16);  
            cube_unit(0.5);  
        glPopMatrix(); 
        // Draw right eye
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.4);  // Position the right eye
            if(currentDirection == UP){
                glRotatef(-45, 1, 0, 0);
            }else if (currentDirection == DOWN) {
                glRotatef(45, 1, 0, 0);
            }
            glScalef(dimensions.x * 0.2, dimensions.y * 0.2, dimensions.z * 0.2);  
            loadMaterial(16);  
            cube_unit(0.5);  
        glPopMatrix(); 
        // Draw left pupil 
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.5);
            if(currentDirection == UP){
                glRotatef(-45, 1, 0, 0);
            }else if (currentDirection == DOWN) {
                glRotatef(45, 1, 0, 0);
            }
            glScalef(dimensions.x * 0.1, dimensions.y * 0.1, dimensions.z * 0.1);  
            loadMaterial(24);  
            cube_unit(0.5); 
        glPopMatrix();  
        // Draw right pupil
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.5);
            if(currentDirection == UP){
                glRotatef(-45, 1, 0, 0);
            }else if (currentDirection == DOWN) {
                glRotatef(45, 1, 0, 0);
            }
            glScalef(dimensions.x * 0.1, dimensions.y * 0.1, dimensions.z * 0.1);  
            loadMaterial(24); 
            cube_unit(0.5); 
        glPopMatrix();  
        //draw the moustache
        glPushMatrix();
            glTranslatef(position.x, position.y + dimensions.y * 0.60, position.z + dimensions.z * 0.4);
            if(currentDirection == UP){
                glRotatef(-45, 1, 0, 0);
            }else if (currentDirection == DOWN) {
                glRotatef(45, 1, 0, 0); 
            }
            glScalef(dimensions.x * 0.3, dimensions.y * 0.08, dimensions.z * 0.2);  
            loadMaterial(21);
            cube_unit(0.5);
        glPopMatrix();  // Reset transformations for the moustache
    glPopMatrix();  // Reset the global transformation state

}

void Mario::draw_pov(){
    jump();
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(dimensions.x, dimensions.y, dimensions.z);
    glPopMatrix();
}

void Mario::spawn_back() {
    float currentTime = ofGetElapsedTimef();

    if (!isRespawning) {
        respawnStartTime = currentTime;
        isRespawning = true;
        return;
    }
    if(dead){
        if (currentTime - respawnStartTime >= 1.0f && position != global.marioPos) {
            position = global.marioPos;
            is_climbing = false;
            on_ladder = false;
            isJumping = false;
            pre_jump_y = 0;
            base_position_y = 0;
            next_position_y = 0;

            respawnStartTime = currentTime;
            currentDirection = FRONT;
            marioLookAt = ofVec3f(position.x, position.y, position.z + 50);
            
        }
    }else{
        currentDirection = RIGHT;
        marioLookAt = ofVec3f(global.right_limit*2, position.y, position.z);
        if (currentTime - respawnStartTime >= 5.0f && position != global.marioPos) {
        position = global.marioPos;
        is_climbing = false;
        on_ladder = false;
        isJumping = false;
        pre_jump_y = 0;
        base_position_y = 0;
        next_position_y = 0;
        respawnStartTime = currentTime;
    }
    }

    if(dead){
        if (currentTime - respawnStartTime >= 0.1f && position == global.marioPos) {
            isRespawning = false;
            times_dead++;
            cout << "Mario has died " << times_dead << " times." << endl;
            currentDirection = FRONT;
            marioLookAt = ofVec3f(position.x, position.y, position.z + 50);
        }
    }else{
        if (currentTime - respawnStartTime >= 0.1f && position == global.marioPos) {
            isRespawning = false;

            cout << "Mario has died " << times_dead << " times." << endl;
            currentDirection = FRONT;
            marioLookAt = ofVec3f(position.x, position.y, position.z + 50);
        }
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
    currentDirection = LEFT;
}

void Mario::move_right(){
    marioLookAt = ofVec3f(global.right_limit*2, position.y, position.z);

    if (position.x < global.right_limit){
        position.x += speed;
    }else{
        position.x = global.right_limit;
    }
    currentDirection = RIGHT;
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
    currentDirection = UP;
}
void Mario::climb_down(){
    is_climbing = true;
    marioLookAt.y = position.y - 50;
    marioLookAt.x = position.x;
    marioLookAt.z = position.z + 20;
    
    position.y -= speed;

    if(position.y <= base_position_y){
        position.y = base_position_y;
        is_climbing = false;
    }
    currentDirection = DOWN;
}
    
    

void Mario::go_down(){
    cout << "Mario can't go down levels" << endl;
    marioLookAt = ofVec3f(position.x, position.y, position.z + 50);
    currentDirection = FRONT;

}

void Mario::jump_down() {
    cout << "Mario can't jump down levels" << endl;
    //currentDirection = FRONT;
}
void Mario::look_front(){
    marioLookAt = ofVec3f(position.x, position.y, position.z - 50);
    currentDirection = BACK;
}
