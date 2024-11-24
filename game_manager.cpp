#include "game_manager.h"
#include "mario.h"
#include "plataforma.h"
#include "escadas.h"
#include "barril.h"
#include "particula.h"
#include "donkey_kong.h"
#include "pauline.h"



Game::Game(){
    glEnable(GL_DEPTH_TEST);
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    
    
    marioPos = global.marioPos;
    marioDim = global.marioDim;

    platDim = global.platDim;

    ladDim = global.ladDim;
    ladHitBoxDim = global.ladHitBoxDim_barrel;
    ladHitBoxDim_mario = global.ladHitBoxDim_mario;
    fakeLadDim = global.fakeLadDim;

    barrelDim = global.barrelDim;
    barrelPos = global.barrelPos;

    kongPos = global.kongPos;
    kongDim = global.kongDim;

    paulinePos = global.paulinePos;
    paulineDim = global.paulineDim;

    cam = new Camera();
    mario = new Mario(marioDim, marioPos);
    barrel = new Barrel(barrelDim, barrelPos);
    kong = new Kong(kongDim, kongPos);
    pauline = new Pauline(paulineDim, paulinePos);

    remainingParticles = 500;
    lastParticleBurstTime = 0.0f;
    lastBarrelSpawnTime = 0;




    plat_ct = 10;
    cam->num_platforms = plat_ct;


    ofVec3f base_plat_pos = marioPos;
    base_plat_pos.y -= platDim.y;
    base_plat_pos.y += marioDim.y*0.5; 


    for(int i = 0; i < plat_ct; i++){        
        GLfloat ladder_right_lim;
        GLfloat ladder_left_lim;
        if(i % 2 == 0){
            ladder_right_lim = 0 + (ladDim.x);
            ladder_left_lim = global.right_limit - (ladDim.x*0.5); 
        }
        else{
            ladder_left_lim = 0 - (ladDim.x);
            ladder_right_lim = global.left_limit + (ladDim.x*0.5);
        }

        ofVec3f cur_plat_pos = base_plat_pos; 
        cur_plat_pos.y += (i*global.empty_space) + (i*platDim.y);
        cur_plat_pos.z -= i*platDim.z;
        ofVec3f cur_lad_pos = ofVec3f(
            ofRandom(ladder_left_lim, ladder_right_lim), 
            cur_plat_pos.y + (ladDim.y*0.5) + (platDim.y*0.5),
            cur_plat_pos.z - (platDim.z*0.5) - (ladDim.z*0.5)  
        );
        ladVec.push_back(
            new Ladder(
                ladDim,
                cur_lad_pos
            )
        );
        ladHitBoxVec_mario.push_back(
            new Ladder(
                ladHitBoxDim_mario,
                ofVec3f(cur_lad_pos.x, cur_lad_pos.y, cur_lad_pos.z)
            )
        );
        if (i!=0){
        ladHitBoxVec.push_back(
            new Ladder(
                ladHitBoxDim,
                ofVec3f(cur_lad_pos.x, cur_lad_pos.y+ barrelDim.y*0.5 +1, cur_lad_pos.z)
            )
        );
        }
        float blueIntensity = 0.4f + (i / float(plat_ct)) * 0.6f;        
        platVec.push_back(
            new Platform(
                platDim,
                cur_plat_pos,
                ofVec3f(0.0f, 0.15f, blueIntensity)
            )
        );
        if(i == 2 || (i % 2 == 0 && ((i / 2) % 2 == 0 && i !=0 ) )){
            GLfloat fake_ladder_left_lim = 0 - (ladDim.x);
            GLfloat fake_ladder_right_lim = global.left_limit + (ladDim.x*0.5);


            ofVec3f fake_lad_pos = ofVec3f(
                ofRandom(fake_ladder_left_lim, fake_ladder_right_lim), 
                cur_plat_pos.y + (ladDim.y*0.5) + (platDim.y*0.5),
                cur_plat_pos.z - (platDim.z*0.5) - (ladDim.z*0.5)  
            );

            fakeLadVec.push_back(
                new Ladder(
                    fakeLadDim,
                    fake_lad_pos
                )
            );
        }
        lastPlatPos = cur_plat_pos;   
    }

    lastPlatPos.y += global.empty_space + platDim.y;
    lastPlatPos.z -= platDim.z;
    lastPlat = new Platform(ofVec3f(platDim.x, platDim.y, platDim.z) , lastPlatPos, ofVec3f(0.7,0.1,0));

    paulinePlatPos = lastPlatPos;

    paulinePlatPos.y += global.empty_space + platDim.y;
    paulinePlatPos.z -= platDim.z;
    paulinePlatPos.x += platDim.x*0.25 - ladDim.x;

    paulinePos = paulinePlatPos;
    paulinePos.y += platDim.y*0.5 + paulineDim.y*0.5;
    paulinePos.x += platDim.x*0.25 - paulineDim.x;

    paulinePlat = new Platform(ofVec3f(platDim.x * 0.5, platDim.y, platDim.z) , paulinePlatPos, ofVec3f(0.85, 0.6, 0.8));

    pauline = new Pauline(paulineDim, paulinePos);

    lastLadderPos = lastPlatPos;
    lastLadderPos.y += platDim.y/2 + ladDim.y/2;
    lastLadderPos.z -= platDim.z/2 + ladDim.z/2;
    lastLad = new Ladder(ladDim, lastLadderPos);
    lastLadderHitBox_mario = new Ladder(ladHitBoxDim_mario, ofVec3f(lastLadderPos.x, lastLadderPos.y, lastLadderPos.z)); 

    ladHitBoxVec_mario.push_back(
        lastLadderHitBox_mario
    );

    initBarrelPos = lastPlatPos;
    initBarrelPos.y += platDim.y/2 + barrelDim.y/2;
    initBarrelPos.x = global.right_limit - 2*kongDim.x;
    barrelPos = initBarrelPos;

    staticBarrel = new Barrel(barrelDim, ofVec3f(barrelPos.x, barrelPos.y, barrelPos.z));
    
    //cout << "first barrel spawned" << endl;
    barrelsSpawned = 1;

    for(int i=0; i<plat_ct -2; i++){
        barrelVec.push_back(
            new Barrel(
                barrelDim,
                ofVec3f(barrelPos.x + 2*kongDim.x, barrelPos.y - (i* ladDim.y), barrelPos.z + (i*platDim.z))
            )   
        );
    }
    kongPos = barrelPos;
    kongPos.x += kongDim.x;
    kong = new Kong(kongDim, ofVec3f(kongPos.x, kongPos.y, kongPos.z));
}

