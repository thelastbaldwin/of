#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    camWidth = ofGetWidth();
    camHeight = ofGetHeight();

    //we can now get back a list of devices.
	vector<ofVideoDevice> devices = vidGrabber.listDevices();

    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}

    vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);
}

void ofApp::displayFramerate(){
    ofSetColor(255, 255, 255);
    std::stringstream ss;
    ss << "FPS: ";
    ss << ofGetFrameRate();
    ofDrawBitmapString(ss.str(), ofGetWidth() - 100, ofGetHeight() - 5);
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    vidGrabber.draw(0, 0);
    displayFramerate();
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
