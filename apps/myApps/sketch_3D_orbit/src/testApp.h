#pragma once

#include "ofMain.h"

#define kNumLights 2

class Ring{
public:
    Ring();
    Ring(int _count, int _radius, int _speed, int _size, float xRot, float yRot, float zRot);
    
    //methods
    void setRotation(float x, float y, float z);
    void update();
    void display();
    
    //attributes
    static float counter;
    int count;
    int radius;
    int size;
    float speed;
    int originX; //may be able to replace this with an ofPoint or similar
    int originY;
    int originZ;
    float rotation[3];
};

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofCamera cam; // add mouse controls for camera movement
        ofLight light[kNumLights];
        Ring tRing; //test Ring
        Ring layers[5]; //set of test rings
    
        ofMaterial mat; 
        
        void drawAxes();

		
};


