#include "ofApp.h"

//TODO: load these from XML settings
const int ofApp::SEND_PORT = 12346;
const int ofApp::RECEIVE_PORT = 12345;
const std::string ofApp::HOST = "localhost";


//--------------------------------------------------------------
void ofApp::setup(){
    sender.setup(HOST, SEND_PORT);
    receiver.setup(RECEIVE_PORT);

    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    //    lambdas will be supported in oF 0.9, but not now
    //    https://github.com/openframeworks/openFrameworks/issues/2335
    //    auto func = [](){return false};
    //for (ofVideoDevice device: devices){
    for(int i = 0; i < devices.size(); ++i){
        if(devices[i].bAvailable){
            //cout << devices[i].id << " : " << devices[i].deviceName << endl;
        }
    }

    settings.load("settings.xml");
    //settings.deserialize();

    cout << settings.getValue() << endl;
    cout << settings.getName() << endl;
    cout << settings.getNumChildren() << endl;

    cout << "camthread1" << settings.getValue("camthread1") << endl;
    cout << "camthread2" << settings.getValue("camthread2") << endl;
    cout << "maincam" << settings.getValue("maincam") << endl;

    std::vector<int> cam1Ids = getCameraIds(settings.getValue("camthread1"));
    std::vector<int cam2Ids = getCameraIds(settings.getValue("camthread2"));

    //arbitrarily deciding camera 0 is the main cam
    std::vector<int> mainCameraIds;
    mainCameraIds.push_back(0);
    hMainCameraThread = new CamThread(mainCameraIds, 1024, 768);
    hMainCameraThread->startThread();

    beep.loadSound("short_beep.wav");
    beep.setMultiPlay(false);
    yeah.loadSound("short_yeah.ogg");
    yeah.setMultiPlay(false);
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
                std::string fileName = takeTraditionalPhoto("traditional - " + ofGetTimestampString("%m%d%Y-%H%M%s") + ".jpg");
                sendMessage(fileName, id);
            }

		}else{
            std::cout << m.getAddress();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

}

 std::vector<int> ofApp::getCameraIds(std::string idString){
    std::vector<string> cam1Addresses = ofSplitString(idString, " ");
    std::vector<int> camIds;
    std::stringstream ss;
    int fromString;

    std::for_each(cam1Addresses.begin(), cam1Addresses.end(), [&ss, &fromString, &camIds](string s){
        ss << s;
        ss >> fromString;
        camIds.push_back(fromString);
        ss.str("");
        ss.clear();
    });

    return camIds;
 }

void ofApp::onGifSaved(string &fileName) {
    cout << "gif saved as " << fileName << endl;
}

std::string ofApp::takeTraditionalPhoto(const string &fileName){
    //set up stage
    ofFbo fbo;
    fbo.allocate(1024 * 2, 768 * 2, GL_RGB);
    ofImage currentFrame;
    currentFrame.allocate(1024, 768, OF_IMAGE_COLOR);

    fbo.begin();
    //repeat 4 times
    for(int i = 0; i < 4; ++i){
        //wait 3 seconds
        beep.play();
        ofSleepMillis(1300);
        yeah.play();
        hMainCameraThread->lock();
        currentFrame.getPixelsRef() = hMainCameraThread->pixels[0];
        hMainCameraThread->unlock();
        currentFrame.reloadTexture();
        //draw to fbo in correct quadrant
        switch(i){
            case 0:
                currentFrame.draw(0, 0);
                break;
            case 1:
                currentFrame.draw(1024, 0);
                break;
            case 2:
                currentFrame.draw(0, 768);
                break;
            case 3:
                currentFrame.draw(1024, 768);
                break;
        }
        ofSleepMillis(800);
    }
    fbo.end();

    //save the image in the fbo
    ofImage finalImage;
    finalImage.allocate(1024 * 2, 768 * 2, OF_IMAGE_COLOR);
    fbo.readToPixels(finalImage.getPixelsRef());
    finalImage.reloadTexture();
    finalImage.saveImage(fileName);
    return fileName;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //just for testing, but might be useful for MANUAL OVERRIDE
    if(key == ' '){
        cout << "space pressed" << endl;
        takeTraditionalPhoto("traditional - " + ofGetTimestampString("%m%d%Y-%H%M%s") + ".jpg");
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
    hMainCameraThread->stopThread();
    delete hMainCameraThread;
    gifEncoder.exit();
}
