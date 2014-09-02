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
    
        void remapColors(const ofPixels& source, ofPixels& destination);
        std::vector<ofColor> sortPixels(const ofPixels& source);
    
        ofImage forest,
                ocean,
                colorMap;
		
        ofVideoGrabber vidGrabber;
    
        ofShader shader;
        ofMesh quad;
    
        const static int COLOR_COUNT = 255;
        ofFloatColor destinationColors[COLOR_COUNT];
};


