#include "pauline.h"
#include <bits/stdc++.h>
#include "global.h"
#include "ofApp.h"

using namespace std;

Pauline::Pauline(ofVec3f dimensions, ofVec3f position) {
    this->dimensions = dimensions;
    this->position = position;
}

void Pauline::draw() {
 // Set color to lighter pink
    glColor3f(1.0, 0.6, 0.8);
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glScalef(dimensions.x, dimensions.y, dimensions.z);
        cube_unit(0.5);
        cube_unit_outline(0.5);
    glPopMatrix();

    //draw arms
    glPushMatrix();
        glTranslatef(position.x - dimensions.x * 0.5, position.y, position.z);  // Position the left arm
        glScalef(dimensions.x * 0.5, dimensions.y * 0.5, dimensions.z * 0.25);  // Scale the left arm
    glColor3f(1.0, 0.6, 0.8);
        cube_unit(0.5);  // Draw the left arm
        //black outline
        glColor3f(0.0, 0.0, 0.0);
        cube_unit_outline(0.5);  // Outline the left arm
    glPopMatrix();  // Reset transformations for the left arm

        glPushMatrix();
        glTranslatef(position.x + dimensions.x * 0.5, position.y, position.z);  // Position the right arm
        glScalef(dimensions.x * 0.5, dimensions.y * 0.5, dimensions.z * 0.25);  // Scale the right arm
    glColor3f(1.0, 0.6, 0.8);
            glColor3f(0.0, 0.0, 0.0);
        cube_unit(0.5);  // Draw the right arm

        cube_unit_outline(0.5);  // Outline the right arm
    glPopMatrix();  // Reset transformations for the right arm
    // Draw the head
   glPushMatrix();
        glTranslatef(position.x, position.y + dimensions.y * 0.5, position.z);  // Position the head above the body
        glScalef(dimensions.x * 0.75, dimensions.y, dimensions.z * 0.75);  // Scale the head
        //beije skin color
        glColor3f(1.0, 0.8, 0.6);  
        cube_unit(0.5);  // Draw the head
        cube_unit_outline(0.5);  // Outline the head
    glPopMatrix();  // Reset transformations for the head
    //draw blonde hair 
    glPushMatrix();
        glTranslatef(position.x , position.y + 0.2 + dimensions.y * 0.5, position.z);  // Position the head above the body
        glScalef(dimensions.x *0.95 , dimensions.y * 1.2, dimensions.z *0.74);  // Scale the head
        glColor3f(1.0, 1.0, 0.0);
        cube_unit(0.5);  // Draw the head
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







}