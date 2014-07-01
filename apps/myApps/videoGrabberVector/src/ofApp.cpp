#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	camWidth 		= 320;	// try to grab at this size. 
	camHeight 		= 240;
	
    //we can now get back a list of devices. 
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName; 
        if( devices[i].bAvailable && devices[i].deviceName != "FaceTime HD Camera"){
            cout << endl;
            ofVideoGrabber grabber;
            cams.push_back(grabber);
            cams[i].setDeviceID(i);
            cams[i].initGrabber(camWidth,camHeight);
            
        }else{
            cout << " - unavailable " << endl; 
        }
	}
    
    
    std::cout << cams.size() << " cameras" << std::endl;
	ofSetVerticalSync(true);
}


//--------------------------------------------------------------
void ofApp::update(){
	
	ofBackground(100,100,100);
	
	for(auto cam: cams){
        cam.update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xffffff);
    int offset = 0;
	for(auto cam: cams){
        cam.draw(offset * 320, 0);
        ++offset;
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	// Video settings no longer works in 10.7
	// You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343        
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
	
	
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
