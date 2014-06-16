#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    origin.setPosition(ofGetWindowWidth()/2, ofGetWindowHeight()/4, 0);
    speed = 0.015;
    counter = 0.0;
    W = ofGetWindowWidth();
    H = ofGetWindowHeight();
    radius = 50;
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void testApp::update(){
    counter += speed;
}

//--------------------------------------------------------------
void testApp::draw(){
    
    std::cout << "counter = " << counter << std::endl;
    cam.begin();
    cam.setTarget(origin);
    
    ofNoFill();
    ofSphere(W/2, H/2, 0, radius); //wireframe base sphere
    
    //orbit around z-axis
    ofSetColor(ofColor::black);
    ofSphere(W/2 + radius * cos(counter), H/2 + radius * sin(counter), 10);
    
    //orbit around y-axis
    ofSetColor(ofColor::blue);
    ofSphere(W/2 + radius * cos(counter), H/2 ,radius * sin(counter), 10);
    
    //orbit around x-axis
    ofSetColor(ofColor::red);
    ofSphere(W/2, H/2 + radius * cos(counter) ,radius * sin(counter), 10);
    
    //x-axis - center
    ofSetColor(ofColor::red);    
    ofLine(0, H/2, W, H/2);
    
    //y-axis - center
    ofSetColor(ofColor::blue);
    ofLine(W/2, 0, W/2, H);
    
    //z-axis - center //note - this may not appear
    ofSetColor(ofColor::black);
    ofLine(W/2, H/2, -100, W/2, H/2, 100);
    
    cam.end();
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