#include "ofApp.h"

//TODO: load these from XML settings
const int ofApp::SEND_PORT = 12346;
const int ofApp::RECEIVE_PORT = 12345;
const std::string ofApp::HOST = "localhost";

bool isFacetime(const ofVideoDevice& device){
    return device.deviceName == "FaceTime HD Camera";
}


//--------------------------------------------------------------
void ofApp::setup(){
    sender.setup(HOST, SEND_PORT);
    receiver.setup(RECEIVE_PORT);
    
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
            std::string type = m.getArgAsString(0);
            std::string id = m.getArgAsString(1);
            
            
            if(type == "matrix"){
                cout << "matrix requested" << endl;
                //get all the camera pictures
                //stitch together into gif
                //send saved filename
                sendMessage("ohboy.gif", id);
            }else if(type == "traditional"){
                cout << "traditional requested" << endl;
                //take 4 photos
                //compose into framebuffer object
                //drop a sweet logo on the bottom
                //profit
                sendMessage("cat.jpeg", id);
            }
			
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

void ofApp::sendMessage(std::string filename, std::string id){
    ofxOscMessage m;
	m.setAddress("/transmit/photo");
	m.addStringArg(filename);
    m.addStringArg(id);
	sender.sendMessage(m);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::exit(){
    gifEncoder.exit();
}
