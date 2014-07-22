#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    borderSize =20;

	camWidth 		= ofGetWidth()/NUM_ACCROSS - borderSize;	// try to grab at this size.
	camHeight 		= ofGetHeight()/NUM_DOWN - borderSize;
	
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
	
    //will be released when sketch is closed
	framePixels = new unsigned char[camWidth*camHeight*3]; //space for 3 bytes
    
    //allocate texture memory
    for (int i =0 ; i < NUM_COLORS; ++i) {
        videoTexture[i].allocate(camWidth,camHeight, GL_RGB);
    }
    
    //pick colors
    colorTriads[0] = colorTriad(ofColor::blue, ofColor::green, ofColor::silver);
    colorTriads[1] = colorTriad(ofColor::red, ofColor::orange, ofColor::yellow);
    colorTriads[2] = colorTriad(ofColor::black, ofColor::gray, ofColor::white);
    colorTriads[3] = colorTriad(ofColor::blue, ofColor::orange, ofColor::white);
    colorTriads[4] = colorTriad(ofColor::steelBlue, ofColor::cyan, ofColor::pink);
    colorTriads[5] = colorTriad(ofColor::black, ofColor::red, ofColor::white);
    colorTriads[6] = colorTriad(ofColor::orchid, ofColor::paleGoldenRod, ofColor::paleGreen);
    colorTriads[7] = colorTriad(ofColor::chartreuse, ofColor::chocolate, ofColor::coral);
	
	ofSetVerticalSync(true);
    
    //load logo
    hashtag.loadImage("hashtag.png");
    hashtag.resize(hashtag.width/3, hashtag.height/3);
}

void polarizeColor(ofColor& original, const colorTriad& triad){
    //    takes a color by reference, shifting it into one of three
    //    bands based on averge value
    const int COLOR_MAX = 255;
    int colorAvg = (original.r + original.g + original.b) / 3;
    
    if (colorAvg < COLOR_MAX/3){
        original = triad.low;
    }
    else if(colorAvg >= COLOR_MAX/3 && colorAvg <= 2 * COLOR_MAX/3){
        original = triad.mid;
    }
    else if(colorAvg > 2 * COLOR_MAX/3){
        original = triad.high;
    }
};


//--------------------------------------------------------------
void ofApp::update(){
	
	ofBackground(255,255,255);
	
	vidGrabber.update();
	
	if (vidGrabber.isFrameNew()){
        for(int shiftIndex = 0; shiftIndex < NUM_COLORS; ++shiftIndex){
            int pixelCount = camWidth * camHeight;
            int totalBytes = pixelCount * 3;
            unsigned char * pixels = vidGrabber.getPixels(); //3 bytes per pixel
            for (int i = 0; i < totalBytes; i+=3){
                ofColor currentColor(pixels[i], pixels[i+1], pixels[i+2]);                             
                polarizeColor(currentColor, colorTriads[shiftIndex]);
                
                //where color shift happens
                //fun fact, r.g.b is accomplished by a union
                framePixels[i] = currentColor.r;
                framePixels[i+1] = currentColor.g;
                framePixels[i+2] = currentColor.b;
            }
            videoTexture[shiftIndex].loadData(framePixels, camWidth,camHeight, GL_RGB);
        }
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofHideCursor();
    ofPushMatrix();
    ofScale(-1.0, 1.0);
    ofTranslate(-ofGetWidth(), 0);
	ofSetHexColor(0xffffff);

    for (int i = 0; i < NUM_ACCROSS; ++i) {
        for (int j = 0; j < NUM_DOWN; ++j) {
            videoTexture[(i + j) % NUM_COLORS].draw(i * (borderSize + camWidth) + borderSize/2, j* (borderSize + camHeight) + borderSize/2,camWidth,camHeight);
        }
    }
    ofPopMatrix();

    ofSetColor(255, 255, 255, 200);
    ofFill();
    ofRect(ofGetWidth() - hashtag.width - 15, ofGetHeight() - hashtag.height - 15, hashtag.width + 15, hashtag.height + 15);
    ofSetColor(255, 255, 255, 255);
    hashtag.draw(ofGetWidth() - hashtag.width - 8, ofGetHeight() - hashtag.height - 8);
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
//	if (key == 's' || key == 'S'){
//		vidGrabber.videoSettings();
//	}
	
	
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
