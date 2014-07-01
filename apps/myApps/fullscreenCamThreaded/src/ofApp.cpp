#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camThread.startThread(true, false);   // blocking, verbose
    camTex.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    camIndex = 0;
    
    
}

void ofApp::displayFramerate(){
    ofSetColor(255, 255, 255);
    std::stringstream ss;
    ss << "FPS: ";
    ss << ofGetFrameRate();
    ofDrawBitmapString(ss.str(), ofGetWidth() - 100, ofGetHeight() - 5);
}

//--------------------------------------------------------------
void ofApp::update(){
    camThread.lock();
    camTex.loadData(camThread.pixels);
    camThread.unlock();
}

//--------------------------------------------------------------
void ofApp::draw(){
    camTex.draw(0, 0);
    ofSetColor(255, 0, 0);
    ofRect(0, ofGetHeight()/2 - 2, ofGetWidth(), 4);
    ofRect(ofGetWidth()/2 - 2, 0, 4, ofGetHeight());
    displayFramerate();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_DOWN){
        --camIndex;
        changeId(camIndex);
    }
    if(key == OF_KEY_UP){
        ++camIndex;
        changeId(camIndex);
    }
}

void ofApp::changeId(int id){
    camThread.lock();
    //can't change camera while running
    camThread.vidGrabber.close();
    camThread.vidGrabber.setDeviceID(id);
    camThread.vidGrabber.setDesiredFrameRate(60);
    //false tells us not to use gl textures
    camThread.vidGrabber.initGrabber(ofGetWidth(),ofGetHeight(), false);
    camThread.unlock();
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

void ofApp::exit() {
    // stop the thread
    camThread.stopThread();
}
