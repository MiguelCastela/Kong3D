#include "game_manager.h"
#include "mario.h"
#include "plataforma.h"
#include "escadas.h"
#include "barril.h"
#include "particula.h"
#include "donkey_kong.h"
#include "pauline.h"



Game::Game(){


    ofDisableArbTex();
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
        float blueIntensity = 0.4f + (i / float(plat_ct)) * 0.5f;        
        platVec.push_back(
            new Platform(
                platDim,
                cur_plat_pos,
                21
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
    lastPlat = new Platform(ofVec3f(platDim.x, platDim.y, platDim.z) , lastPlatPos, 15);

    paulinePlatPos = lastPlatPos;

    paulinePlatPos.y += global.empty_space + platDim.y;
    paulinePlatPos.z -= platDim.z;
    paulinePlatPos.x += platDim.x*0.25 - ladDim.x;

    paulinePos = paulinePlatPos;
    paulinePos.y += platDim.y*0.5 + paulineDim.y*0.5;
    paulinePos.x += platDim.x*0.25 - paulineDim.x;

    paulinePlat = new Platform(ofVec3f(platDim.x * 0.5, platDim.y, platDim.z) , paulinePlatPos, 27);

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
    //kong = new Kong(kongDim, ofVec3f(0, 0, 0));




}

void Game::update(){



    update_movement();






    cam->meters = marioPos.y;
    float curTime = ofGetElapsedTimef();
    barrelSpawnDelay = ofRandom(1.0f, 55.0f);
    
    if(!mario->isRespawning){
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
                        ofRandom(1, 23)
                    )
                );
            }
            for (int i = 0; i < 100; i++) {
                explosion.push_back(
                    new Particle(
                        paulinePos,
                        ofVec3f(1, 1, 1),
                        ofRandom(1, 23)

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
                        ofRandom(1, 23)
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
                        19

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
                        9

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
                        22

                    )
                );
                }
                for (int i = 0; i < 25; i++) {
                explosion.push_back(
                    new Particle(
                        curBar->position,
                        ofVec3f(1, 1, 1),
                        18
                    )
                );
                }
                for(int i=0; i < 50 ; i++){
                explosion.push_back(
                    new Particle(
                        curBar->position,
                        ofVec3f(1, 1, 1),
                        21
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


    //lights update 

    spotPosVec = ofVec3f(kongPos.x - kongDim.x*0.1, kongPos.y + kongDim.y + kongDim.y*0.30, kongPos.z);
    spotDirVec = ofVec3f(global.left_limit*100, kongPos.y - kongDim.y*2, kongPos.z);




    pointPosVec[0] = marioPos.x;
    pointPosVec[1] = marioPos.y + 0.5 *marioDim.y;
    pointPosVec[2] = marioPos.z ;

    global.load_textures();


}

void Game::draw(){

    cam->apply(marioPos, mario->marioLookAt);
    //cout << mario->marioLookAt.x << " " << mario->marioLookAt.y << " " << mario->marioLookAt.z << endl;
    if (mario_dead) {
        if (cam -> camMode == 0) {
        cam -> camMode = 2;
        }
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


if (cam->camMode == 0) {
    draw_scene(true);

    if (statsActive) {
        cam->draw_stats();
    } else if (objActive) {
        cam->draw_objective();
    } else if (keysActive) {
        cam->draw_keys();
    }

    cam->miniMap(marioPos);
    draw_scene(false);
} else if (cam->camMode == 2) {
    draw_scene(false);

    if (statsActive) {
        cam->draw_stats();
    } else if (objActive) {
        cam->draw_objective();
    } else if (keysActive) {
        cam->draw_keys();
    }

    cam->miniMap(marioPos);
    draw_scene(false);
} else {
    draw_scene(false);

    if (statsActive) {
        cam->draw_stats();
    } else if (objActive) {
        cam->draw_objective();
    } else if (keysActive) {
        cam->draw_keys();
    }

    draw_scene(false);
}

}

void Game::draw_scene(bool pov){
    glPushMatrix();

        //lights

        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
        glShadeModel(GL_SMOOTH);


        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);


        ambientOff[0] = 0.0;
        ambientOff[1] = 0.0;
        ambientOff[2] = 0.0;
        ambientOff[3] = 1.0;

        diffuseOff[0] = 0.0;
        diffuseOff[1] = 0.0;
        diffuseOff[2] = 0.0;
        diffuseOff[3] = 1.0;

        specularOff[0] = 0.0;
        specularOff[1] = 0.0;
        specularOff[2] = 0.0;
        specularOff[3] = 1.0;



        if (Ambient) {
            GLfloat ambientLight[] = {1, 1, 1, 1.0}; // Moderate ambient light
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
        } else {
            GLfloat ambientLight[] = {0.0, 0.0, 0.0, 1.0}; // No ambient light
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
        }
        

        dirVec[0] = 0.;
        dirVec[1] = 1.;
        dirVec[2] = 1.;
        dirVec[3] = 0;

        dirAmb[0] = 1.;//R
        dirAmb[1] = 1.;//G
        dirAmb[2] = 1.;//B
        dirAmb[3] = 1.;//constante

        dirDif[0] = 1.;//R
        dirDif[1] = 1.;//G
        dirDif[2] = 1.;//B
        dirDif[3] = 1.;//constante

        dirSpec[0] = 1.;//R
        dirSpec[1] = 1.;//G
        dirSpec[2] = 1.;//B
        dirSpec[3] = 1.;//constante

        glLightfv(GL_LIGHT0, GL_POSITION, dirVec);
        glLightfv(GL_LIGHT0, GL_AMBIENT, dirAmb);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, dirDif);
        glLightfv(GL_LIGHT0, GL_SPECULAR, dirSpec);


        if(Directional){   
            if(!prevDirectional){
                dirAmbOff = false;
                dirDiffOff = false;
                dirSpecOff = false;
            }
            glEnable(GL_LIGHT0);

            if(dirAmbOff)
                glLightfv(GL_LIGHT0, GL_AMBIENT, ambientOff);
            if(dirDiffOff)
                glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseOff);
            if(dirSpecOff)
                glLightfv(GL_LIGHT0, GL_SPECULAR, specularOff);
        }else{
            glDisable(GL_LIGHT0);
        }
        prevDirectional = Directional;


        pointPos[0] = pointPosVec.x;
        pointPos[1] = pointPosVec.y;
        pointPos[2] = pointPosVec.z;
        pointPos[3] = 1.;//ponto - posi��o!

        pointAmb[0] = 1.; // R
        pointAmb[1] = 1.; // G
        pointAmb[2] = 1.; // B
        pointAmb[3] = 1.0; // Constant

        pointDif[0] = 1.; // R
        pointDif[1] = 1.; // G
        pointDif[2] = 1.; // B
        pointDif[3] = 1.0; // Constant

        pointSpec[0] = 1.; // R
        pointSpec[1] = 1.; // G
        pointSpec[2] = 1.; // B
        pointSpec[3] = 1.0; // Constant

        glLightfv(GL_LIGHT1, GL_POSITION, pointPos);
        glLightfv(GL_LIGHT1, GL_AMBIENT, pointAmb);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, pointDif);
        glLightfv(GL_LIGHT1, GL_SPECULAR, pointSpec);

        glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0); // Keep constant attenuation
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.02);  // Lower linear attenuation
        glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.002); // Lower quadratic attenuation



        
        if (Point) {
            if (!prevPoint) {
                pointAmbOff = false;
                pointDiffOff = false;
                pointSpecOff = false;
            }
            glEnable(GL_LIGHT1);

            if(pointAmbOff)
                glLightfv(GL_LIGHT1, GL_AMBIENT, ambientOff);
            if(pointDiffOff)
                glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseOff);
            if(pointSpecOff)
                glLightfv(GL_LIGHT1, GL_SPECULAR, specularOff);
        }
        else {
            glDisable(GL_LIGHT1);
        }
        prevPoint = Point;


        spotPos[0] = spotPosVec.x;
        spotPos[1] = spotPosVec.y; 
        spotPos[2] = spotPosVec.z;
        spotPos[3] = 1.;


        //direcao
        spotDir[0] = spotDirVec.x;
        spotDir[1] = spotDirVec.y;
        spotDir[2] = spotDirVec.z;
        //spotDir[3] = 0.;N�o tem a 4 coordenada, � sempre vetor

        //ambiente
        spotAmb[0] = 1.;//R
        spotAmb[1] = 1.;//G
        spotAmb[2] = 1.;//B
        spotAmb[3] = 1.;//constante

        //difusa
        spotDif[0] = 1.;//R
        spotDif[1] = 1.;//G
        spotDif[2] = 1.;//B
        spotDif[3] = 1.;//constante

        //specular
        spotSpec[0] = 1.;//R
        spotSpec[1] = 1.;//G
        spotSpec[2] = 1.;//B
        spotSpec[3] = 1.;//constante

        glLightfv(GL_LIGHT2, GL_POSITION, spotPos);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);
        glLightfv(GL_LIGHT2, GL_AMBIENT, spotAmb);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, spotDif);
        glLightfv(GL_LIGHT2, GL_SPECULAR, spotSpec);
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.02);
        glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.002);

        spotCutOff = 80;  
        spotExponent = 0.5;  
        
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutOff);
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);

        if (Focus) {
            if (!prevFocus) {
                spotAmbOff = false;
                spotDiffOff = false;
                spotSpecOff = false;
            }
            glEnable(GL_LIGHT2);
            if(spotAmbOff)
                glLightfv(GL_LIGHT2, GL_AMBIENT, ambientOff);
            if(spotDiffOff)
                glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseOff);
            if(spotSpecOff)
                glLightfv(GL_LIGHT2, GL_SPECULAR, specularOff);
        } else {
            glDisable(GL_LIGHT2);   
        }
        prevFocus = Focus;

        //draw 
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
        /*
        for(auto curBar : barrelVec){
            if(curBar->is_active){
                curBar->draw();
            }    
        }
        */
        for (auto it = barrelVec.begin(); it != barrelVec.end();) {
            Barrel* curBar = *it;
            if (!curBar->is_active) {
                delete curBar; // Destroy the barrel
                it = barrelVec.erase(it); // Remove from the vector
            } else {
                curBar->draw(); // Only draw active barrels
                ++it;
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
        //debug
        //lastLadderHitBox_mario->draw_hitbox();

        /*
        if(mario_dead){
            for(auto curExplosion : explosion){
                curExplosion->draw();
            }
        }
        */



        if (mario_dead) {
            for (auto it = explosion.begin(); it != explosion.end();) {
                Particle* curExplosion = *it;
                if (!curExplosion->isAlive) {
                    delete curExplosion;          // Manually delete
                    it = explosion.erase(it);     // Remove from container
                } else {
                    curExplosion->draw();         // Draw remaining particles
                    ++it;
                }
            
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
    if(cam->camMode != 0){
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

    }else{
        if ((ofGetKeyPressed('s') || ofGetKeyPressed('S')) && ofGetKeyPressed(' ') && !flag_down  && !mario->isRespawning) {
            if(!mario->is_climbing){
            mario->start_jump();
            mario->jump_down();
        }
        }
        
        
        
        if(!(ofGetKeyPressed('s') || ofGetKeyPressed('S')) && ofGetKeyPressed(' ')){
            if(!mario->is_climbing){
            mario->start_jump();
            }
        }
        if(ofGetKeyPressed(OF_KEY_UP) && !mario->is_climbing && !mario->isRespawning){
            mario->move_right();
        }
        if(ofGetKeyPressed(OF_KEY_DOWN) && !mario->is_climbing && !mario->isRespawning){
            mario->move_left();
        }
        if(ofGetKeyPressed('w') && !mario->on_ladder && !mario->isJumping && !mario->isRespawning){
            mario->climb_up();
        }
        if((ofGetKeyPressed('s') || ofGetKeyPressed('S')) && !mario->on_ladder && !mario->isJumping && !mario->isRespawning){
            mario->climb_down();
        }
        if ((ofGetKeyPressed('s') || ofGetKeyPressed('S')) && !ofGetKeyPressed(OF_KEY_DOWN) && !ofGetKeyPressed(OF_KEY_UP) && !flag_down && !mario->isRespawning && !mario->is_climbing)  {
            mario->go_down();
        }
        if(ofGetKeyPressed('w') && !ofGetKeyPressed(OF_KEY_DOWN) && !ofGetKeyPressed(OF_KEY_UP) && !mario->is_climbing && !mario->isJumping && !mario->isRespawning){
            mario->look_front();
        }
    }


    if ((ofGetKeyPressed('z') || ofGetKeyPressed('Z')) && !mario->isRespawning) {
        if (!isKeyAPressed) { // Key was not pressed in the previous frame
            Ambient = !Ambient; // Toggle ambient light
            cout << "Ambient light: " << (Ambient ? "ON" : "OFF") << endl;
            isKeyAPressed = true; // Mark key as pressed
        }
    } else {
        if (isKeyAPressed) {
            cout << "Key 'a' is now released." << endl;
            isKeyAPressed = false; // Reset when key is released
        }
    }
    if((ofGetKeyPressed('x') || ofGetKeyPressed('X'))&& !mario->isRespawning){
        if(!isKeySPressed){
            Directional = !Directional;
            cout << "Directional light: " << (Directional ? "ON" : "OFF") << endl;
            isKeySPressed = true;
        }
    }else{
        if(isKeySPressed){
            cout << "Key 's' is now released." << endl;
            isKeySPressed = false;
        }
    }
    if((ofGetKeyPressed('c') || ofGetKeyPressed('C')) && !mario->isRespawning){
        if(!isKeyVPressed){
            Point = !Point;
            cout << "Point light: " << (Point ? "ON" : "OFF") << endl;
            isKeyVPressed = true;
        }
    }else{
        if(isKeyVPressed){
            cout << "Key 'v' is now released." << endl;
            isKeyVPressed = false;
        }
    }

    if((ofGetKeyPressed('v') || ofGetKeyPressed('V')) && !mario->isRespawning){
        if(!isKeyCPressed){
            Focus = !Focus;
            cout << "Focus light: " << (Focus ? "ON" : "OFF") << endl;
            isKeyCPressed = true;
        }
    }else{
        if(isKeyCPressed){
            cout << "Key 'c' is now released." << endl;
            isKeyCPressed = false;
        }

    }

    if((ofGetKeyPressed('i') || ofGetKeyPressed('I')) && !mario->isRespawning){
        if(!isKeyIPressed){
            dirAmbOff = !dirAmbOff;
            cout << "Directional ambient light: " << (dirAmbOff ? "OFF" : "ON") << endl;
            isKeyIPressed = true;
        }
    }else{
        if(isKeyIPressed){
            cout << "Key 'i' is now released." << endl;
            isKeyIPressed = false;
        }
    }
    if((ofGetKeyPressed('o') || ofGetKeyPressed('O')) && !mario->isRespawning){
        if(!isKeyOPressed){
            dirDiffOff = !dirDiffOff;
            cout << "Directional diffuse light: " << (dirDiffOff ? "OFF" : "ON") << endl;
            isKeyOPressed = true;
        }
    }else{
        if(isKeyOPressed){
            cout << "Key 'o' is now released." << endl;
            isKeyOPressed = false;
        }
    }
    if((ofGetKeyPressed('p') || ofGetKeyPressed('P')) && !mario->isRespawning){
        if(!isKeyPPressed){
            dirSpecOff = !dirSpecOff;
            cout << "Directional specular light: " << (dirSpecOff ? "OFF" : "ON") << endl;
            isKeyPPressed = true;
        }
    }else{
        if(isKeyPPressed){
            cout << "Key 'p' is now released." << endl;
            isKeyPPressed = false;
        }
    }

    if((ofGetKeyPressed('j') || ofGetKeyPressed('J')) && !mario->isRespawning){
        if(!isKeyJPressed){
            pointAmbOff = !pointAmbOff;
            cout << "Point ambient light: " << (pointAmbOff ? "OFF" : "ON") << endl;
            isKeyJPressed = true;
        }
    }else{
        if(isKeyJPressed){
            cout << "Key 'k' is now released." << endl;
            isKeyJPressed = false;
        }
    }
    if((ofGetKeyPressed('k') || ofGetKeyPressed('K')) && !mario->isRespawning){
        if(!isKeyKPressed){
            pointDiffOff = !pointDiffOff;
            cout << "Point diffuse light: " << (pointDiffOff ? "OFF" : "ON") << endl;
            isKeyKPressed = true;
        }
    }else{
        if(isKeyKPressed){
            cout << "Key 'l' is now released." << endl;
            isKeyKPressed = false;
        }
    }
    if((ofGetKeyPressed('l') || ofGetKeyPressed('L')) && !mario->isRespawning){
        if(!isKeyLPressed){
            pointSpecOff = !pointSpecOff;
            cout << "Point specular light: " << (pointSpecOff ? "OFF" : "ON") << endl;
            isKeyLPressed = true;
        }
    }else{
        if(isKeyLPressed){
            cout << "Key 'ç' is now released." << endl;
            isKeyLPressed = false;
        }
    }

    if((ofGetKeyPressed('b') || ofGetKeyPressed('B')) && !mario->isRespawning){
        if(!isKeyBPressed){
            spotAmbOff = !spotAmbOff;
            cout << "Spot ambient light: " << (spotAmbOff ? "OFF" : "ON") << endl;
            isKeyBPressed = true;
        }
    }else{
        if(isKeyBPressed){
            cout << "Key 'b' is now released." << endl;
            isKeyBPressed = false;
        }
    }
    if((ofGetKeyPressed('n') || ofGetKeyPressed('N')) && !mario->isRespawning){
        if(!isKeyNPressed){
            spotDiffOff = !spotDiffOff;
            cout << "Spot diffuse light: " << (spotDiffOff ? "OFF" : "ON") << endl;
            isKeyNPressed = true;
        }
    }else{
        if(isKeyNPressed){
            cout << "Key 'n' is now released." << endl;
            isKeyNPressed = false;
        }
    }
    if((ofGetKeyPressed('m') || ofGetKeyPressed('M')) && !mario->isRespawning){
        if(!isKeyMPressed){
            spotSpecOff = !spotSpecOff;
            cout << "Spot specular light: " << (spotSpecOff ? "OFF" : "ON") << endl;
            isKeyMPressed = true;
        }
    }else{
        if(isKeyMPressed){
            cout << "Key 'm' is now released." << endl;
            isKeyMPressed = false;
        }
    }
    if((ofGetKeyPressed('g')|| ofGetKeyPressed('G'))){
        if(!isKeyGPressed){
            objActive = !objActive;
            if (objActive) {
                statsActive = false;
                keysActive = false;
            }            
            cout << "Stats: " << (objActive ? "ON" : "OFF") << endl;
            isKeyGPressed = true;
        }
    }else{
        if(isKeyGPressed){
            isKeyGPressed = false;
        }
    }
    if((ofGetKeyPressed('h')|| ofGetKeyPressed('H'))){
        if(!isKeyHPressed){
            statsActive = !statsActive;
            if (statsActive) {
                objActive = false;
                keysActive = false;
            }        
            cout << "Stats: " << (statsActive ? "ON" : "OFF") << endl;
            isKeyHPressed = true;
        }
    }else{
        if(isKeyHPressed){
            isKeyHPressed = false;
        }
    }
    if((ofGetKeyPressed('f')|| ofGetKeyPressed('F'))){
        if(!isKeyFPressed){
            keysActive = !keysActive;
            if (keysActive) {
                statsActive = false;
                objActive = false;
            }        
            cout << "Keys: " << (keysActive ? "ON" : "OFF") << endl;
            isKeyFPressed = true;
        }
    }else{
        if(isKeyFPressed){
            isKeyFPressed = false;
        }
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


