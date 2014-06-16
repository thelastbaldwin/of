#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"
#include "particle.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context
	//ofSetFullscreen(true);  //for final presentation

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());
}
