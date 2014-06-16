#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    image.loadImage("IMG_0034_small.jpg");
    image2.clone(image);
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();
    
    //build image2 using image
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            float amp = sin( y * 0.03);
            int x1 = x + sin (time * 2.0) * amp * 50.0;
            
            //clamp x1 to range [0, image.width-1]
            x1 = ofClamp(x1, 0, image.width-1);
            
            //set image2(x,y) equal to image(x1,y1)
            ofColor color = image.getColor(x1, y);
            image2.setColor(x, y, color);
        }
    }
    
    image2.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(255);
    image2.draw(0, 0);
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