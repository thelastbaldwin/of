#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){        
#ifdef TARGET_OPENGLES
        shader.load("shadersES2/shaderVert.c","shadersES2/shaderFrag.c");
#else
        if(ofIsGLProgrammableRenderer()){
            shader.load("shadersGL3/shaderVert.c","shadersGL3/shaderFrag.c");
        }else{
            shader.load("shadersGL2/shaderVert.c","shadersGL2/shaderFrag.c");
        }
#endif

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    shader.begin();
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
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