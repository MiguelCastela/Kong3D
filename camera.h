#pragma once

#include "ofMain.h"
#include "cg_extras.h"


class Camera{
    public:
        Camera(GLfloat fov = 60, GLfloat distance = 100, ofVec3f position = ofVec3f(0, 0, 0));
        void update();
        void apply(ofVec3f marioPos, ofVec3f marioLookAt);
        void applyp1(ofVec3f marioPos);
        void applyp2(ofVec3f marioPos);
        void applyp3(ofVec3f marioPos, ofVec3f marioLookAt);
        void miniMap(ofVec3f marioPos);
        GLint camMode;
        bool camFlag;
        GLint num_lives =0;
        GLint high_score = INT_MAX;
        bool isFirstPlaythrough = true;
        GLint meters = 0;
        GLint num_platforms = 0;
    private:

        GLfloat fov;
        GLfloat distance;
        ofVec3f position;
        GLint alpha;
        GLint beta;

};

