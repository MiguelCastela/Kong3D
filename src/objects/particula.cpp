#include "particula.h"
#include <bits/stdc++.h>
#include "global.h"
#include "ofApp.h"
#include "materials.h"


using namespace std;

Particle::Particle(ofVec3f position, ofVec3f dimensions, int materialIndex){
    this->position = position;
    this->dimensions = dimensions;

    this->velocity = ofVec3f(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0));

    this->lifetime = 0.0f;  
    this->isAlive = true;    
    this->materialIndex = materialIndex;
}

void Particle::update() {
    this->position += this->velocity;

    this->lifetime += ofGetLastFrameTime(); 

    if (this->lifetime > 4.5f) {
        this->isAlive = false;
    }
}

void Particle::draw() {
    if (!isAlive) return;  
    ofPushMatrix();
        ofTranslate(position.x, position.y, position.z);
        ofScale(dimensions.x, dimensions.y, dimensions.z);

        loadMaterial(materialIndex);
        cube_unit(0.5);
        
    ofPopMatrix();
}

Particle::~Particle() {
    //std::cout << "Particle at position (" << position.x << ", " << position.y << ", " << position.z << ") destroyed." << std::endl;
}