#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableSmoothing(); //smooth edges
    ofSetFrameRate(60); //fixed framerate
}

//--------------------------------------------------------------
void testApp::update(){
    for(int i = 0; i < sizeof( particles) / sizeof( particles[0] ); i++){
        particles[i].update(testBall);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(ofColor::black);
    
    testBall.orbit();

    for(int i = 0; i < sizeof( particles) / sizeof( particles[0] ); i++){
        particles[i].display();
    }
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
