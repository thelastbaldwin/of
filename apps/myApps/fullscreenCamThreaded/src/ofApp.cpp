#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camThread.startThread(true, false);   // blocking, verbose
    camTex.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
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
    displayFramerate();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1'){
        changeId(0);
    }
    else if(key == '2'){
        changeId(1);
    }
    else if(key == '3'){
        changeId(2);
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
