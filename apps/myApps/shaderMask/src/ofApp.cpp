#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){        
    shader.load("shaders/shaderVert.c","shaders/shaderFrag.c");
    
//    textures
    ofLoadImage(mask, "mask.jpg");
    ofLoadImage(forest, "forest.jpg");
    ofLoadImage(desert, "desert.jpg");
    
//    images
//    mask.loadImage("mask.jpg");
//    forest.loadImage("forest.jpg");
//    desert.loadImage("desert.jpg");
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
    camWidth 		= ofGetWidth();	// try to grab at this size.
	camHeight 		= ofGetHeight();
	
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
    
    vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);
    
    videoTexture.allocate(camWidth,camHeight, GL_RGB);
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vidGrabber.update();
    //set mask texture to video
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    shader.begin();
    
//    shader.setUniformTexture("mask", mask, 0);
    shader.setUniformTexture("mask", vidGrabber.getTextureReference(), 0);
    shader.setUniformTexture("top", desert, 1);

    
    //need to pass in some vertex data to the shader
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    shader.end();
    fbo.end();
    forest.draw(0, 0, ofGetWidth(), ofGetHeight());
    fbo.draw(0, 0);
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