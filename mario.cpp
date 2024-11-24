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

    this->going_up = false;

    this->times_dead = 0;

    this->target_y = 0;
    this->target_z = 0;

    this->dead = false;

    this-> currentDirection = FRONT;

    this->winState = false;

    

    

    this->marioLookAt = ofVec3f(global.right_limit*2, position.y, position.z);
}

void Mario::draw() {
    jump();
    glPushMatrix();  // Save the global transformation state
    
    // Apply global translation for Mario's position
    glTranslatef(position.x, position.y, position.z);  
    
    // Apply local rotation for orientation
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
    glTranslatef(-position.x, -position.y, -position.z);  // Return to origin after rotation
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(dimensions.x, dimensions.y, dimensions.z);
        //if(camera.camFlag = true){
        glColor3f(1, 0, 0);
            cube_unit(0.5);
        //}
        cube_unit_outline(0.5);
    glPopMatrix();
     //draw arms
    glPushMatrix();
        glTranslatef(position.x - dimensions.x * 0.5, position.y, position.z);  // Position the left arm
            if (currentDirection == UP) {
        glRotatef(90, 1, 0, 0);  // Rotate arm 90 degrees along the X-axis to make it reach out
    }
        glScalef(dimensions.x * 0.5, dimensions.y * 0.5, dimensions.z * 0.25);  // Scale the left arm
    glColor3f(0, 0, 1);
        cube_unit(0.5);  // Draw the left arm
        //black outline
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);  // Outline the left arm
    glPopMatrix();  // Reset transformations for the left arm
    //draw left hand
    glPushMatrix(); 
    // Position the arm first
    glTranslatef(position.x - dimensions.x * 0.5, position.y, position.z);  // Position the left arm

    // Apply rotation only after positioning the arm
    if (currentDirection == UP) {
        glRotatef(-90, 1, 0, 0);  // Rotate arm 90 degrees along the X-axis to make it reach out
    }

    // Now apply the second translation to position the arm's hand part
    glTranslatef(0, -dimensions.y * 0.30, 0);  // Offset for hand position (relative to arm)

    // Scale the arm after the rotation and second translation
    glScalef(dimensions.x * 0.4, dimensions.y * 0.05, dimensions.z * 0.15);  // Scale the left arm

    // Draw the left arm
    glColor3f(1.0, 0.8, 0.6);  
    cube_unit(0.5);  // Draw the left arm

    // Black outline for the left arm
    glColor3f(0.0, 0.0, 0.0);
    cube_unit_outline(0.5);  // Outline the left arm
glPopMatrix();  // Reset transformations for the left arm
        glPushMatrix();
        glTranslatef(position.x + dimensions.x * 0.5, position.y, position.z);  // Position the right arm
            if (currentDirection == UP) {
        glRotatef(90, 1, 0, 0);  // Rotate arm 90 degrees along the X-axis to make it reach out
    }
        glScalef(dimensions.x * 0.5, dimensions.y * 0.5, dimensions.z * 0.25);  // Scale the right arm
    glColor3f(0,0,1);
        cube_unit(0.5);  // Draw the right arm
        //black outline
        cube_unit_outline(0.5);  // Outline the right arm
    glPopMatrix();  // Reset transformations for the right arm
    //draw left hand
    glPushMatrix(); 
    // Position the arm first
    glTranslatef(position.x + dimensions.x * 0.5, position.y, position.z);  // Position the left arm

    // Apply rotation only after positioning the arm
    if (currentDirection == UP) {
        glRotatef(-90, 1, 0, 0);  // Rotate arm 90 degrees along the X-axis to make it reach out
    }

    // Now apply the second translation to position the arm's hand part
    glTranslatef(0, -dimensions.y * 0.30, 0);  // Offset for hand position (relative to arm)

    // Scale the arm after the rotation and second translation
    glScalef(dimensions.x * 0.4, dimensions.y * 0.05, dimensions.z * 0.15);  // Scale the left arm

    // Draw the left arm
    glColor3f(1.0, 0.8, 0.6);  
    cube_unit(0.5);  // Draw the left arm

    // Black outline for the left arm
    glColor3f(0.0, 0.0, 0.0);
    cube_unit_outline(0.5);  // Outline the left arm
    glPopMatrix();  // Reset transformations for the left arm

    // Draw the head
   glPushMatrix();
        glTranslatef(position.x, position.y + dimensions.y * 0.5, position.z);  // Position the head above the body
        if(currentDirection == UP){
           glRotatef(-45, 1, 0, 0);
        }else if (currentDirection == DOWN) {
        glRotatef(45, 1, 0, 0); // Rotate Mario's head to look down
    }
        glScalef(dimensions.x * 0.75, dimensions.y, dimensions.z * 0.75);  // Scale the head
        //beije skin color
        glColor3f(1.0, 0.8, 0.6);  
        cube_unit(0.5);  // Draw the head
        cube_unit_outline(0.5);  // Outline the head
    glPopMatrix();  // Reset transformations for the head
    glPushMatrix(); // Start a new matrix stack for the hat
    // Apply global transformations for Mario
    glTranslatef(position.x, position.y + dimensions.y * 0.5, position.z); // Position the head

    // Apply head rotation (UP direction)
    if (currentDirection == UP) {
        glRotatef(-45, 1, 0, 0); // Rotate Mario's head to look up
    }else if (currentDirection == DOWN) {
        glRotatef(45, 1, 0, 0); // Rotate Mario's head to look down
    }

    // Position the hat relative to the rotated head
    glTranslatef(0, dimensions.y * 0.55, dimensions.z * 0.25); // Offset for the hat on top of the head

    // Scale and draw the hat
    glScalef(dimensions.x * 0.75, dimensions.y * 0.1, dimensions.z * 1.25);
    glColor3f(0, 0, 1); // Blue hat color
    cube_unit(0.5); // Draw the hat
    // Draw black outline for the hat
    glColor3f(0, 0, 0);
    cube_unit_outline(0.5); // Hat outline
