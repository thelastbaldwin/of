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
		
		ofVideoGrabber 			vidGrabber;
		ofPtr<ofQTKitGrabber>	vidRecorder;
    
    	ofVideoPlayer recordedVideoPlayback;
    
		void videoSaved(ofVideoSavedEventArgs& e);
	
    	vector<string> videoDevices;
	    vector<string> audioDevices;

        ofImage scanlineImage;
        void generateScanlineImage(ofImage& img, int scanLineHeight, float opacity);

        //distortion settings;
        float scrollSpeed;
        float wavelength;
        float amplitude;
        float speed;
        float opacity;
        unsigned int scanlineHeight;
    
        ofFbo fbo;
        ofMesh quad;
        ofShader shader;
    
        ofArduino	arduino;
        bool		bSetupArduino;			// flag variable for setting up arduino once
        void setupArduino(const int & version);
        void digitalPinChanged(const int & pinNum);
        void analogPinChanged(const int & pinNum);
        void updateArduino();
    
        bool bButtonState;
        float potValue;

};
