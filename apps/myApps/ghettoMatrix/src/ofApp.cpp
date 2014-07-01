#include "ofApp.h"

//TODO: load these from XML settings
const int ofApp::PORT = 12345;
const std::string ofApp::HOST = "localhost";

bool isFacetime(const ofVideoDevice& device){
    return device.deviceName == "FaceTime HD Camera";
}


//--------------------------------------------------------------
void ofApp::setup(){
    sender.setup(HOST, PORT);
    receiver.setup(PORT);
    
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    //    lambdas will be supported in oF 0.9, but not now
    //    https://github.com/openframeworks/openFrameworks/issues/2335
    //    auto func = [](){return false};
    auto it = std::find_if(devices.begin(), devices.end(), isFacetime);
    devices.erase(it);

}

//--------------------------------------------------------------
void ofApp::update(){
    while(receiver.hasWaitingMessages()){
        // get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        if(m.getAddress() == "/take/picture"){
			//get all the camera pictures
            //stitch together into gif
            //send saved filename
		}else{
            std::cout << m.getAddress();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

}

void ofApp::onGifSaved(string &fileName) {
    cout << "gif saved as " << fileName << endl;
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
    ofxOscMessage m;
	m.setAddress("/photo/transmit");
	m.addStringArg("ohboy.gif");
	sender.sendMessage(m);
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

void ofApp::exit(){
    gifEncoder.exit();
}
