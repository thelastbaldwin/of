#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    int tileSize = 40;
    
    tile.loadImage("houndstooth.jpg");
    cout << ofGetWidth() << ", " << ofGetHeight() << endl;
    // int _x, int _y, int _width, int _height, int _cellSize, ofImage* tile
    cellGrid = Virus::CellGrid(0, 0, (ofGetWidth()/tileSize) + 1, (ofGetHeight()/tileSize) + 1, tileSize, &tile);
    
    ofSetFrameRate(24);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(cellGrid.getRemainingCellCount() <= 0){
        cellGrid.changeDirection();
    }
    cellGrid.spread();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0, 0);
    cellGrid.draw();
    
    std::stringstream ss;
    std::string frameRate;
    ss << ofGetFrameRate();
    ss >> frameRate;
    ofDrawBitmapString(frameRate, ofGetWidth() - 40, ofGetHeight() - 20);
    ss.clear();
    ss.str("");
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
