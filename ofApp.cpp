#include "ofApp.h"


ofApp::ofApp() : marioInstance(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0) {
} //default constructor for marioInstance so it can use its functions
//--------------------------------------------------------------
void ofApp::setup(){
    glEnable(GL_DEPTH_TEST);
	ofBackground(0.05, 0.05, 0.05);

	

	view = 0;


    ofSetFrameRate(60);

	//mostra o estado inicial das matrizes
	coutModelviewMatrix();
	coutProjectionMatrix();
	
	glPointSize(200);
	glLineWidth(3);

	levelWidth = floorWidth;
    levelHeight = floorHeight / GLfloat(resY);
    levelDepth = floorHeight / GLfloat(resY);


	marioPosHeight = levelHeight;
	marioPosWidth = (floorWidth/2 + (marioWidth* marioSize));
	marioWidth = floorWidth/ (GLfloat(resX)*2);
	marioDepth = floorHeight / (GLfloat(resY)*2); 
	marioHeight = floorHeight / (GLfloat(resY)*2);

	ladderWidth = levelWidth / GLfloat(resY);
	ladderHeight = levelHeight;
	ladderDepth = levelHeight / GLfloat(resY);
	ladderPosWidth = (floorWidth/2 + (marioWidth* marioSize));

	marioInstance = Mario(marioSize, marioWidth, marioHeight, marioPosHeight, marioDepth, 3, resY, marioPosWidth);

	LensAngle = 30;
	alpha = 10;
	beta = 1000;
	platforms.clear();
	ladders.clear();
	int index = resY/2;
    for (int i = -(resY / 2); i <= (resY / 2); i += 2) {
        Platform p(levelWidth, levelHeight, levelDepth, i, resY);
		Ladder l(levelWidth, levelHeight, levelDepth, i, resY, ladderPosWidth);
        p.setIndex(index);
		l.setIndex(index); 
        platforms.push_back(p);
		ladders.push_back(l);
        index--;
    }



	

}

//--------------------------------------------------------------
void ofApp::update(){
    bool isOnLadder = false; // Assume Mario is not on a ladder

    marioPos = marioInstance.getMarioPosition();
	int index = 0;

    // Collision detection threshold for proximity
    float thresholdX = (marioWidth * marioSize) + (ladderWidth * 0.5);
    float thresholdY = (marioHeight * marioSize) + (ladderHeight * 0.5);
    float thresholdZ = (marioDepth * marioSize) + (ladderDepth * 0.5);

    for (auto& ladder : ladders) {
        float ladderPosX = ladder.escadasx;
        float ladderPosY = ladder.escadasy;
        float ladderPosZ = ladder.adjustedescadasz;

        bool xCollision = std::abs(marioPos[0] - ladderPosX) < thresholdX;
        bool yCollision = std::abs(marioPos[1] - ladderPosY) < (2* thresholdY)+ 3*(marioHeight * marioSize);
		//bool yCollision = marioPos[1] >= ladderPosY && marioPos[1] <= (ladderPosY + ladderHeight);
        bool zCollision = std::abs(marioPos[2] - ladderPosZ) < thresholdZ;

		cout << "Mario: " << marioPos[0] << " " << marioPos[1] << " " << marioPos[2] << endl;
		cout << "Ladder: " << index << ladderPosX << " " << ladderPosY << " " << ladderPosZ << endl;
		cout << "Threshold: " << thresholdX << " " << thresholdY << " " << thresholdZ << endl;

		index++;
        if (xCollision && yCollision && zCollision) {
			cout << "Mario is on ladder" << endl;
            isOnLadder = true;
            break;
        }
    }

 	bool stillOnLadder = marioInstance.climbLadder(isOnLadder);
	if(!stillOnLadder){
    marioInstance.moveLeft();
    marioInstance.moveRight();
    marioInstance.moveBack(isOnLadder);
    marioInstance.jump();	
    marioInstance.jumpKey(isOnLadder);
    marioInstance.moveFront(isOnLadder);
	}
}
void ofApp::perspective1(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0 , gw(), gh(), 0, 5*gw(), -5*gw());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	lookat(0,0,1,0,0,0,0,1,0);
}

void ofApp::perspective2(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspective(LensAngle, alpha, beta);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	lookat(
		gw()*0.5, -gw()/5, -gw(),
		gw()*0.5, gh()*0.44, 0, 
		0, -1, 0
		);
}
/*
void ofApp::plataformas(){//talvez fazer modular, com o argumento a ser o numero de plat que quero
	int index=4;
	for (int i = -(resY / 2); i <= (resY / 2); i += 2) {
		glTranslatef(0, 0, 0);
		Platform p(levelWidth, levelHeight, levelDepth, i, resY);
		p.draw(index);
		p.ladders(index);
        index--;
	}

}

*/

//--------------------------------------------------------------
void ofApp::draw(){ 
	glPushMatrix();// perspective push
	switch (view) {
	case 0:
		perspective1();
		break;
	case 1:
		perspective2();
		break;
	}
    glPushMatrix();//floor push
    glTranslatef(gw() * 0.5, gh() * 0.5, 0);
    glScalef(floorWidth, floorHeight, 1.);
	//malha_unit(resX, resY);
	glPopMatrix();//floor pop
	glPushMatrix();// level push

	//plataformas();
    for (auto& platform : platforms) {
        platform.draw(platform.getIndex());
		}  // Pass the index if needed
	for (auto& ladder : ladders) {
		if (ladder.getIndex() != 4) {
        ladder.draw(ladder.getIndex());
		}
    }
	glPopMatrix();// level pop
	glPushMatrix();// mario push

	marioInstance.draw();
	//mario();
	glPopMatrix();// mario pop
	glPopMatrix();// perspective pop
}
//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case '1':
		glDisable(GL_CULL_FACE);
		break;
	case '2':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		break;
	case '3':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		break;
	case '4':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT_AND_BACK);
		break;
	case 'g':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
		//tank
    case 't':
		view = (view+1) %2;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    setup();

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
