#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){
    
    int w = 512,
        h = 512;
    
    //must call delete on data;
    unsigned char* data = new unsigned char[w * h * 4];
    
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            //            time from application start
            float time = ofGetElapsedTimef();
            
            //            level of hyperbola value of x and y with center in
            //            w/2, h/2
            float v = (x - w/2) * (y - h/2);
            
            //            combining v with time for motion effect
            float u = v * 0.00025 + time;
            
            //            computee color components as periodical
            //            functions of u, and stretched to [0...255]
            int red = ofMap(sin(u), -1, 1, 0, 255),
            green = ofMap(sin(u*2), -1, 1, 0, 255),
            blue = 255 - green,
            alpha = 255;
            
            //            fill array components for pixel (x, y):
            int index = 4 * (x + w * y);
            data[index] = red;
            data[index + 1] = green;
            data[index + 2] = blue;
            data[index + 3] = alpha;
            
        }
    }
    
    //            load array to image
    image.setFromPixels(data, w, h, OF_IMAGE_COLOR_ALPHA);
    
    delete[] data;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(255);
    image.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //p
    if( key == 112){
        EM::takeScreenShot();
    }
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