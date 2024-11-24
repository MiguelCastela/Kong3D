#include "donkey_kong.h"
#include <bits/stdc++.h>
#include "global.h"
#include "ofApp.h"

using namespace std;

Kong::Kong(ofVec3f dimensions, ofVec3f position) {
    this->dimensions = dimensions;
    this->position = position;
}

void Kong::draw() {
    glPushMatrix();  // Save the global transformation state

    // Rotate Donkey Kong 90 degrees to the left
    glTranslatef(position.x, position.y, position.z);  // Move to Kong's position
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);  // Rotate 90 degrees around the y-axis

    glTranslatef(-position.x, -position.y, -position.z);  // Return to origin after rotation
    
    // Draw body
    glPushMatrix();
        glColor3f(0.5, 0.35, 0.05);
        glTranslatef(position.x, position.y, position.z);  // Position the body
        glScalef(dimensions.x, dimensions.y, dimensions.z);  // Scale the body
        cube_unit(0.5);  // Draw the body
        //black outline
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);  // Outline the body
    glPopMatrix();  // Reset transformations for the body

    //draw arms
    glPushMatrix();
        glTranslatef(position.x - dimensions.x * 0.5, position.y , position.z + dimensions.z *0.5);  // Position the left arm
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(dimensions.x * 0.5, dimensions.y , dimensions.z * 0.25);  // Scale the left arm

        glColor3f(0.5, 0.35, 0.05); 
        cube_unit(0.5);  // Draw the left arm
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);  // Outline the left arm
                glPushMatrix();
            glTranslatef(0.0f, 0.05f, 0.0f);  // Move to the end of the arm
            glScalef(0.7f, 1.05f, 0.7f);  // Scale to make it smaller
            glColor3f(0.55, 0.35, 0.05);  // Bright color for the end cap
            cube_unit(0.5);  // Draw the cap
            glColor3f(0.0, 0.0, 0.0);  // Black color for the cap
            cube_unit_outline(0.5);  // Outline the cap
    glPopMatrix();
    glPopMatrix();  // Reset transformations for the left arm


    glPushMatrix();
        glTranslatef(position.x + dimensions.x * 0.5, position.y  , position.z + dimensions.z*0.5);  // Position the right arm
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(dimensions.x * 0.5, dimensions.y, dimensions.z * 0.25);  // Scale the right arm
        glColor3f(0.5, 0.35, 0.05); 
        cube_unit(0.5);  // Draw the right arm
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);  // Outline the right arm
        glPushMatrix();
            glTranslatef(0.0f, 0.05f, 0.0f);  // Move to the end of the arm
            glScalef(0.7f, 1.05f, 0.7f);  // Scale to make it smaller
            glColor3f(0.55, 0.35, 0.05);  // Bright color for the end cap
            cube_unit(0.5);  // Draw the cap
            glColor3f(0.0, 0.0, 0.0);  // Black color for the cap
            cube_unit_outline(0.5);  // Outline the cap
    glPopMatrix();
    glPopMatrix();  // Reset transformations for the right arm




    // Draw head
    glPushMatrix();
        glTranslatef(position.x, position.y + dimensions.y * 0.5, position.z);  // Position the head above the body
        glScalef(dimensions.x * 0.75, dimensions.y, dimensions.z * 0.75);  // Scale the head
        glColor3f(0.5, 0.35, 0.05); 
        cube_unit(0.5);  // Draw the head
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);  // Outline the head
    glPopMatrix();  // Reset transformations for the head
        // Draw left eye
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.4);  // Position the left eye
            glScalef(dimensions.x * 0.2, dimensions.y * 0.2, dimensions.z * 0.2);  // Scale the left eye
            glColor3f(1.0, 1.0, 1.0);  // White color for the eye
            cube_unit(0.5);  // Draw the left eye
        glPopMatrix();  // Reset transformations for the left eye

        // Draw right eye
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.4);  // Position the right eye
            glScalef(dimensions.x * 0.2, dimensions.y * 0.2, dimensions.z * 0.2);  // Scale the right eye
            glColor3f(1.0, 1.0, 1.0);  // White color for the eye
            cube_unit(0.5);  // Draw the right eye
        glPopMatrix();  // Reset transformations for the right eye
        // Draw left pupil
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.5);
            glScalef(dimensions.x * 0.1, dimensions.y * 0.1, dimensions.z * 0.1);  // Scale the left pupil
            glColor3f(0.0, 0.0, 0.0);  // Black color for the pupil
            cube_unit(0.5);  // Draw the left pupil
        glPopMatrix();  // Reset transformations for the left pupil

        // Draw right pupil
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.5);
            glScalef(dimensions.x * 0.1, dimensions.y * 0.1, dimensions.z * 0.1);  // Scale the right pupil
            glColor3f(0.0, 0.0, 0.0);  // Black color for the pupil
            cube_unit(0.5);  // Draw the right pupil
        glPopMatrix();  // Reset transformations for the right pupil


        //draw belly
        glPushMatrix();
            glTranslatef(position.x, position.y, position.z + dimensions.z*0.05);  // Position the belly
            glScalef(dimensions.x*0.6 , dimensions.y*0.6 , dimensions.z);  // Scale the belly
            glColor3f(0.75, 0.5, 0.1);  // Brown color for the belly
            cube_unit(0.5);  // Draw the belly
        glPopMatrix();  // Reset transformations for the belly
        glPopMatrix();  // Reset transformations for Donkey Kong
}
