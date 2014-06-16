#pragma once

#include "ofMain.h"

struct colorTriad{
    ofColor low;
    ofColor mid;
    ofColor high;
    
    colorTriad(){};
    
    colorTriad(const ofColor& first, const ofColor& second, const ofColor& third):
        low(first),
        mid(second),
        high(third){};
};

void polarizeColor(ofColor& original, const colorTriad& triad);

class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
		ofVideoGrabber vidGrabber;
    
        //where the converted pixels are stored
		unsigned char * 	framePixels;
    
        //the number of hue shift variants to create
        const static int NUM_COLORS = 6;
    
        const static int NUM_DOWN = 16;
        const static int NUM_ACCROSS = 9;
    
        //turn this into an array of the number of variants
        ofTexture videoTexture[ofApp::NUM_COLORS];
        colorTriad colorTriads[ofApp::NUM_COLORS];
		
        int camWidth;
        int camHeight;
        int borderSize;
};
