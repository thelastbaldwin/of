#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofShader shader, wiggleShader;
    
        ofVideoGrabber vidGrabber;
        ofMesh mesh, quad;
        ofCamera cam;
        ofLight light;
    
        ofxPanel gui;
        ofxFloatSlider squareSize;
        ofxFloatSlider wavelength;
        ofxFloatSlider amplitude;
        ofxFloatSlider speed;
        ofxFloatSlider cameraX;
        ofxFloatSlider cameraY;
        ofxFloatSlider cameraZ;
        bool bHide;
    
        ofFbo fbo;
};
