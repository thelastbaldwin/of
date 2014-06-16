#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    W = ofGetWindowWidth();
    H = ofGetWindowHeight();
    counter = 0.0;
    xPos;
    yPos;
    speed = 0.15;
    radius = W/6;
    
    ofSetFrameRate(60); //lock framerate
}

//--------------------------------------------------------------
void testApp::update(){
    counter += speed;
}

//--------------------------------------------------------------
void testApp::draw(){
    //simple blue circle in center of screen
    ofSetColor(255);
    ofRect(0, 0, 5, 5);
    
    ofSetColor(0, 0, 255);    
    ofCircle(W/2, H/2, 30);
    ofCircle(W/2 + radius * cos(counter), H/2 + radius * sin(counter) , 10, 10);
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}