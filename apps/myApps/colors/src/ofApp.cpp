#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);
    
    // changing brightness
    for (int i = 0; i < 256; i++) {
        ofColor color = ofColor::red;
        color.setBrightness(i);
        ofSetColor(color);
        ofLine(i, 0, i, 50);
    }
    
    // changing saturation
    for (int i = 0; i < 256; i++) {
        ofColor color = ofColor::red;
        color.setSaturation(i);
        ofSetColor(color);
        ofLine(i, 80, i, 130);
        
    }
    
    // changing hue
    for (int i = 0; i < 256; i++) {
        ofColor color = ofColor::red;
        color.setHue(i);
        ofSetColor(color);
        ofLine(i, 160, i, 210);
        
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    EM::takeScreenShot();
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