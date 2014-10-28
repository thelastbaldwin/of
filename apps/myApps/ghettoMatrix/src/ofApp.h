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
        std::string takeTraditionalPhoto(const string& fileName);
        std::string takeMatrixPhoto(const string& fileName);

        std::vector<int> getCameraIds(std::string idString);

        void exit();

        ofxGifEncoder gifEncoder;
        void onGifSaved(string & fileName);

        static const int SEND_PORT;
        static const int RECEIVE_PORT;
        static const std::string HOST;
        static const std::string OUTPUT_PATH;
        static const int NUM_MATRIX_FRAMES;

        ofImage qrcode;

        ofDirectory dir;
		vector<ofImage> animals;
		int currentAnimal;

		ofShader shader;
		ofFbo fbo;

        ofxOscReceiver receiver;
        ofxOscSender sender;

        CamThread* hMainCameraThread;
        CamThread* hCamThread1;
        CamThread* hCamThread2;

        ofSoundPlayer beep;
        ofSoundPlayer yeah;

		ofXml settings;
};
