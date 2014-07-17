#pragma once

#include <algorithm>
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGifEncoder.h"
#include "camThread.h"
//#include "ofxXmlSettings.h"

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
        void sendMessage(std::string filename, std::string id);
    
        void onGifSaved(string & fileName);
        void exit();
    
        static const int SEND_PORT;
        static const int RECEIVE_PORT;
        static const std::string HOST;
    
        ofxOscReceiver receiver;
        ofxOscSender sender;
    
        ofVideoGrabber 		vidGrabber;
        ofxGifEncoder gifEncoder;
//        ofxXmlSettings XML;
    
        CamThread* hMainCameraThread;
		
};
