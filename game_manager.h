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
class Background;
class Game{
    public:
        Game();
        void draw();
        void update();
        void draw_scene(bool pov);
        void key_pressed(int key);
        void key_released(int key);
        void update_movement();
        void update_cam_mode();
        bool check_collision(
            ofVec3f dim1, ofVec3f pos1,
            ofVec3f dim2, ofVec3f pos2        
        );
        void update_game_mode();

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

        //turn off specific properties
        GLfloat ambientOff[4];
        GLfloat diffuseOff[4];
        GLfloat specularOff[4];




        //ambient light
        GLfloat ambientLight[4];
        bool Ambient = true;
        bool isKeyAPressed = false;


        //directional light
        ofVec3f lightDirection;
        bool Directional = true;
        bool isKeySPressed = false;
        GLfloat dirVec[4];
        GLfloat dirAmb[4];
        GLfloat dirDif[4];
        GLfloat dirSpec[4];
        ofVec3f dirVec3f;
        bool dirAmbOff = false;
        bool dirDiffOff = false;
        bool dirSpecOff = false;
        bool isKeyIPressed = false;
        bool isKeyOPressed = false;
        bool isKeyPPressed = false;
        bool prevDirectional = false;


        //point light
        bool Point = false;
        bool isKeyVPressed = false;
        GLfloat pointPos[4];
        GLfloat pointAmb[4];
        GLfloat pointDif[4];
        GLfloat pointSpec[4];
        ofVec3f pointPosVec;
        bool pointAmbOff = false;
        bool pointDiffOff = false;
        bool pointSpecOff = false;
        bool isKeyJPressed = false;
        bool isKeyKPressed = false;
        bool isKeyLPressed = false;
        bool prevPoint = false;


        //focus light
        bool Focus = false;
        bool isKeyCPressed = false;
        GLfloat spotPos[4];
	    GLfloat spotDir[3];
	    ofVec3f spotDirVec;
        GLfloat spotAmb[4];
	    GLfloat spotDif[4];
	    GLfloat spotSpec[4];
        ofVec3f spotPosVec;
        GLfloat spotCutOff;
        GLfloat spotExponent;
        bool spotAmbOff = false;
        bool spotDiffOff = false;
        bool spotSpecOff = false;
        bool isKeyBPressed = false;
        bool isKeyNPressed = false;
        bool isKeyMPressed = false;
        bool prevFocus = false;

        //gameModes
        bool isKeyTWOPressed = false;
        bool hardModeActive = false;
        bool mediumModeActive = false;
        bool isKeyONEPressed = false;
        bool easyModeActive = true;
        bool customModeActive = false;
        bool isKeyTHREEPressed = false;
        int game_mode;
        int currentGameMode = -1;
        int cam_mode = 1;
        int currentCamMode = -1;



 


        //stats
        bool statsActive = false;
        bool isKeyGPressed = true;
        bool objActive = false;
        bool keysActive = false;
        bool isKeyFPressed = true;
        bool isKeyHPressed = true;







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
        Background* background;
};