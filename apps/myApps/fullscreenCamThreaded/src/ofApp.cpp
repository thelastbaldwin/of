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