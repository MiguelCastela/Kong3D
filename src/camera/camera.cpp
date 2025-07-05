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
    objText = " Pauline is in danger! Avoid the barrels and save her from Donkey Kong \n Press 'H' for game stats and 'F' for keybinds \n hide this window with 'G'";
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 1, 1);
    float textWidth = font.stringWidth(objText);
    float textHeight = font.stringHeight(objText);

    float x = (gw() - textHeight) / 2 - textWidth / 5;
    float y = gh() - textHeight - 10;

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

    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    font.drawString(objText, x, y);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
}

void Camera::draw_stats(){
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 1, 1);

    std::string statsText = " Total deaths: " + std::to_string(total_lifes) + "\n Current height/Pauline height: " + std::to_string(meters) + "/" + std::to_string(2 * (num_platforms * 10) + 20) + " meters \n number of platforms:" + std::to_string(num_platforms) +" \n Hide this window: 'H'";

    float textWidth = font.stringWidth(statsText);
    float textHeight = font.stringHeight(statsText);

    float x = (gw() - textHeight) / 2 - textWidth / 5;;
    float y = gh() - textHeight - 10;

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

    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    font.drawString(statsText, x, y);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
}

void Camera::draw_keys(){
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 1, 1);
    std::string keys_text = " Change camera mode: 'T' \n EASY MODE: '1'\n MEDIUM MODE: '2'\n HARD/NIGHT MODE: '3' \n SANDBOX MODE: '4' \n Move in third person: 'leftArrow', 'rightArrow', 'upArrow', 'downArrow' \n Move in first person: 'leftArrow', 'rightArrow', 'W', 'S' \n Jump: 'space'\n Ambient light on/off (SANDBOX ONLY): 'z'\n (SANDBOX ONLY) Directional light on/off: 'X' Properties: 'I', 'O' , 'P'\n (SANDBOX ONLY) Point light (Mario) on/off: 'C' Properties: 'J', 'K' , 'L' \n (SANDBOX ONLY) Spot light (donkeyKong) on/off: 'V' Properties: 'B', 'N', 'M' \n Quit game: 'Esc' \n Hide this window: 'F' ";

    float textWidth = font.stringWidth(keys_text);
    float textHeight = font.stringHeight(keys_text);

    float x = (gw() - textHeight) / 2  - 200;
    float y = gh() - textHeight - 10;

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

    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    font.drawString(keys_text, x, y);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
}

void Camera::draw_mode(){
    // Enable color material and set texto to red
    // wnable glcolormateiral
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0, 1.0, 1.0);

       std::string mode;
       std::string mode1;
    if(camMode == 0){
        mode = "First Person";
    }
    if(camMode == 1){
        mode = "2D third Person";
    }
    if(camMode == 2){
        mode = "3D third Person";
    }

    if(gameMode == 1){
        mode1 = "HARD/NIGHT MODE";
    }
    if(gameMode == 2){
        mode1 = "EASY MODE";
    }
    if(gameMode == 3){
        mode1 = "SANDBOX MODE";
    }
    if(gameMode == 4){
        mode1 = "MEDIUM MODE";
    }

    
    std::string mode_text = " Current Game Mode:" + mode1 + "\n Current Camera Mode:" + mode;

    float textWidth = font.stringWidth(mode_text);
    float textHeight = font.stringHeight(mode_text);

    float x = (gw() - textHeight) / 2 - textWidth / 5; ;
    float y = (gh() - textHeight) / 2 - 10;

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

    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    font.drawString(mode_text, x, y);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // Disable color material
    glDisable(GL_COLOR_MATERIAL);
}

void Camera::draw_winning_message() {
    glEnable(GL_COLOR_MATERIAL);

    // Part 1: "Times dead: " + num_lives
    glColor3f(1, 0, 0); // Red color
    std::string part1 = "Deaths: " + std::to_string(num_lives);

    // Part 2: meters (green)
    std::string part2 = std::to_string(meters);

    // Part 3: "/" + (platform height) + " m"
    std::string part3 = "/" + std::to_string(2 * (num_platforms * 10) + 20) + " m";

    // Calculate positions
    float x = 10;
    float y = gh() - font.stringHeight(part1 + part2 + part3) - 30; // Start higher on the screen

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, gw(), gh(), 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);

    // Render Part 1
    glColor3f(1, 0, 0); // Red for part 1
    font.drawString(part1, x, y); // Draw part 1
    y += font.stringHeight(part1) + 10; // Move y down for the next line

    // Render Part 2 and Part 3 on the same line
    glColor3f(0, 1, 0); // Green for part 2
    font.drawString(part2, x, y); // Draw part 2
    x += font.stringWidth(part2); // Move x to the end of part 2

    glColor3f(1, 0, 0); // Red for part 3
    font.drawString(part3, x, y); // Draw part 3

    // Restore OpenGL states
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
}

void Camera::draw_fps() {
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 1, 1); // White color

    // Get the real FPS
    std::string fpsText = std::to_string((int)ofGetFrameRate()) + " FPS";

    // Calculate position for top-right corner
    float textWidth = font.stringWidth(fpsText);
    float x = gw() - textWidth - 10; // 10 pixels from the right edge
    float y = font.stringHeight(fpsText) + 10; // 10 pixels from the top edge

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, gw(), gh(), 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);

    // Render the FPS text
    font.drawString(fpsText, x, y);

    // Restore OpenGL states
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
}

void Camera::draw_victory_message() {
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0, 1, 0); // Green color

    // Save current font size
    int originalSize = font.getSize();

    // Set a bigger font size (e.g., 48)
    font.load("font_stats.ttf", 48);

    std::string victory = "YOU WON";

    float textWidth = font.stringWidth(victory);
    float textHeight = font.stringHeight(victory);
    float x = (gw() - textWidth) /2;
    float y = (gh() + textHeight) / 2  - 150;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, gw(), gh(), 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);

    font.drawString(victory, x, y);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);

    // Restore original font size
    font.load("font_stats.ttf", originalSize);
}




