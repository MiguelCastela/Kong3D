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
class Kong;
class Pauline;
class Game{
    public:
        Game();
        void draw();
        void update();
        void draw_scene(bool pov);
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
        ofVec3f ladHitBoxDim_mario;
        GLint plat_ct;


        ofVec3f lastPlatPos;
        ofVec3f paulinePlatPos;
        ofVec3f lastLadderPos;



        std::vector<Platform*> platVec;
        std::vector<Ladder*> ladVec;
        std::vector<Ladder*> ladHitBoxVec;
        std::vector<Ladder*> fakeLadVec;
        std::vector<Ladder*> ladHitBoxVec_mario;
        std::vector<Barrel*> barrelVec;



        //barrel
 
        ofVec3f barrelPos;
        ofVec3f initBarrelPos;
        bool barrel_flag = false;
        float lastBarrelSpawnTime; 
        int barrelsSpawned;       
        float barrelSpawnDelay;

        //kong
        ofVec3f kongPos;
        ofVec3f kongDim;

        //pauline
        ofVec3f paulinePos;
        ofVec3f paulineDim;

        //particles 
        vector<Particle*> explosion;


        //state
        bool flag_down = false;
        bool mario_dead = false;
        bool mario_wins = false;
        bool barrels_reset = false;
        bool  explosion_created = false; 
        bool explosion_kong = false;
        bool explosion_barrel = false;
        int remainingParticles;  // Total particles left to release
        float lastParticleBurstTime; // Last time a burst was released
        const int particlesPerBurst = 10;  // Number of particles to release per burst


        int times_dead = 0; 
    private:
        Camera* cam;
        Mario* mario;
        Barrel *barrel;
        Particle *marioParticle;
        Kong *kong;
        Platform* lastPlat;
        Platform * paulinePlat;
        Ladder* lastLad;
        Pauline* pauline;
        Ladder* lastLadderHitBox_mario;
        Barrel* staticBarrel;
};