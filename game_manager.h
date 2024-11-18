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
class Barrel;
class Game{
    public:
        Game();
        void draw();
        void update();
        void draw_scene();
        void key_pressed(int key);
        void key_released(int key);
        void update_movement();
        void draw_barrels();
        bool check_collision(
            ofVec3f dim1, ofVec3f pos1,
            ofVec3f dim2, ofVec3f pos2        
        );

        // Player
        ofVec3f marioPos;
        ofVec3f marioDim;
        ofVec3f marioLookAt;        

        // Scene
        ofVec3f ladHitBoxDim;
        ofVec3f ladDim;
        ofVec3f platDim;
        ofVec3f barrelDim;
        GLint plat_ct;
        std::vector<Platform*> platVec;
        std::vector<Ladder*> ladVec;
        std::vector<Ladder*> ladHitBoxVec;


        Platform* lastPlat;
        ofVec3f lastPlatPos;

        ofVec3f barrelPos;
        bool keep_drawing = true;
        ofVec3f initBarrelPos;
        bool barrel_flag = false;
    private:
        Camera* cam;
        Mario* mario;
        Barrel *barrel;
};