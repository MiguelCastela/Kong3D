#pragma once

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"
#include "cg_cam_extras.h"
#include "camera.h"
#include "global.h"

#include <vector>   

class Camera;
class Mario;
class Platform;
class Ladder;
class Game{
    public:
        Game();
        void draw();
        void update();
        void draw_scene();
        void key_pressed(int key);
        void key_released(int key);
        void update_movement();
        bool check_collision(
            ofVec3f dim1, ofVec3f pos1,
            ofVec3f dim2, ofVec3f pos2        
        );

        // Player
        ofVec3f marioPos;
        ofVec3f marioDim;
        ofVec3f marioLookAt;        

        // Scene
        ofVec3f ladDim;
        ofVec3f platDim;
        GLint plat_ct;
        std::vector<Platform*> platVec;
        std::vector<Ladder*> ladVec;

    private:
        Camera* cam;
        Mario* mario;
};