void Game::update(){



    update_movement();

    cam->meters = marioPos.y;
    float curTime = ofGetElapsedTimef();
    barrelSpawnDelay = ofRandom(1.0f, 800.0f);
    if (curTime - lastBarrelSpawnTime >= barrelSpawnDelay) {
        barrelVec.push_back(
        new Barrel(
            barrelDim,
            ofVec3f(barrelPos.x, barrelPos.y, barrelPos.z)
            )
        );

        lastBarrelSpawnTime = curTime;
        barrelsSpawned++;
    }
    pauline->winState = false;
    mario->winState = false;
    if (marioPos.y == paulinePos.y) {
        pauline->winState = true;
        mario->winState = true;
        cout << "Mario wins!" << endl;
        mario_wins = true;
        if (!explosion_created) {
            // Create victory particles
            for (int i = 0; i < 100; i++) {
                explosion.push_back(
                    new Particle(
                        marioPos,
                        ofVec3f(1, 1, 1),
                        ofVec3f(ofRandom(0,1),ofRandom(0,1),ofRandom(0,1) ) 
                    )
                );
            }
            for (int i = 0; i < 100; i++) {
                explosion.push_back(
                    new Particle(
                        paulinePos,
                        ofVec3f(1, 1, 1),
                        ofVec3f(ofRandom(0,1),ofRandom(0,1),ofRandom(0,1) ) 
                    )
                );
            }
            explosion_created = true;
            remainingParticles = 500;
        }
        mario->times_dead = 0;
        mario->dead = false;
        mario_dead = true;  
    }

    if (mario_wins && remainingParticles > 0) {
        float currentTime = ofGetElapsedTimef();
        if(currentTime - lastParticleBurstTime >= 0.1f){
            int burstCount = std::min(particlesPerBurst, remainingParticles);
            for(int i =0; i<burstCount; i++){
                explosion.push_back(
                    new Particle(
                        ofVec3f(ofRandom(marioPos.x, paulinePos.x), marioPos.y + marioDim.y*5, marioPos.z),
                        ofVec3f(1, 1, 1),
                        ofVec3f(ofRandom(0,1),ofRandom(0,1),ofRandom(0,1) ) 
                    )
                );
            }
            remainingParticles -= burstCount;
            lastParticleBurstTime = currentTime;
        }
    }

    if (mario_wins){
            if (!explosion_kong) {
            for (int i = 0; i < 100; i++) {
                explosion.push_back(
                    new Particle(
                        kongPos,
                        ofVec3f(1, 1, 1),
                        ofVec3f(0.5, 0.35, 0.05)
                    )
                );
            }
            explosion_kong = true;
        }
        if (!explosion_barrel) {
            for (int i = 0; i < 100; i++) {
                explosion.push_back(
                    new Particle(
                        ofVec3f(barrelPos.x, barrelPos.y, barrelPos.z),
                        ofVec3f(1, 1, 1),
                        ofVec3f(1.0f, 0.5f, 0.0f) 
                    )
                );
            }
            explosion_barrel = true;
        }
    }
    if (mario_dead && !mario->isRespawning) {
    // Reset the explosion flags when Mario respawns
    explosion_kong = false;
    explosion_barrel = false;
    }    

    
    // se quiser barris a dar clean up dps de cada morte
    /*
    if(mario_dead && !barrels_reset){
        barrelVec.clear();
           for(int i=0; i<plat_ct - 2; i++){
        barrelVec.push_back(
            new Barrel(
                barrelDim,
                ofVec3f(barrelPos.x, barrelPos.y - (i* ladDim.y), barrelPos.z + (i*platDim.z))
            )   
        );
    }
    barrels_reset = true;
    }

    if(barrels_reset && !mario_dead){
        barrels_reset = false;
    }
    */
    

    for(auto curExplosion : explosion){
        curExplosion->update();
    }
    
    marioPos = mario->position;

    if(!mario->is_climbing){
        mario->marioLookAt.y = marioPos.y;
        mario->marioLookAt.z = marioPos.z;
    }

    bool flag = false;
    flag_down = false;
    mario->on_ladder = false;
    for(auto curLad : ladHitBoxVec_mario){
        if (check_collision(marioDim, marioPos, curLad->dimension, curLad->position)) { 
            //std::cout << "Collision with ladder detected after respawn!" << std::endl;
            mario->next_position_y = mario->base_position_y + ladDim.y;
            flag = true;
        }
    }
    if(!flag){
        mario->going_up = true;
        mario->on_ladder = true;
        mario->is_climbing = false;
    }
    
    for(auto curLad: ladHitBoxVec){
        if (check_collision(marioDim, marioPos, curLad->dimension, curLad->position)) {
            flag_down = true;
        }
    }
    
    for(auto curBar : barrelVec){
        if (check_collision(marioDim, marioPos, curBar->dimensions, curBar->position) || check_collision(marioDim, marioPos, kongDim , kongPos) || check_collision(marioDim, marioPos, barrelDim, barrelPos)) {
            if(!explosion_created){
            //cout << "Collision detected" << endl;
                mario_dead = true;
                mario->dead = true;
                for (int i = 0; i < 75; i++) {
                explosion.push_back(
                    new Particle(
                        marioPos,
                        ofVec3f(1, 1, 1),
                        ofVec3f(1, 0, 0)
                    )
                );
                }
                for (int i = 0; i < 25; i++) {
                explosion.push_back(
                    new Particle(
                        curBar->position,
                        ofVec3f(1, 1, 1),
                        ofVec3f(0, 0, 1)
                    )
                );
                }
                for(int i=0; i < 50 ; i++){
                explosion.push_back(
                    new Particle(
                        curBar->position,
                        ofVec3f(1, 1, 1),
                        ofVec3f(1.0, 0.8, 0.6)
                    )
                );
                }
                explosion_created = true;
            }
        }
        
        bool ladder_collision = false;
        for(auto curLad : ladHitBoxVec){
            if (check_collision(curBar->dimensions, curBar->position, curLad->dimension, curLad->position)) {
            //cout << "collision from barrel with ladder" << endl;
            ladder_collision = true;
            curBar->on_ladder = true;
            }
        }
        if (ladder_collision && curBar->on_ladder) {
            //cout << "Calling move_down()" << endl;
            curBar->move_down();
            } else if (!curBar->on_ladder) {
            if (curBar->is_moving_left) {
            curBar->move_back();
            } else {
            curBar->move_front();
            }
        }
        if (curBar->leave_ladder) {
            //cout << "Leaving ladder, resetting state." << endl;
            curBar->on_ladder = false;
            curBar->leave_ladder = false;
        }
    }
}