glPopMatrix(); // Reset transformations after drawing the hat
glPushMatrix(); // Start a new matrix stack for the second part of the hat
    // Apply global transformations for Mario
    glTranslatef(position.x, position.y + dimensions.y * 0.5, position.z); // Position the head

    // Apply head rotation (UP direction)
    if (currentDirection == UP) {
        glRotatef(-45, 1, 0, 0); // Rotate Mario's head to look up
    }else if (currentDirection == DOWN) {
        glRotatef(45, 1, 0, 0); // Rotate Mario's head to look down
    }

    // Position the second part of the hat relative to the rotated head
    glTranslatef(0, dimensions.y * 0.7, 0); // Offset to position the second hat part on top of the first one

    // Scale and draw the second part of the hat
    glScalef(dimensions.x * 0.75, dimensions.y * 0.2, dimensions.z * 0.75);
    glColor3f(0, 0, 1); // Blue color for the second part of the hat
    cube_unit(0.5); // Draw the second part of the hat
    // Draw black outline for the second part
    glColor3f(0.0, 0.0, 0.0);
    cube_unit_outline(0.5); // Outline
glPopMatrix(); // Reset transformations after drawing the second part of the hat
            // Draw left eye
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.4);  // Position the left eye
                    if(currentDirection == UP){
           glRotatef(-45, 1, 0, 0);
        }else if (currentDirection == DOWN) {
        glRotatef(45, 1, 0, 0); // Rotate Mario's head to look down
    }

            glScalef(dimensions.x * 0.2, dimensions.y * 0.2, dimensions.z * 0.2);  // Scale the left eye
            glColor3f(1.0, 1.0, 1.0);  // White color for the eye
            cube_unit(0.5);  // Draw the left eye
        glPopMatrix();  // Reset transformations for the left eye

        // Draw right eye
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.4);  // Position the right eye
                    if(currentDirection == UP){
           glRotatef(-45, 1, 0, 0);
        }else if (currentDirection == DOWN) {
        glRotatef(45, 1, 0, 0); // Rotate Mario's head to look down
    }
            glScalef(dimensions.x * 0.2, dimensions.y * 0.2, dimensions.z * 0.2);  // Scale the right eye
            glColor3f(1.0, 1.0, 1.0);  // White color for the eye
            cube_unit(0.5);  // Draw the right eye
        glPopMatrix();  // Reset transformations for the right eye
        // Draw left pupil
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.5);
                    if(currentDirection == UP){
           glRotatef(-45, 1, 0, 0);
        }else if (currentDirection == DOWN) {
        glRotatef(45, 1, 0, 0); // Rotate Mario's head to look down
    }
            glScalef(dimensions.x * 0.1, dimensions.y * 0.1, dimensions.z * 0.1);  // Scale the left pupil
            glColor3f(0.0, 0.0, 0.0);  // Black color for the pupil
            cube_unit(0.5);  // Draw the left pupil
        glPopMatrix();  // Reset transformations for the left pupil

        // Draw right pupil
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.5);
                    if(currentDirection == UP){
           glRotatef(-45, 1, 0, 0);
        }else if (currentDirection == DOWN) {
        glRotatef(45, 1, 0, 0); // Rotate Mario's head to look down
    }
            glScalef(dimensions.x * 0.1, dimensions.y * 0.1, dimensions.z * 0.1);  // Scale the right pupil
            glColor3f(0.0, 0.0, 0.0);  // Black color for the pupil
            cube_unit(0.5);  // Draw the right pupil
        glPopMatrix();  // Reset transformations for the right pupil
        //draw the moustache
        glPushMatrix();
            glTranslatef(position.x, position.y + dimensions.y * 0.60, position.z + dimensions.z * 0.4);
                    if(currentDirection == UP){
           glRotatef(-45, 1, 0, 0);
        }else if (currentDirection == DOWN) {
        glRotatef(45, 1, 0, 0); // Rotate Mario's head to look down
    }
            glScalef(dimensions.x * 0.3, dimensions.y * 0.05, dimensions.z * 0.1);  // Scale the moustache
            //dark brown color
            glColor3f(0.5, 0.35, 0.05);
            cube_unit(0.5);  // Draw the moustache
        glPopMatrix();  // Reset transformations for the moustache
    glPopMatrix();  // Reset the global transformation state

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
    if(dead){
    if (currentTime - respawnStartTime >= 1.0f && position != global.marioPos) {
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
        currentDirection = FRONT;
    }
    }else{
        currentDirection = RIGHT;
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
    }


    if(dead){
    if (currentTime - respawnStartTime >= 0.1f && position == global.marioPos) {
        // Exit the respawning state after 1 second at the respawn position
        isRespawning = false;
        times_dead++;
        cout << "Mario has died " << times_dead << " times." << endl;
    }
    }else{
        if (currentTime - respawnStartTime >= 0.1f && position == global.marioPos) {
        // Exit the respawning state after 1 second at the respawn position
        isRespawning = false;
        cout << "Mario has died " << times_dead << " times." << endl;
        currentDirection = FRONT;
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
