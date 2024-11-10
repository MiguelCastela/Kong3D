#include "ofApp.h"

ofApp::ofApp() : marioInstance(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0) {
} //default constructor for marioInstance so he can move 
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

	marioInstance = Mario(0.25, marioWidth, marioHeight, marioPosHeight, marioDepth, 3, resY);

	LensAngle = 30;
	alpha = 10;
	beta = 1000;
	

}

//--------------------------------------------------------------
void ofApp::update(){
	marioInstance.moveLeft();
	marioInstance.moveRight();
	marioInstance.moveFront();
	marioInstance.moveBack();

}
void ofApp::perspective1(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0 , gw(), gh(), 0, -gh(), gh());
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
	lookat(gw()*0.5, -400, 1500, gw()*0.5, gh()*0.44, 0, 0, -1, 0);
	
	
}
void ofApp::plataformas(){//talvez fazer modular, com o argumento a ser o numero de plat que quero
	for (int i = -(resY / 2); i <= (resY / 2); i += 2) {
		Platform p(levelWidth, levelHeight, levelDepth, i, resY);
		p.draw();
	}

}



//--------------------------------------------------------------
void ofApp::draw(){

 
	glPushMatrix();// perspective push
	switch (view) {
	case 0:
		perspective1();
		marioInstance.setPerspective(1);
		break;
	case 1:
		perspective2();
		marioInstance.setPerspective(2);
		break;
	}
    glColor3f(1, 1, 1);
    glPushMatrix();//floor push
    glTranslatef(gw() * 0.5, gh() * 0.5, 0);
    glScalef(floorWidth, floorHeight, 1.);
	malha_unit(resX, resY);
	glPopMatrix();//floor pop
	glPushMatrix();// level push
	levelWidth = floorWidth;
    levelHeight = floorHeight / GLfloat(resY);
    levelDepth = floorHeight / GLfloat(resY);
	plataformas();
	glPopMatrix();// level pop
	glPushMatrix();// mario push
	marioPosHeight = floorHeight / GLfloat(resY);
	marioWidth = floorWidth/ (GLfloat(resX)*2);
	marioDepth = floorHeight / (GLfloat(resY)*2);
	marioHeight = floorHeight / (GLfloat(resY)*2);
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
	case OF_KEY_RIGHT:
		marioInstance.moveRight();
		break;
	case OF_KEY_LEFT:
		marioInstance.moveLeft();
		break;
	case OF_KEY_UP:
		marioInstance.moveFront();
		break;
	case OF_KEY_DOWN:
		marioInstance.moveBack();
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
