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
        void generateScanlineImage(ofImage& img, int scanLineHeight, float opacity = 0.3);
    
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
        ofxToggle doFade;
        ofxFloatSlider opacity;
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
                opacity;
            int scanlineHeight;
        };
    
        Settings defaultSettings;
        Settings wigoutSettings;
};
