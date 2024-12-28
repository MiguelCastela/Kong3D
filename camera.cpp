#include "camera.h"
#include "cg_cam_extras.h"


Camera::Camera(GLfloat fov, GLfloat distance, ofVec3f position){
    camMode = 1;
    this -> fov = fov;
    this -> distance = distance;
    this -> position = position;
    alpha = 10;
    beta = 1000;
    font.load("font_stats.ttf", 12);

    distance = gw()*0.5*tan((fov*0.5)*(PI / 180));
}


void Camera::update(){}

void Camera::apply(ofVec3f marioPos, ofVec3f marioLookAt){

    switch(camMode){
        case(0) : applyp3(marioPos, marioLookAt);
            break;
        case(1) : applyp2(marioPos);
            break;
        case(2) : applyp1(marioPos);
            break;
    }
}

void Camera::applyp1(ofVec3f marioPos){

    camFlag = false;
    perspective(fov, alpha, beta);
    lookat(
        0, marioPos.y + 50, marioPos.z + distance*1.2,
        0, marioPos.y, marioPos.z,
        0, 1, 0
    );
}

void Camera::applyp2(ofVec3f marioPos){

    camFlag = false;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-gw()/8, gw()/8, -gh()/8, gh()/8, 10, 10000);
    lookat(
        0, marioPos.y, distance,
        0, marioPos.y, marioPos.z,
        0, 1, 0        
    );
}

void Camera::applyp3(ofVec3f marioPos, ofVec3f marioLookAt){
    camFlag = true;
    perspective(fov, alpha*100, beta*100);
    lookat(
        marioPos.x, marioPos.y + 5 , marioPos.z,
        marioLookAt.x, marioLookAt.y, marioLookAt.z,
        0, 1, 0
    );
}

void Camera::miniMap(ofVec3f marioPos){
    glViewport(gw()-gw()/5, gh()-gw()/5, gw()/4, gh()/4);;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-gw()/8, gw()/8, -gh()/8, gh()/8, 10, 10000);
    lookat(
        0, marioPos.y, distance,
        0, marioPos.y, marioPos.z,
        0, 1, 0        
    );
}

void Camera::draw_objective(){
    objText = " Avoid the barrels and save Pauline from Donkey Kong! \n Activate stats with 'H' and keybinds with 'F' \n hide this window with 'G'";

    float textWidth = font.stringWidth(objText);
    float textHeight = font.stringHeight(objText);

    float x = (gw() - textHeight) / 2;
    float y = (gh() - textHeight) / 2;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, gw(), gh(), 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat mat_ambient[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_specular[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    ofSetColor(255, 255, 255); 
    font.drawString(objText, x, y);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Camera::draw_stats(){

    std::string statsText = " Times dead: " + std::to_string(num_lives) + "\n Current height/Pauline height: " + std::to_string(meters) + "/" + std::to_string(2 * (num_platforms * 10) + 20) + " meters \n Hide this window: 'H' \n Current Game Mode: " + std::to_string(gameMode);

    float textWidth = font.stringWidth(statsText);
    float textHeight = font.stringHeight(statsText);

    float x = (gw() - textHeight) / 2 ;
    float y = (gh() - textHeight) / 2;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, gw(), gh(), 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat mat_ambient[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_specular[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    ofSetColor(255, 255, 255); 
    font.drawString(statsText, x, y);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Camera::draw_keys(){
    std::string keys_text = " Change camera mode: 'T' \n Move in third person: 'leftArrow', 'rightArrow', 'upArrow', 'downArrow' \n Move in first person: 'leftArrow', 'rightArrow', 'W', 'S' \n Jump: 'space'\n Ambient light on/off: 'z'\n Directional light on/off: 'X' Properties: 'I', 'O' , 'P'\n Point light (Mario) on/off: 'C' Properties: 'J', 'K' , 'L' \n Spot light (donkeyKong) on/off: 'V' Properties: 'B', 'N', 'M' \n NORMAL MODE: '1'\n HARD MODE: '2'\n Hide this window: 'F' ";

    float textWidth = font.stringWidth(keys_text);
    float textHeight = font.stringHeight(keys_text);

    float x = (gw() - textHeight) / 2 ;
    float y = (gh() - textHeight) / 2;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, gw(), gh(), 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat mat_ambient[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_specular[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    ofSetColor(255, 255, 255); 
    font.drawString(keys_text, x, y);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Camera::draw_mode(){
       std::string mode;
    if(camMode == 0){
        mode = "First Person";
    }
    if(camMode == 1){
        mode = "2D third Person";
    }
    if(camMode == 2){
        mode = "3D third Person";
    }

    
    std::string mode_text = "Current Game Mode:" + std::to_string(gameMode)  + "\n Current Camera Mode:" + mode;

    float textWidth = font.stringWidth(mode_text);
    float textHeight = font.stringHeight(mode_text);

    float x = (gw() - textHeight) / 2 ;
    float y = (gh() - textHeight) / 2;

    glMatrixMode(GL_PROJECTION);    
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, gw(), gh(), 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat mat_ambient[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_specular[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    ofSetColor(255, 255, 255); 
    font.drawString(mode_text, x, y);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

