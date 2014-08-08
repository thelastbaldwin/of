#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //shader loading
    shader.load("shaders/shaderVert.c", "shaders/shaderFrag.c");
    
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(640, 480, true);
    plane.set(ofGetWidth(), ofGetHeight());
    plane.setPosition(plane.getWidth()/2, plane.getHeight()/2, 100);
    plane.setResolution(ofGetWidth()/4, ofGetHeight()/4);
    
    plane.mapTexCoordsFromTexture(vidGrabber.getTextureReference());
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    plane.mapTexCoordsFromTexture(vidGrabber.getTextureReference());
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofEnableDepthTest();
    //same as getTextureReference.draw();
    //vidGrabber.draw(0, 0);
    vidGrabber.getTextureReference().bind();
    shader.begin();
    
    shader.setUniform1f("time", ofGetElapsedTimef());
    
    //plane.draw();
    plane.drawWireframe();
    
    shader.end();
    vidGrabber.getTextureReference().unbind();
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