
#include <bits/stdc++.h>
#include "ofApp.h"
#include "plataforma.h"
using namespace std;

Platform::Platform(GLfloat levelWidth, GLfloat levelHeight, GLfloat levelDepth, GLfloat height, GLint resY) {
    this->levelWidth = levelWidth;
    this->levelHeight = levelHeight;
    this->levelDepth = levelDepth;
    if(height != 0){
        this->height = height;
    }else{
        this->height = 0;
    }

    

}

void Platform::draw() {
    glColor3f(0.0f, 0.0f, 0.4f); // Set color to yellow for regular platforms


	glPushMatrix();//base push
    glTranslatef(gw() * 0.5, (gh() * 0.5) + (height * levelHeight) , 0);
	glScalef(levelWidth, levelHeight, levelDepth);
	cube_unit(0.5);
	glPopMatrix();//level pop
    
    
    glColor3f(0, 0, 0);  // Black for the edges
    glPushMatrix();
    glTranslatef(gw() * 0.5, (gh() * 0.5) + (height * levelHeight), 0);
    
    GLfloat x1 = -levelWidth * 0.5;
    GLfloat x2 = levelWidth * 0.5;
    GLfloat y1 = -levelHeight * 0.5;
    GLfloat y2 = levelHeight * 0.5;
    GLfloat z1 = -levelDepth * 0.5;
    GLfloat z2 = levelDepth * 0.5;

    glBegin(GL_LINES);

    // Front rectangle edges (4 edges)
    glVertex3f(x1, y1, z1); glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z1); glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z1); glVertex3f(x1, y2, z1);
    glVertex3f(x1, y2, z1); glVertex3f(x1, y1, z1);

    // Back rectangle edges (4 edges)
    glVertex3f(x1, y1, z2); glVertex3f(x2, y1, z2);
    glVertex3f(x2, y1, z2); glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z2); glVertex3f(x1, y2, z2);
    glVertex3f(x1, y2, z2); glVertex3f(x1, y1, z2);

    // Vertical edges (4 edges)
    glVertex3f(x1, y1, z1); glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z1); glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z1); glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z1); glVertex3f(x1, y2, z2);

    glEnd();  

    glPopMatrix();
}

