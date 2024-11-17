#include "game_manager.h"
#include "mario.h"
#include "plataforma.h"
#include "escadas.h"
//#include "global.h"



Game::Game(){
    glEnable(GL_DEPTH_TEST);
    
    // TODO: MUDAR PARA STARTING POSITION DO MARIO
    marioPos = ofVec3f(0,0,0);
    marioDim = global.marioDim;
    platDim = global.platDim;
    ladDim = global.ladDim;

    cam = new Camera();
    mario = new Mario(marioDim, marioPos);

    // Number of platforms
    plat_ct = 10;

    // First platform's position
    ofVec3f base_plat_pos = marioPos;
    base_plat_pos.y -= platDim.y;
    base_plat_pos.y += marioDim.y*0.5; 
    for(int i = 0; i < plat_ct; i++){        
        // Determine in which half the ladder can be drawn
        GLfloat ladder_right_lim;
        GLfloat ladder_left_lim;
        if(i % 2 == 0){
            ladder_right_lim = 0;
            ladder_left_lim = global.right_limit - (ladDim.x*0.5); 
        }
        else{
            ladder_left_lim = 0;
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
        platVec.push_back(
            new Platform(
                platDim,
                cur_plat_pos,
                ofVec3f(ofRandom(0, 1), ofRandom(0, 1), ofRandom(0, 1))
            )
        );
    }
}

void Game::update(){
    update_movement();
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
}

void Game::draw(){
    cam->apply(marioPos, mario->marioLookAt);
    cout << mario->marioLookAt.x << " " << mario->marioLookAt.y << " " << mario->marioLookAt.z << endl;
    draw_scene();

}

void Game::draw_scene(){
    mario->draw();
    
    for(auto cur_plat: platVec){
        cur_plat->draw();
    }    

    for(auto cur_lad: ladVec){
        cur_lad->draw();
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
    if(ofGetKeyPressed(OF_KEY_DOWN) && !mario->isJumping){
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


