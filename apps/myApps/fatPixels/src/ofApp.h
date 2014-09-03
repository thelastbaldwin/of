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
        void generateScanlineImage(ofImage& img, int scanLineHeight, float opacity = 0.2);
        void reset();
        void shuffleSettings();
    
        //this needs to be a template class becuase of the ofxFloatSlider class
        template<typename T> void adjustOpacity(T& opacity);
    
        ofShader shader, wiggleShader;
    
        ofVideoGrabber vidGrabber;
        ofMesh mesh, quad;
        ofCamera cam;
        ofLight light;
        ofImage scanlineImage;
    
        ofxPanel gui;
        ofxFloatSlider squareSize;
        ofxFloatSlider wavelength;
        ofxFloatSlider amplitude;
        ofxIntSlider scanlineHeight;
        int prevScanlineHeight;
        ofxFloatSlider speed;
        ofxFloatSlider cameraX;
        ofxFloatSlider cameraY;
        ofxFloatSlider cameraZ;
        ofxFloatSlider scrollSpeed;
        ofxToggle doFade;
        ofxToggle bWigout;
        ofxToggle bDistortVideo;
        ofxFloatSlider opacity;
        ofxColorSlider overlayColor;
        bool bHide;
        //if true, fade up
        bool bFade;
    
        ofFbo fbo;
    
        ofVideoPlayer videoPlayer;
    
        struct Settings{
          float squareSize,
                wavelength,
                amplitude,
                speed,
                cameraX,
                cameraY,
                cameraZ,
                opacity,
                scrollSpeed;
            int scanlineHeight;
        };
    
        Settings defaultSettings;
    
        //wigout interval variables
        float targetTime,
            stableInterval, //want an amount between 20 and 30 seconds
            time;

        //initialization of static floats in the header file is
        //apparently no bueno http://stackoverflow.com/questions/2454019/why-arent-static-const-floats-allowed
        const static float WIGOUT_INTERVAL;
        bool doWigout;
    
};
