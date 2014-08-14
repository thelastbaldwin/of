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
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxPanel gui;
    
    //Sphere and controls
    ofSpherePrimitive sphere;
    ofxFloatSlider radius;
    ofxIntSlider sphereResolution;
    ofxVec3Slider  sphereCenter;
    
    //Light and controls
    ofLight pointLight;
    ofxVec3Slider lightPosition;
    ofxColorSlider diffuseLightColor;
    ofxColorSlider specularLightColor;
    
    //Material and controls
    ofMaterial material;
    ofxColorSlider diffuseMaterialColor;
    ofxColorSlider specularMaterialColor;
    ofxFloatSlider shininess;
    
    bool hideGui;
    
    ofFbo fbo;
    
};
