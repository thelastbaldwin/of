#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

    //needs to be 16:9
    //final at 1920 x 1080
	ofSetupOpenGL(1080,1920, OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
