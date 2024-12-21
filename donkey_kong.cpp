#include "donkey_kong.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include "global.h"
#include "ofApp.h"
#include "materials.h"

using namespace std;

Kong::Kong(ofVec3f dimensions, ofVec3f position) {
    this->dimensions = dimensions;
    this->position = position;
}

void Kong::draw() {
    //rotate kong
    glPushMatrix();  
        glTranslatef(position.x, position.y, position.z);  
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); 
        glTranslatef(-position.x, -position.y, -position.z); 
        // Draw body
        glPushMatrix();
            loadMaterial(19);
            glTranslatef(position.x, position.y, position.z);  
            glScalef(dimensions.x, dimensions.y, dimensions.z);  
            cube_unit(0.5); 
            loadMaterial(2);
            cube_unit_outline(0.5);
        glPopMatrix();  
        //draw left arm
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.5, position.y , position.z + dimensions.z *0.5);  
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glScalef(dimensions.x * 0.5, dimensions.y , dimensions.z * 0.25); 
            loadMaterial(19); 
            cube_unit(0.5);  
            loadMaterial(2);
            cube_unit_outline(0.5);  
            //left hand
            glPushMatrix();
                glTranslatef(0.0f, 0.05f, 0.0f); 
                glScalef(0.7f, 1.05f, 0.7f);  
                loadMaterial(20); 
                cube_unit(0.5);  
                loadMaterial(2);  
                cube_unit_outline(0.5);  
            glPopMatrix();
        glPopMatrix(); 
        //draw right arm
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.5, position.y  , position.z + dimensions.z*0.5);  
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glScalef(dimensions.x * 0.5, dimensions.y, dimensions.z * 0.25); 
            loadMaterial(19); 
            cube_unit(0.5);  
            loadMaterial(2);
            cube_unit_outline(0.5); 
            //right hand 
            glPushMatrix();
                glTranslatef(0.0f, 0.05f, 0.0f);  
                glScalef(0.7f, 1.05f, 0.7f);  
                loadMaterial(20);  
                cube_unit(0.5);  
                loadMaterial(2);  
                cube_unit_outline(0.5);  
            glPopMatrix();
        glPopMatrix();  
        // Draw head
        glPushMatrix();
            glTranslatef(position.x, position.y + dimensions.y * 0.5, position.z);  
            glScalef(dimensions.x * 0.75, dimensions.y, dimensions.z * 0.75);  
            loadMaterial(19); 
            cube_unit(0.5);  
            loadMaterial(2);
            cube_unit_outline(0.5);  
        glPopMatrix(); 
        // Draw left eye
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.4);  
            glScalef(dimensions.x * 0.2, dimensions.y * 0.2, dimensions.z * 0.2);  
            loadMaterial(16); 
            cube_unit(0.5);  
        glPopMatrix(); 

        // Draw right eye
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.4);  
            glScalef(dimensions.x * 0.2, dimensions.y * 0.2, dimensions.z * 0.2);  
            loadMaterial(16); 
            cube_unit(0.5); 
        glPopMatrix();  
        // Draw left pupil
        glPushMatrix();
            glTranslatef(position.x - dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.5);
            glScalef(dimensions.x * 0.1, dimensions.y * 0.1, dimensions.z * 0.1); 
            loadMaterial(2);  
            cube_unit(0.5);  
        glPopMatrix();  
        // Draw right pupil
        glPushMatrix();
            glTranslatef(position.x + dimensions.x * 0.2, position.y + dimensions.y * 0.75, position.z + dimensions.z * 0.5);
            glScalef(dimensions.x * 0.1, dimensions.y * 0.1, dimensions.z * 0.1);  
            loadMaterial(2);  
            cube_unit(0.5);  
        glPopMatrix();  

        //draw belly
        glPushMatrix();
            glTranslatef(position.x, position.y, position.z + dimensions.z*0.05);  
            glScalef(dimensions.x*0.6 , dimensions.y*0.6 , dimensions.z);  
            loadMaterial(20);  
            cube_unit(0.5); 
        glPopMatrix();  
    glPopMatrix();//global pop
}
