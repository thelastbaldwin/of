#pragma once

#include "ofMain.h"
#include "particle.h"
#include "ofxJSONElement.h"

#define NUM_BYTES 6

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		int count;
		int total;
		int layer;
        int radius;
        int wishindex;
        bool incremented;
        ofSerial serial;
        int serialVal;
        bool readSerialMessage;
        int countCycles;
        string message;
        string message2;
        float Force;
        float scorePercent;
    
        ofArduino	ard;
        bool		bSetupArduino;			// flag variable for setting up arduino once
        const static int PARTICLE_COUNT = 555;
        Particle particles[PARTICLE_COUNT];
    
        ofImage bg;
        ofPoint ORIGIN;
        
        bool blowingAway;
        bool comingBack;
        unsigned int recordCount;
        
        ofTrueTypeFont futuraMedium;
        ofxJSONElement result; //result from the database

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void incrementWishList();
        void decrementWishList();

        
    
private:
    
    void setupArduino(const int & version);
    void analogPinChanged(const int & pinNum);
	void updateArduino();
};