void Game::draw(){

    cam->apply(marioPos, mario->marioLookAt);
    //cout << mario->marioLookAt.x << " " << mario->marioLookAt.y << " " << mario->marioLookAt.z << endl;
    if (mario_dead) {
        mario->spawn_back();
        cam->num_lives = mario->times_dead;

 
        if (mario_dead && !mario->isRespawning) {
            mario_dead = false;  
            explosion_created = false;
            explosion_kong = false;
            explosion_barrel = false;


            if (mario_wins) {
                cout << "Mario has won! Resetting state..." << endl;
            }
            mario_wins = false;
  
        }
        draw_scene(true);
        return;
    }
    if(cam->camMode == 2){
        draw_scene(true);
        cam->miniMap(marioPos);
        draw_scene(false);
    }
    else{
        draw_scene(false);
        cam->miniMap(marioPos);
        draw_scene(false);
    }
}

void Game::draw_scene(bool pov){
glPushMatrix();

        if(!pov || mario_wins){
            mario->draw();
        }
        
        for(auto cur_plat: platVec){
            cur_plat->draw();
        }    
        lastPlat->draw();
        paulinePlat->draw();
        for(auto cur_lad: ladVec){
            cur_lad->draw();
        }
        for(auto cur_lad: fakeLadVec){
            cur_lad->draw_fake_lad();
        }
        //debug
        /*
        for(auto cur_lad: ladHitBoxVec){
            cur_lad->draw_hitbox();
        }
        for(auto cur_lad: ladHitBoxVec_mario){
            cur_lad->draw_hitbox();
        }
        */
        for(auto curBar : barrelVec){
            if(curBar->is_active){
                curBar->draw();
            }    
        }
        if(!mario_wins){
            kong->draw();
        }
        pauline->draw();
        lastLad->draw_golden();
        if(!mario_wins){
            staticBarrel->draw();
        }
            lastLadderHitBox_mario->draw_hitbox();

        if(mario_dead){
            for(auto curExplosion : explosion){
                curExplosion->draw();
            }
        }
glPopMatrix();
}
void Game::key_pressed(int key){
    if (key == 'T' || key == 't') {
        cam->camMode = ((cam->camMode)+1)%3;
    } 
}

