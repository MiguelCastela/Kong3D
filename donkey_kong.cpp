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
    glColor3f(0.5, 0.35, 0.05);
    // Draw body
    glPushMatrix();
        glTranslatef(position.x, position.y, position.z);  // Position the body
        glScalef(dimensions.x, dimensions.y, dimensions.z);  // Scale the body
        cube_unit(0.5);  // Draw the body
        cube_unit_outline(0.5);  // Outline the body
    glPopMatrix();  // Reset transformations for the body

    // Draw head
    glPushMatrix();
        glTranslatef(position.x, position.y + dimensions.y * 0.5, position.z);  // Position the head above the body
        glScalef(dimensions.x * 0.75, dimensions.y, dimensions.z * 0.75);  // Scale the head
        glColor3f(0.5, 0.35, 0.05); 
        cube_unit(0.5);  // Draw the head
        cube_unit_outline(0.5);  // Outline the head
    glPopMatrix();  // Reset transformations for the head
        // Draw left eye
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.4);  // Position the left eye
            glScalef(dimensions.x * 0.1, dimensions.y * 0.1, dimensions.z * 0.1);  // Scale the left eye
            glColor3f(1.0, 1.0, 1.0);  // White color for the eye
            cube_unit(0.5);  // Draw the left eye
            glColor3f(0.0, 0.0, 0.0);  // Black color for the outline
            cube_unit_outline(0.5);  // Outline the left eye
        glPopMatrix();  // Reset transformations for the left eye

        // Draw right eye
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.4);  // Position the right eye
            glScalef(dimensions.x * 0.1, dimensions.y * 0.1, dimensions.z * 0.1);  // Scale the right eye
            glColor3f(1.0, 1.0, 1.0);  // White color for the eye
            cube_unit(0.5);  // Draw the right eye
            glColor3f(0.0, 0.0, 0.0);  // Black color for the outline
            cube_unit_outline(0.5);  // Outline the right eye
        glPopMatrix();  // Reset transformations for the right eye
        
    glPopMatrix();

}
