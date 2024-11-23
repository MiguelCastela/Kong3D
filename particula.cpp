#include "particula.h"
#include <bits/stdc++.h>
#include "global.h"
#include "ofApp.h"


using namespace std;

Particle::Particle(ofVec3f position, ofVec3f dimensions, ofVec3f color) {
    this->position = position;
    this->dimensions = dimensions;
    this->color = color;

    this->velocity = ofVec3f(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0));
}

void Particle::update() {
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