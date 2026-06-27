#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	ambientOn = true;
	dirOn = false;
	pointOn = false;
	autoMove = true;

	pointZtheta = 0;
	dirVecTheta = 0.;

	view = 0;

}



//--------------------------------------------------------------
void ofApp::update() {

	if (autoMove) {

		//calculo da posicao da luz pontual
		pointPos[0] = gw() * 0.5 * sin(3 * pointZtheta * PI / 180.0);
		pointPos[1] = gh() * 0.5 * cos(pointZtheta * PI / 180.0);
		pointPos[2] = 200 + 199 * cos(8 * pointZtheta * PI / 180.0);
		pointZtheta += 0.25;

		//calculo da direcao da luz direcional
		float z = gh() * 0.25 * (cos(dirVecTheta * PI / 180.) * 0.5 + 0.45);
		float y = gh() * 0.5;
		float x = 0;
		dirVec3f = ofVec3f(x, y, z) - ofVec3f(0, 0, 0);
		dirVecTheta += 0.5;


	}
	else {
		//luz pontual
		//centro acima
		pointPos[0] = 0;
		pointPos[1] = 0;
		pointPos[2] = 90;
		//centro embaixo
		/*pointPos[0] = 0;
		pointPos[1] = 0;
		pointPos[2] = -90;*/
		//centro malha esquerda
		/*pointPos[0] = -gw()*0.25;
		pointPos[1] = 0;
		pointPos[2] = 90;*/
		//centro edge
		/*pointPos[0] = 0;
		pointPos[1] = -gh()*0.5;
		pointPos[2] = 100;*/


		//luz direcional
		//auto max 
		dirVec3f = ofVec3f(0, gh()*0.5, gh()*0.25*0.95) - ofVec3f(0, 0, 0);
		//auto min
		//dirVec3f = ofVec3f(0, gh()*0.5, 0) - ofVec3f(0, 0, 0);
		//z+
		//dirVec3f = ofVec3f(0, 0, 1);
		//45 graus
		//dirVec3f = ofVec3f(0, 1, 1);
	}




}

//--------------------------------------------------------------
void ofApp::draw() {
	//define viewport
	glViewport(0, 0, gw(), gh());
	//define proje��o
	perspective(60, 100, 100);

	//define camera

	switch (view) {
	case 0:
		lookat(0, 0, gh(), 0, 0, 0, 0, 1, 0);
		break;
	case 1:
		lookat(0, -gh() * 1.25, gh() * 0.75, 0, 0, 0, 0, 0, 1);
		break;
	case 2:
		lookat(gw() * 0.5, -gh() * 1.25, gh() * 0.75, 0, 0, 0, 0, 0, 1);
	}


	//#################################################
	//define luzes
	glEnable(GL_LIGHTING);//habilita o uso de ilumina��o
	glEnable(GL_NORMALIZE);//utiliza versores para normais (normais normalizadas)

	//glDisable(GL_COLOR_MATERIAL);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
	//acho que em Mac tem que usar este também
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//#################################################


	//#################################################
	//fonte de luz que s� tem componente ambiente
	//n�o conta como uma fonte de luz LIGHT0 - LIGHT8
	if (ambientOn) {
		ambientLight[0] = 1.;//R
		ambientLight[1] = 1.;//G
		ambientLight[2] = 1.;//B
		ambientLight[3] = 1;//useless
	}
	else {
		ambientLight[0] = 0.;
		ambientLight[1] = 0.;
		ambientLight[2] = 0.;
		ambientLight[3] = 1;
	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	//#################################################


	//#################################################
	//luz direcional
	dirVec[0] = dirVec3f.x;//x
	dirVec[1] = dirVec3f.y;//y
	dirVec[2] = dirVec3f.z;//z
	dirVec[3] = 0;//vetor - dire��o!

	dirAmb[0] = 0.0;//R
	dirAmb[1] = 0.0;//G
	dirAmb[2] = 0.0;//B
	dirAmb[3] = 1.;//constante

	dirDif[0] = 0.5;//R
	dirDif[1] = 0.5;//G
	dirDif[2] = 0.5;//B
	dirDif[3] = 1.;//constante

	dirSpec[0] = 0.;//R
	dirSpec[1] = 0.;//G
	dirSpec[2] = 0.;//B
	dirSpec[3] = 1.;//constante

	glLightfv(GL_LIGHT0, GL_POSITION, dirVec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, dirAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dirDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, dirSpec);
	if (dirOn) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}
	//#################################################

	//#################################################
	//luz pontual
	//pointPos[0] = 0;//x
	//pointPos[1] = gh()*0.5;//y
	//pointPos[2] = 20;//z
	pointPos[3] = 1;//ponto - posi��o!

	pointAmb[0] = 0.25;//R
	pointAmb[1] = 0.25;//G
	pointAmb[2] = 0.25;//B
	pointAmb[3] = 1.;//constante

	pointDif[0] = 0.75;//R
	pointDif[1] = 0.;//G
	pointDif[2] = 0.;//B
	pointDif[3] = 1.;//constante

	pointSpec[0] = 0.;//R
	pointSpec[1] = 0.;//G
	pointSpec[2] = 0.;//B
	pointSpec[3] = 1.;//constante

	glLightfv(GL_LIGHT1, GL_POSITION, pointPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, pointAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, pointDif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, pointSpec);
	if (pointOn) {
		glEnable(GL_LIGHT1);
	}
	else {
		glDisable(GL_LIGHT1);
	}
	//#################################################

	//#################################################
	//define cores para malha esquerda
	glColor3f(1, 1., 1.);
	

	//desenha malha esquerda
	glPushMatrix();
	glTranslatef(-gw() * 0.25, 0, 0);
	glScalef(gw() * 0.4, gh(), 1);
	malha_unit(25, 25);
	glPopMatrix();
	//#################################################


	//#################################################
	//define cores para malha direita
	glColor3f(1, 1., 1.);

	//desenha malha direita
	glPushMatrix();
	glTranslatef(gw() * 0.25, 0, 0);
	glScalef(gw() * 0.4, gh(), 1);
	malha_unit(1, 1);
	glPopMatrix();
	//#################################################


	//#################################################
	//desenha representa��o das luzes e vetores utilizados
	//sem ilumina��o
	glDisable(GL_LIGHTING);//desabilita ilumina��o
	//representa��o da posi��o da Light1
	if (pointOn) {
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(pointPos[0], pointPos[1], pointPos[2]);
		glScalef(30, 30, 30);
		cube_unit();
		glPopMatrix();
	}

	//representa��o da posi��o da Light0
	if (dirOn) {
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(dirVec3f.x, dirVec3f.y, dirVec3f.z);
		glScalef(30, 30, 30);
		cube_unit();
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(dirVec3f.x, dirVec3f.y, dirVec3f.z);
		glEnd();
		glPopMatrix();
	}
	//#################################################





}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
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
	case 'a':
		ambientOn = !ambientOn;
		break;
	case 'd':
		dirOn = !dirOn;
		break;
	case 'p':
		pointOn = !pointOn;
		break;
	case 'm':
		glShadeModel(GL_FLAT);
		break;
	case 'n':
		glShadeModel(GL_SMOOTH);
		break;
	case 'v':
		view++;
		if (view > 2) {
			view = 0;
		}
		break;
	case 'q':
		autoMove = !autoMove;
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	ofImage aux;
	ofColor rgb;
	aux.grabScreen(x, y, 1, 1);
	rgb = aux.getColor(0, 0);
	cout << endl << float(rgb.r) / 255. << " " << float(rgb.g) / 255. << " " << float(rgb.b) / 255.;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	setup();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