void Game::update_movement(){
    if (ofGetKeyPressed(OF_KEY_DOWN) && ofGetKeyPressed(' ') && !flag_down  && !mario->isRespawning) {
        if(!mario->is_climbing){
            mario->start_jump();
            mario->jump_down();
    }
    }
    
    if(!ofGetKeyPressed(OF_KEY_DOWN) && ofGetKeyPressed(' ')){
        if(!mario->is_climbing){
            mario->start_jump();
        }
    }
    if(ofGetKeyPressed(OF_KEY_RIGHT) && !mario->is_climbing && !mario->isRespawning){
        mario->move_right();
    }
    if(ofGetKeyPressed(OF_KEY_LEFT) && !mario->is_climbing && !mario->isRespawning){
        mario->move_left();
    }
    if(ofGetKeyPressed(OF_KEY_UP) && !mario->on_ladder && !mario->isJumping && !mario->isRespawning){
        mario->climb_up();
    }
    if(ofGetKeyPressed(OF_KEY_DOWN) && !mario->on_ladder && !mario->isJumping && !mario->isRespawning){
        mario->climb_down();
    }
    if (ofGetKeyPressed(OF_KEY_DOWN) && !ofGetKeyPressed(OF_KEY_LEFT) && !ofGetKeyPressed(OF_KEY_RIGHT) && !flag_down && !mario->isRespawning && !mario->is_climbing)  {
        mario->go_down();
    }
    if(ofGetKeyPressed(OF_KEY_UP) && !ofGetKeyPressed(OF_KEY_LEFT) && !ofGetKeyPressed(OF_KEY_RIGHT) && !mario->is_climbing && !mario->isJumping && !mario->isRespawning){
        mario->look_front();
    }

}

bool Game::check_collision(ofVec3f dim1, ofVec3f pos1, ofVec3f dim2, ofVec3f pos2){
    return (
        fabs(pos1.x - pos2.x) * 2 < (dim1.x + dim2.x)&&
        fabs(pos1.y - pos2.y) * 2 < (dim1.y + dim2.y)   
    );
}


void Game::key_released(int key){
}


