#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    pos0 = ofPoint(512, 300);
    pos = ofPoint(600, 200);
    velocity = ofPoint(100, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    //constants
    const float dt = 1.0 / 6.0; //time step
    const float mass = 0.1; //mass of ball
    const float rubberLen = 200.0; //Segment's length
    const float k = 0.5; //Segment's stiffness
    const ofPoint g(0.0, 9.8); //Gravity force
    
    //Compute Hooke's force
    ofPoint delta = pos - pos0;
    float len = delta.length(); //Vector's length
    float hookeValue = k * (len - rubberLen);
    delta.normalize();
    ofPoint hookeForce = delta * (-hookeValue);
    
    //update velocity and position
    ofPoint force = hookeForce + g; // Resulted force
    ofPoint a = force / mass; //second newton's law
    velocity += a * dt; //Euler method
    pos += velocity * dt; //Euler method
}

//--------------------------------------------------------------
void ofApp::draw(){
    //white background
    ofBackground(255, 255, 255);
    
    //draw rubber as a blue line
    ofSetColor(0, 0, 255); //set bue color
    ofLine(pos0.x, pos0.y, pos.x, pos.y); //draw line
    
    //Draw ball as red circle
    ofSetColor(255, 0, 0);
    ofFill(); //enable filling
    ofCircle(pos.x, pos.y, 20);
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