#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
//    this interferes with openCV in some way, will need to drop down to #version 120 shaders
//    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1920, 1080, OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
