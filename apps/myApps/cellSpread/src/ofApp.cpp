#include "ofApp.h"

const int ofApp::SEND_PORT = 12345;
const std::string ofApp::HOST = "localhost";
const float ofApp::heartBeatInterval = 30;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    int tileSize = 40;
    
    tile.loadImage("houndstooth.jpg");
    cout << ofGetWidth() << ", " << ofGetHeight() << endl;
    // int _x, int _y, int _width, int _height, int _cellSize, ofImage* tile
    cellGrid = Virus::CellGrid(0, 0, (ofGetWidth()/tileSize) + 1, (ofGetHeight()/tileSize) + 1, tileSize, &tile);
    
    ofSetWindowTitle("ofxSyphon CellSpread");
    
    individualTextureSyphonServer.setName("ofxSyphon CellSpread Texture OutPut");
    mainOutputSyphonServer.setName("ofxSyphon CellSpread Output");
    
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
    ofSetFrameRate(24);
    ofSetVerticalSync(true);
    
    sender.setup(HOST, SEND_PORT);
    lastInterval = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    if(cellGrid.getRemainingCellCount() <= 0){
        cellGrid.changeDirection();
    }
    cellGrid.spread();
    
    if(ofGetElapsedTimef() - lastInterval >= heartBeatInterval){
        lastInterval = ofGetElapsedTimef();
        cout << "interval reached: " << ofGetElapsedTimef() << endl;
        
        ofxOscMessage m;
        m.setAddress("/heartbeat");
        sender.sendMessage(m);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    ofBackground(0,0, 0);
    cellGrid.draw();
    fbo.end();
    
    fbo.draw(0, 0);
    
    individualTextureSyphonServer.publishTexture(&fbo.getTextureReference());
    mainOutputSyphonServer.publishScreen();
    
//    std::stringstream ss;
//    std::string frameRate;
//    ss << ofGetFrameRate();
//    ss >> frameRate;
//    ofDrawBitmapString(frameRate, ofGetWidth() - 40, ofGetHeight() - 20);
//    ss.clear();
//    ss.str("");
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
