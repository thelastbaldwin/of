#include "testApp.h"
#include <math.h>
#include <time.h>
#include <string> //substr


//--------------------------------------------------------------
void testApp::setup(){
    //-- APP SPECIFIC VARS --//
    Force = 0.0;
    scorePercent = 0.0;
    wishindex = 0;
    incremented = false;
    blowingAway = false;
    
    //-- GENERAL SETUP -//
    bg.loadImage("bg.jpg");
    ofSetBackgroundAuto(false);
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    futuraMedium.loadFont("Futura.ttc", 14);
    
    //--- BEGIN PARTICLE SETUP --//
    count = 55;
    total = 0;
    ORIGIN.set(1024/2, 768/2);
    radius = 150;
    layer = 0;
    
    while(total < PARTICLE_COUNT){
        for(radius = 150; radius > 0; radius -=10){
            layer++;

            for(int i = 0; i < count; i++){
                 particles[total] = Particle(radius * sin(i*2*PI/count)+ORIGIN.x, radius*cos(i*2*PI/count)+ORIGIN.y, genParticleXRange(), genParticleYRange());
                total++;
            }
            count *= 0.95;
        }
    }
    //-- END PARTICLE SETUP--//
    
       
    //-- GET RECORDS -- //
	string url = "http://localhost:5000/I wish";

	bool parsingSuccessful = result.open(url);
	if ( parsingSuccessful )
    {
        cout << "Parsing successful" << endl;
		
	}
    else
    {
		cout  << "Failed to parse JSON" << endl;
	}    
    recordCount = result.size();
    
    //-- SERIAL --//
    serialVal = 0;
    //serial.enumerateDevices(); //list all devices.
    ard.connect("/dev/tty.usbmodem1a21", 57600);
    
    // listen for EInitialized notification. this indicates that
	// the arduino is ready to receive commands and it is safe to
	// call setupArduino()
	ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
	bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
}

//--------------------------------------------------------------
void testApp::update(){
    
    if(serialVal > 100){
        Force = serialVal * .002;
        blowingAway = true;
        comingBack = false;
    }else{
        comingBack = true;
        blowingAway = false;
    }
    
    if(blowingAway){
       for(int i= 0; i < PARTICLE_COUNT; i++){
            particles[i].blowAway(Force);
        }
    }
    if(comingBack){
        incremented = false; //flag. You can move to the next record once the particles are coming back
        for(int i= 0; i < PARTICLE_COUNT; i++){
            particles[i].comeBack();
        }
    }
    
    scorePercent = Particle::score/float(PARTICLE_COUNT);
    if(scorePercent == 1 && !incremented){
        incrementWishList();
        incremented = true;
    }
    
    //-- Text --//
    message = result[wishindex]["text"].asString();
    if(message.length() > 70){
		//if the lengrth is over this threshold, find the last punctuation mark or space
        size_t mid_space = message.rfind(' ', 70);
		//string substr ( size_t pos = 0, size_t n = npos ) const;
		string temp = message.substr(0, mid_space);
		message2 = message.substr(mid_space+1);
        message = temp;
	}else{
        message2 = string(); //empty string
    }
    
    //update the arduino
    ard.update();
}

//--------------------------------------------------------------
void testApp::draw(){

    //background with alpha transparency
    ofSetColor(255,255,255, 50);
    bg.draw(0, 0);

    for(int i= 0; i < PARTICLE_COUNT; i++){
        particles[i].display();
    }
    
    //--Score Bar--//
    ofSetColor(255, 255, 255, 30);
    ofRect(0, (ofGetHeight()/2)-12.5, ofGetWidth()*scorePercent, 100);
    
    //-- Text --//
    ofSetHexColor(0xFFFFFF);
    if(message2.empty()){
        futuraMedium.drawString(message, 10, 40);
    }else{
        futuraMedium.drawString(message, 10, 40);
        futuraMedium.drawString(message2, 10, 65);
    }
}

//--------------------------------------------------------------
void testApp::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    cout << ard.getFirmwareName() << endl;
    cout << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion() << endl;
    
    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    // If using Arduino 0022 or older, then use 16 - 21.
    // Firmata pin numbering changed in version 2.3 (which is included in Arduino 
    
    // set pin A2 to analog input
    ard.sendAnalogPinReporting(2, ARD_ANALOG);
    
    ofAddListener(ard.EAnalogPinChanged, this, &testApp::analogPinChanged);
}

// analog pin event handler, called whenever an analog pin value has changed
//--------------------------------------------------------------
void testApp::analogPinChanged(const int & pinNum) {
    // do something with the analog input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    //serialVal = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum));
    serialVal = ard.getAnalog(pinNum)/3;
    cout << "analog pin: " << ofToString(pinNum) << " = " << ofToString(serialVal) << endl;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    //357 = Up
    //359 = Down
    //358 = Left
    //356 = Right
   
    switch(key){
        case(98):
            blowingAway = true;
            comingBack = false;
            break;
        case(357):
            //up
            Force += 0.1;
            //cout << "Force = " << Force << endl; //test seems like a value from 1-1.5 is desireable. Above that is ok.
            break;
        case(359):
            //down
            Force -= 0.1;
            //cout << "Force = " << Force << endl;
            break;
        case(358):
            //right
            incrementWishList();
            break;
        case(356):
            decrementWishList();
            //left
            break;
        default:
            cout << key << " was pressed " <<  endl;
    }
}

void testApp::incrementWishList(){
    wishindex++;
    wishindex %= recordCount;
}

void testApp::decrementWishList(){
    wishindex > 0? wishindex--: wishindex = recordCount; //ternary, bitches
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if(key == 98){//'b'
        comingBack = true;
        blowingAway = false;
    }

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
