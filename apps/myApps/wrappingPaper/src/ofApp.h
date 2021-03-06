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
		
    
        ofMesh quad;
        ofFbo fbo;
        ofShader textureShader;
        const int columns = 4, rows = 4;
    
        float time, padding;
    
        struct TrippyQuad{
            float rotOffset, amplitude, speed;
            TrippyQuad();
            TrippyQuad(float _rotOffset, float _amplitude, float _speed);
        };
    
        //columns * rows
        TrippyQuad trippyQuads[16];
        float quadWidth, quadHeight;
    
};
