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

    this->lifetime = 0.0f;  
    this->isAlive = true;    
}

void Particle::update() {
    this->position += this->velocity;

    this->lifetime += ofGetLastFrameTime(); 

    if (this->lifetime > 6.0f) {
        this->isAlive = false;
    }
}

void Particle::draw() {
    if (!isAlive) return;  
    glColor3f(this->color.x, this->color.y, this->color.z);
    ofPushMatrix();
        ofTranslate(position.x, position.y, position.z);
        ofScale(dimensions.x, dimensions.y, dimensions.z);
        cube_unit(0.5);
        cube_unit_outline(0.5);
    ofPopMatrix();
}