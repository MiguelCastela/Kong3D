#include "camera.h"
#include "cg_cam_extras.h"

Camera::Camera(GLfloat fov, GLfloat distance, ofVec3f position){
    camMode = 0;
    this -> fov = fov;
    this -> distance = distance;
    this -> position = position;
    alpha = 10;
    beta = 1000;

    distance = gw()*0.5*tan((fov*0.5)*(PI / 180));
}


void Camera::update(){}

void Camera::apply(ofVec3f marioPos, ofVec3f marioLookAt){
    switch(camMode){
        case(0) : applyp1(marioPos);
            break;
        case(1) : applyp2(marioPos);
            break;
        case(2) : applyp3(marioPos, marioLookAt);
            break;
    }
}

void Camera::applyp1(ofVec3f marioPos){
    perspective(fov, alpha, beta);
    lookat(
        0, marioPos.y + 50, marioPos.z + distance,
        0, marioPos.y, marioPos.z,
        0, 1, 0
    );
}

void Camera::applyp2(ofVec3f marioPos){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-gw()/8, gw()/8, -gh()/8, gh()/8, 10, 10000);
    lookat(
        0, marioPos.y, distance,
        0, marioPos.y, marioPos.z,
        0, 1, 0        
    );
}

void Camera::applyp3(ofVec3f marioPos, ofVec3f marioLookAt){
    perspective(fov, alpha*100, beta*100);
    lookat(
        marioPos.x, marioPos.y + 10, marioPos.z,
        marioLookAt.x, marioLookAt.y, marioLookAt.z,
        0, 1, 0
    );
}

