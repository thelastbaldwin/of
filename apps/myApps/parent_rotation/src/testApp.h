#pragma once

#include "ofMain.h"

#define kNumTestNodes 4

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		ofNode testNodes[kNumTestNodes];
		ofCamera cam;
		ofLight pointLight;
		
		//taken from orientationExample 
		deque<ofVec3f> pathVertices[kNumTestNodes]; //wtf is a deque? some kind of collection/vector
		ofMesh pathLines[kNumTestNodes];	
		ofVec3f previous[kNumTestNodes];
		ofVec3f current[kNumTestNodes];
};
