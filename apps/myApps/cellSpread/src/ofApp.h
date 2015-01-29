#pragma once

#include "ofMain.h"
#include "CellGrid.h"
#include "ofxSyphon.h"
#include "ofxOsc.h"


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
    
        ofImage tile;
        Virus::CellGrid cellGrid;
    
        //syphon stuff
        ofxSyphonServer mainOutputSyphonServer;
        ofxSyphonServer individualTextureSyphonServer;
    
        ofFbo fbo;
    
        //for sending out heartbeat
        ofxOscSender sender;
    
        //heartbeat params
        const static int SEND_PORT;
        const static std::string HOST;
    
        //how often to send a heartbeat
        const static float heartBeatInterval;
        float lastInterval;
};
