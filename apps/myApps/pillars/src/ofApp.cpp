#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    pointLight.setDiffuseColor(ofColor(255));
    pointLight.setPosition(ofGetWidth()/2, ofGetHeight()/2, 500);
    
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            boxes[j][i].set(80);
            boxes[j][i].setPosition(80 * i, 80 * j, 0);
        }
    }
    timer = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){
//    cout << ofNoise(ofGetElapsedTimef()) << endl;
//        cout << timer << endl;
    timer += 0.1;
    
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            boxes[j][i].setPosition(boxes[j][i].getPosition().x, boxes[j][i].getPosition().y, sin(j + i + timer) * 80);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    ofEnableLighting();
    pointLight.enable();

    ofTranslate(40, 40, 0);
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            ofSetColor(ofColor(255, 0, 0));
            boxes[j][i].draw();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
