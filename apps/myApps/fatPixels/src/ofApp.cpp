#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //shader loading
    shader.load("shaders/shaderVert.c", "shaders/shaderFrag.c", "shaders/shaderGeometry.c");
    shader.setGeometryInputType(GL_POINTS);
    //this will be a GL_TRIANGLE_STRIP
    shader.setGeometryOutputType(GL_POINTS);
    shader.setGeometryOutputCount(ofGetWidth() * ofGetHeight());
    
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(640, 480, true);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    for(int i = 0; i < ofGetHeight(); ++i){
        for(int j = 0; j < ofGetWidth(); ++j){
            mesh.addVertex(ofPoint(j, i, 0));
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofEnableDepthTest();
    //same as getTextureReference.draw();
    //vidGrabber.draw(0, 0);
    vidGrabber.getTextureReference().bind();
    shader.begin();
    
    //shader.setUniform1f("time", ofGetElapsedTimef());
    
    mesh.draw();
    //plane.drawWireframe();
    
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