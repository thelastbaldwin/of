#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    using namespace std;
    
    camWidth 		= 1024;	// try to grab at this size.
	camHeight 		= 768;
	
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
    
	vidGrabber.setDeviceID(1);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoTexture.allocate(camWidth,camHeight, GL_RGB);
	ofSetVerticalSync(true);
    
    grayImage.allocate(camWidth, camHeight);
    
    cameraImage.allocate(camWidth, camHeight);
    bufferFloat.allocate(camWidth, camHeight);

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
            diffFloat *= 1.0; //amplify
            
            if(!bufferFloat.bAllocated){
                //If the buffer is not initialized, then just set it equal to diffFloat
                bufferFloat = diffFloat;
            }else{
                bufferFloat *= 0.85; //dat magic number
                bufferFloat += diffFloat;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    
    bufferFloat.draw(0, 0, camWidth, camHeight);
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
