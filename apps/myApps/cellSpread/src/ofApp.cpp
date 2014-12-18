#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    tile.loadImage("houndstooth.jpg");
    
    // int _x, int _y, int _width, int _height, int _cellSize, ofImage* tile
    cellGrid = Virus::CellGrid(30, 30, 80, 80, 10, &tile);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(cellGrid.getRemainingCellCount() <= 0){
        cellGrid.changeDirection();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(201,201, 201);
    cellGrid.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
   cellGrid.spread();
//    std::cout << cellGrid << std::endl;
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
