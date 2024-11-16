#pragma once

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"
#include "cg_cam_extras.h"
#include "escadas.h"
#include "plataforma.h"
#include "mario.h"
#include <vector>

class ofApp : public ofBaseApp{

	public:
		ofApp();
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
		void perspective1();
		void perspective2();

		// Perspective variables
        GLfloat LensAngle;
        GLfloat alpha;
        GLfloat beta;
        GLfloat lensAngle;

		//floor
		GLint resX = 9, resY = 9;
		GLfloat floorWidth = gw() * 0.5, floorHeight = gw() * 0.5, floorHeightPos = 0.;
		GLfloat levelWidth, levelHeight, levelDepth;

		//view
		GLint view;

		//mario
		GLfloat marioSize = 0.25;
		GLfloat marioHeight, marioWidth, marioDepth, marioPosHeight, marioPosWidth;
		Mario marioInstance;

		//platform vector
		std::vector<Platform> platforms;	

		//ladder vector
		std::vector<Ladder> ladders;	
		GLfloat ladderWidth, ladderHeight, ladderDepth, ladderPosWidth;

		//mario pos
		std::vector<float> marioPos;
		GLfloat thresholdDistance = 5.0f;


		bool wasOnLadder = false;  // Track if Mario is climbing
		int MarioLevel = 0; 

};

