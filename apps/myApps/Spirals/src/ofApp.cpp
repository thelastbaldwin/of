#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
    fbo.begin();
    ofBackground(255);
    fbo.end();
    
    a = 0;
    b = 0;
    pos = ofPoint( ofGetWidth()/2, ofGetHeight()/2);
    
    colorStep = 0; 
}

//--------------------------------------------------------------
void ofApp::update(){
    fbo.begin();
    for(int i=0; i < 200; i++){
        draw1();    
    }
    fbo.end();
}

void ofApp::draw1(){
    // a holds values in radians, b holds values in degrees
    // when changing we multiply by DEG_TO_RAD constant
    a += b * DEG_TO_RAD;
    
    //change b
    b = b + 0.5;
    
    //Shift pos in direction defined by angle a
    lastPos = pos; // store last position
    ofPoint d = ofPoint(cos(a), sin(a));
    float len = 20;
    pos += d * len;
    
    //Chnage color each 100 steps
    if (colorStep % 100 == 0){
        //Generate random color
        color = ofColor (ofRandom(0, 255), ofRandom(0, 255), ofRandom(0,255));
    }
    colorStep++;
    
    //draw line segment
    ofSetColor(color);
    ofLine(lastPos, pos);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(255);
    fbo.draw(0, 0);

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