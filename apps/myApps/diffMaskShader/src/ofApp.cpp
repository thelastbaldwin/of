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
    
    //gui stuff
    gui.setup();
    gui.add(opacity.setup("opacity", 0.80, 0.0, 0.95));
    gui.add(amplitude.setup("amplitude", 8.0, 0.0, 50.0));
    bHide = false;
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
            diffFloat *= amplitude; //amplify
            
            if(!bufferFloat.bAllocated){
                //If the buffer is not initialized, then just set it equal to diffFloat
                bufferFloat = diffFloat;
            }else{
                bufferFloat *= opacity; //dat magic number
                bufferFloat += diffFloat;
            }
        }
        diffImage = bufferFloat;
        diffTex.loadData(diffImage.getPixels(), ofGetWidth(), ofGetHeight(), GL_RGB);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofHideCursor();
    fbo.begin();
    shader.begin();
    waves.getTextureReference().bind();
    diffTex.bind();

    shader.setUniformTexture("mask", diffTex, 0);
    shader.setUniformTexture("top", waves.getTextureReference(), 1);

    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();

    ofPushMatrix();
    ofScale(-1.0, 1.0);
    ofTranslate(-ofGetWidth(), 0);
    
    waves.draw(0, 0);
    face.draw(0, 0);
    fbo.draw(0, 0);
    ofPopMatrix();
    
    if(bHide){
        ofShowCursor();
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'h' ){
		bHide = !bHide;
	}
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
