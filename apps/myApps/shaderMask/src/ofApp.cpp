#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){        
    shader.load("shaders/shaderVert.c","shaders/shaderFrag.c");
    
  
//    images
    forest.loadImage("forest.jpg");
    desert.loadImage("desert.jpg");
    
    camWidth 		= ofGetWidth();	// try to grab at this size.
	camHeight 		= ofGetHeight();
    
    forest.resize(ofGetWidth(), ofGetHeight());
    desert.resize(ofGetWidth(), ofGetHeight());
	
    //we can now get back a list of devices.
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}
    
    //if there are multiple cameras on the device,
    //this will need to be changed to the appropriate one
    vidGrabber.setDeviceID(1);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);

    //GL_LUMINANCE is an openGL constant. only store grayscale 
    videoTexture.allocate(camWidth,camHeight, GL_LUMINANCE);
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    shader.begin();
    
    desert.getTextureReference().bind();
    forest.getTextureReference().bind();
    
    shader.setUniformTexture("mask", vidGrabber.getTextureReference(), 0); //GL_LUMINANCE?
    shader.setUniformTexture("top", desert.getTextureReference(), 1);
	shader.setUniformTexture("bottom", forest.getTextureReference(), 2);

    
    //need to pass in some vertex data to the shader
    ofRect(0, 0, ofGetWidth(), ofGetHeight());

	shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}