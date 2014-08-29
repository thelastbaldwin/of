#pragma once

#include "ofMain.h"

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
    
        ofImage getSortedImage(ofImage& source);
        void remapColors(const ofImage& source, ofImage& destination);
        std::vector<ofColor> sortPixels(const ofImage& source);
    
        ofImage forest,
                ocean;
		
};

 bool compareColors(const ofColor&  a, const ofColor& b);


