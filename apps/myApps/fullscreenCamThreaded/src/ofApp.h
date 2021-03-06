// use this as a test to calibrate the camera positions

#pragma once

#include "ofMain.h"
#include <algorithm>
#include "camThread.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void changeId(int id);
        void displayFramerate();
        ofTexture camTex;
        CamThread camThread;
        int camIndex;
};
