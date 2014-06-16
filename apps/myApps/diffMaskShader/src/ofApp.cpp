#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    shader.load("shaders/shaderVert.c", "shaders/shaderFrag.c");
    
    //images
    waves.loadImage("waves.png");
    face.loadImage("face.png");
    
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
    
    if(waves.getWidth() != ofGetWidth()){
        waves.resize(ofGetWidth(), ofGetHeight());
         face.resize(ofGetWidth(), ofGetHeight());
    }
    
    //change this if you need to use primary camera
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);

	ofSetVerticalSync(true);
    
    grayImage.allocate(camWidth, camHeight);
    cameraImage.allocate(camWidth, camHeight);
    bufferFloat.allocate(camWidth, camHeight);
    diffImage.allocate(camWidth, camHeight);
    fbo.allocate(camWidth, camHeight);
    diffTex.allocate(camWidth, camHeight, GL_RGB);
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    
    if(vidGrabber.isFrameNew()){
        if(grayImage.bAllocated){
            grayImagePrev = grayImage;
        }
        
        cameraImage.setFromPixels(vidGrabber.getPixelsRef());
        grayImage = cameraImage;
        
        if(grayImage.bAllocated){
            diff.absDiff(grayImage, grayImagePrev);
            
            diffFloat = diff; //convert diffImage to float image
            diffFloat *= 5.0; //amplify
            
            if(!bufferFloat.bAllocated){
                //If the buffer is not initialized, then just set it equal to diffFloat
                bufferFloat = diffFloat;
            }else{
                bufferFloat *= 0.85; //dat magic number
                bufferFloat += diffFloat;
            }
        }
        diffImage = bufferFloat;
        diffTex.loadData(diffImage.getPixels(), ofGetWidth(), ofGetHeight(), GL_RGB);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    shader.begin();
    waves.getTextureReference().bind();
    diffTex.bind();

    shader.setUniformTexture("mask", diffTex, 0);
    shader.setUniformTexture("top", waves.getTextureReference(), 1);

    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();

    ofScale(-1.0, 1.0);
    ofTranslate(-ofGetWidth(), 0);
    
    waves.draw(0, 0);
    face.draw(0, 0);
    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
