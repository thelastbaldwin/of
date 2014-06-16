#include "ofMain.h"
#include "ofApp.h"
// import the fancy new renderer
//#include "ofGLProgrammableRenderer.h"

//========================================================================
int main( ){

    //may not be necessary
    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(1900,1080, OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
