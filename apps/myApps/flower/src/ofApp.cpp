#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){
    stem0 = ofPoint(300, 100);
    stem1 = ofPoint(300, 270);
    stem2 = ofPoint(300, 300);
    stem3 = ofPoint(300, 400);
    leftLeaf = ofPoint(200, 220);
    rightLeaf = ofPoint(400, 220);

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);
    ofNoFill();
    
    ofPushMatrix();
    ofTranslate(stem0);
    
    float angle = ofGetElapsedTimef() * 30;
    ofRotate(angle);
    
    int petals = 15;
    for (int i = 0; i < petals; i++) {
        ofRotate(360.0 / petals);
        ofPoint p1(0, 20);
        ofPoint p2(80, 0);
        ofTriangle(p1, -p1, p2);
    }
    
    ofPopMatrix();
    
    
    ofSetColor(0, 0, 0);
    
    ofSetCircleResolution(20); //default. Increase number for larger circles
    ofCircle(stem0, 40);
    ofLine(stem0, stem3);
    ofTriangle(stem1, stem2, leftLeaf);
    ofTriangle(stem1, stem2, rightLeaf);
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