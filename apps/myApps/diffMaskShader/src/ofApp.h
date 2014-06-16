#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include <iostream>

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
    
        ofVideoGrabber 		vidGrabber;
        int 				camWidth;
        int 				camHeight;
    
        //    openCV classes
        ofxCvColorImage cameraImage, diffImage;
        ofxCvGrayscaleImage grayImage, grayImagePrev, diff;
        ofxCvFloatImage diffFloat, bufferFloat;
    
        ofShader shader;
        ofFbo fbo;
        ofImage waves, face;
    
        ofTexture diffTex;
    
};
