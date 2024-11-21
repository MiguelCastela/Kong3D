#include "particula.h"
#include <bits/stdc++.h>
#include "ofApp.h"


using namespace std;

Particle::Particle(ofVec3f position, ofVec3f dimensions, ofVec3f color) {
    this->position = position;
    this->dimensions = dimensions;
    this->color = color;
}
void Particle::shoot(float speed) {
    // Generate a random direction for the particle
    float randomX = ofRandom(-1.0, 1.0); // Random value for the x direction
    float randomY = ofRandom(-1.0, 1.0); // Random value for the y direction
    float randomZ = ofRandom(-1.0, 1.0); // Random value for the z direction
    
    // Create a random direction vector using these values
    ofVec3f direction(randomX, randomY, randomZ);
    
    // Normalize the direction vector and multiply by speed to get the final velocity
    this->velocity = direction.getNormalized() * speed;
}

void Particle::update() {
    // Update the position of the particle based on its velocity
    this->position += this->velocity;
}

void Particle::draw() {
    // Set the color of the particle
    glColor3f(this->color.x, this->color.y, this->color.z);
    // Draw a unit cube at the particle's position
    ofPushMatrix();
        ofTranslate(position.x, position.y, position.z);
        ofScale(dimensions.x, dimensions.y, dimensions.z);
        cube_unit(0.5);
        cube_unit_outline(0.5);
    ofPopMatrix();
}
