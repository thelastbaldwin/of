#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
        ofTexture text;
        ofLight light1, light2;
    
		void setup();
		void update();
		void draw();
		
};
