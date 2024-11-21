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
class Particle;
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
        ofVec3f ladHitBoxDim;
        ofVec3f ladDim;
        ofVec3f platDim;
        ofVec3f barrelDim;
        ofVec3f fakeLadDim;
        GLint plat_ct;
        Platform* lastPlat;
        ofVec3f lastPlatPos;

        std::vector<Platform*> platVec;
        std::vector<Ladder*> ladVec;
        std::vector<Ladder*> ladHitBoxVec;
        std::vector<Ladder*> fakeLadVec;



        //barrel
        std::vector<Barrel*> barrelVec;
        ofVec3f barrelPos;
        ofVec3f initBarrelPos;
        bool barrel_flag = false;
        float lastBarrelSpawnTime; 
        int barrelsSpawned;       
        float barrelSpawnDelay;


        //particles 
        vector<Particle*> explosion;


        //state
        bool mario_dead = false;
 
    private:
        Camera* cam;
        Mario* mario;
        Barrel *barrel;
        Particle *marioParticle;
};