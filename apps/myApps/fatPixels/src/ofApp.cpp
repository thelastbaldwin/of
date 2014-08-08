#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int divisionFactor = 8;
    
    //shader loading
    shader.load("shaders/shaderVert.c", "shaders/shaderFrag.c", "shaders/shaderGeometry.c");
    shader.setGeometryInputType(GL_POINTS);
    //this will be a GL_TRIANGLE_STRIP
    shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    shader.setGeometryOutputCount(ofGetWidth() * ofGetHeight()/divisionFactor * 4);
    
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(640, 480, true);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    
    for(int i = 0; i < ofGetHeight(); i+=divisionFactor){
        for(int j = 0; j < ofGetWidth(); j+=divisionFactor){
            mesh.addVertex(ofPoint(j, i, 0));
            mesh.addTexCoord(ofPoint(j, i, 0));
        }
    }
    
    cam.setPosition(ofGetWidth()/2, ofGetHeight()/2, -180);
    cam.lookAt(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0));
    cam.setFov(60);
    cam.setVFlip(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofScale(-1.0, 1.0);
    ofTranslate(-ofGetWidth(), 0);
    
    vidGrabber.getTextureReference().bind();
    cam.begin();
    shader.begin();
    
    //shader.setUniform1f("time", ofGetElapsedTimef());
    
//    mesh.drawWireframe();
    mesh.draw();
    
    shader.end();
    vidGrabber.getTextureReference().unbind();
    cam.end();
    ofPopMatrix();
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