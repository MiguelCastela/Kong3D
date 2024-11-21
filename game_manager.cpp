#include "game_manager.h"
#include "mario.h"
#include "plataforma.h"
#include "escadas.h"
#include "barril.h"
#include "particula.h"



Game::Game(){
    glEnable(GL_DEPTH_TEST);
    
    // TODO: MUDAR PARA STARTING POSITION DO MARIO/BARRIL
    marioPos = ofVec3f(0,0,0);
    marioDim = global.marioDim;
    platDim = global.platDim;
    ladDim = global.ladDim;
    ladHitBoxDim = global.ladHitBoxDim;
    fakeLadDim = global.fakeLadDim;
    barrelDim = global.barrelDim;
    barrelPos = ofVec3f(0,0,0);

    cam = new Camera();
    mario = new Mario(marioDim, marioPos);
    barrel = new Barrel(barrelDim, barrelPos);
    



    //barrel
    lastBarrelSpawnTime = 0;
    // Number of platforms
    plat_ct = 10;


    // First platform's position
    ofVec3f base_plat_pos = marioPos;
    base_plat_pos.y -= platDim.y;
    base_plat_pos.y += marioDim.y*0.5; 

    int s=1;


    for(int i = 0; i < plat_ct; i++){        
        // Determine in which half the ladder can be drawn
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

        // Add the ladders and stairs
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
        ladHitBoxVec.push_back(
            new Ladder(
                ladHitBoxDim,
                ofVec3f(cur_lad_pos.x, cur_lad_pos.y+ barrelDim.y*0.5 +1, cur_lad_pos.z)
            )
        );
        platVec.push_back(
            new Platform(
                platDim,
                cur_plat_pos,
                ofVec3f(ofRandom(0, 1), ofRandom(0, 1), ofRandom(0, 1))
            )
        );

        if(i % 2 == 0 && ((i / 2) % 2 == 0)){
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
        s++;
        
    }

    lastPlatPos.y += global.empty_space + platDim.y;
    lastPlatPos.z -= platDim.z;
    lastPlat = new Platform(platDim , lastPlatPos, ofVec3f(0,0,0));


    initBarrelPos = lastPlatPos;
    initBarrelPos.y += platDim.y/2 + barrelDim.y/2;
    barrelPos = initBarrelPos;


    barrelVec.push_back(
        new Barrel(
            barrelDim,
            ofVec3f(barrelPos.x, barrelPos.y, barrelPos.z)
        )
    );
    //cout << "first barrel spawned" << endl;
    barrelsSpawned = 1;




    }

void Game::update(){
    update_movement();
    float curTime = ofGetElapsedTimef();
    barrelSpawnDelay = ofRandom(1.0f, 8.0f);
        if (curTime - lastBarrelSpawnTime >= barrelSpawnDelay) {
        barrelVec.push_back(
            new Barrel(
                barrelDim,
                ofVec3f(barrelPos.x, barrelPos.y, barrelPos.z)
            )
        );

        lastBarrelSpawnTime = curTime;
        barrelsSpawned++;

        //cout << "Barrel spawned at: " << curTime << " seconds." << endl;
    }
    
    
    
    
    
    
    marioPos = mario->position;

    if(!mario->is_climbing){
        mario->marioLookAt.y = marioPos.y;
        mario->marioLookAt.z = marioPos.z;
    }

    bool flag = false;
    mario->on_ladder = false;
    for(auto curLad : ladVec){
        if (check_collision(marioDim, marioPos, curLad->dimension, curLad->position)) {
            mario->next_position_y = mario->base_position_y + ladDim.y;
            flag = true;
        }
    }
    if(!flag){
        mario->on_ladder = true;
        mario->is_climbing = false;
    }
    for(auto curBar : barrelVec){
    if (check_collision(marioDim, marioPos, curBar->dimensions, curBar->position)) {
        cout << "Collision detected" << endl;
        mario_dead = true;
            explosion.push_back(
        new Particle(
            marioPos,
            ofVec3f(1, 1, 1),
            ofVec3f(1, 0, 0)
        )
        );



  
        }
        
    
        bool ladder_collision = false;
        //curBar->next_position_z = curBar->position.z + barrelDim.z*0.5;
        //curBar->next_position_y = curBar->position.y - ladDim.y;
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
    draw_scene();
    cam -> miniMap(marioPos);
    draw_scene();

}

void Game::draw_scene(){
    if(!cam->camFlag && !mario_dead){
        mario->draw();
    }else{
        mario->draw_pov();
    }
    
    for(auto cur_plat: platVec){
        cur_plat->draw();
    }    
    lastPlat->draw();
    for(auto cur_lad: ladVec){
        cur_lad->draw();
    }
    for(auto cur_lad: fakeLadVec){
        cur_lad->draw_fake_lad();
    }
    for(auto cur_lad: ladHitBoxVec){
        cur_lad->draw_hitbox();
    }
    for(auto curBar : barrelVec){
        curBar->draw();
    }
    if(mario_dead){
        for(auto curExplosion : explosion){
            curExplosion->draw();
        }
    }
    
}
void Game::key_pressed(int key){
    if (key == 'T' || key == 't') {
        cam->camMode = ((cam->camMode)+1)%3;
    } 
}

void Game::update_movement(){
    if(ofGetKeyPressed(OF_KEY_RIGHT) && !mario->is_climbing){
        mario->move_right();
    }
    if(ofGetKeyPressed(OF_KEY_LEFT) && !mario->is_climbing){
        mario->move_left();
    }
    if(ofGetKeyPressed(OF_KEY_UP) && !mario->on_ladder && !mario->isJumping){
        mario->climb_up();
    }
    if(ofGetKeyPressed(OF_KEY_DOWN) && !mario->on_ladder && !mario->isJumping){
        mario->climb_down();
    }
    if(ofGetKeyPressed(' ')){
        if(!mario->is_climbing){
            mario->start_jump();
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


