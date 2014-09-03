#include "ofApp.h"

const float ofApp::WIGOUT_INTERVAL = 1.0;

//--------------------------------------------------------------
void ofApp::setup(){
    int divisionFactor = 8;
    
    //defualt settings
    defaultSettings.squareSize = 8.0;
    defaultSettings.wavelength = 0.01;
    defaultSettings.amplitude = 0.1;
    defaultSettings.speed = 1.0;
    defaultSettings.cameraX = ofGetWidth()/2;
    defaultSettings.cameraY = ofGetHeight()/2;
    defaultSettings.cameraZ = -200;
    defaultSettings.opacity = 1.0;
    defaultSettings.scanlineHeight = 2;
    defaultSettings.scrollSpeed = 0;
    
    //shader loading
    shader.load("shaders/shaderVert.c", "shaders/shaderFrag.c", "shaders/shaderGeometry.c");
    shader.setGeometryInputType(GL_POINTS);
    
    //this will be a GL_TRIANGLE_STRIP
    shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    shader.setGeometryOutputCount(ofGetWidth() * ofGetHeight()/divisionFactor * 4);
    
    wiggleShader.load("shaders/passThroughVert.c", "shaders/horizontalDistortFrag.c");
    
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(640, 480, true);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    quad.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    
    //set up point mesh
    for(int i = 0; i < ofGetHeight(); i+=divisionFactor){
        for(int j = 0; j < ofGetWidth(); j+=divisionFactor){
            mesh.addVertex(ofPoint(j, i, 0));
            mesh.addTexCoord(ofPoint(j, i, 0));
        }
    }
    
    //set up quad mesh
    quad.addVertex(ofPoint(0, ofGetHeight(), 0));
    quad.addTexCoord(ofPoint(0, ofGetHeight(), 0));
    quad.addVertex(ofPoint(0, 0, 0));
    quad.addTexCoord(ofPoint(0, 0, 0));
    quad.addVertex(ofPoint(ofGetWidth(), ofGetHeight(), 0));
    quad.addTexCoord(ofPoint(ofGetWidth(), ofGetHeight(), 0));
    quad.addVertex(ofPoint(ofGetWidth(), 0, 0));
    quad.addTexCoord(ofPoint(ofGetWidth(), 0, 0));
    
    //gui
    gui.setup();
    gui.add(squareSize.setup("square size", defaultSettings.squareSize, 0.5, 16.0));
    gui.add(wavelength.setup("wavelength", defaultSettings.wavelength, 0.01, 10.0));
    gui.add(amplitude.setup("amplitude", defaultSettings.amplitude, 0.1, 100.0));
    gui.add(speed.setup("speed", defaultSettings.speed, 1.0, 1000.0));
    gui.add(cameraX.setup("cameraX", defaultSettings.cameraX, -ofGetWidth()/2, ofGetWidth()));
    gui.add(cameraY.setup("cameraY", defaultSettings.cameraY, -ofGetHeight()/2, ofGetHeight()));
    gui.add(cameraZ.setup("cameraZ", defaultSettings.cameraZ, -100, -500));
    gui.add(scrollSpeed.setup("scroll speed", defaultSettings.scrollSpeed, 0.0, 2000.0));
    gui.add(scanlineHeight.setup("scanline height", defaultSettings.scanlineHeight, 1, 20));
    gui.add(doFade.setup("enable fading", true));
    gui.add(opacity.setup("opacity", defaultSettings.opacity, 0.0, 1.0));
    gui.add(bWigout.setup("enable wigout", true));
    gui.add(bDistortVideo.setup("distort video", false));
    gui.add(overlayColor.setup("overlay color", ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(0.0, 0.0, 0.0, 0.0), ofFloatColor(1.0, 1.0, 1.0, 1.0)));
    
    bHide = true;
	bFade = false;
    
    cam.setPosition(ofGetWidth()/2, ofGetHeight()/2, cameraZ);
    cam.lookAt(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0));
    cam.setFov(60);
    cam.setVFlip(true);
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    //load video
    videoPlayer.loadMovie("glitch_video.mov");
	videoPlayer.setPosition(0.0);
    videoPlayer.setLoopState(OF_LOOP_NONE);
    videoPlayer.play();
    
    scanlineImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    generateScanlineImage(scanlineImage, scanlineHeight);
    prevScanlineHeight = scanlineHeight;
    
    doWigout = false;
    targetTime = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    
    if(videoPlayer.getIsMovieDone()){
        bFade = !bFade;
		videoPlayer.setPosition(0.0);
        videoPlayer.play();
        bDistortVideo = false;
    }else if(videoPlayer.getPosition() > 0.85){
        bDistortVideo = true;
    }
    
    if (prevScanlineHeight != scanlineHeight) {
        generateScanlineImage(scanlineImage, scanlineHeight);
        prevScanlineHeight = scanlineHeight;
    }
    
    videoPlayer.update();
    
    time = ofGetElapsedTimef();
    
    if (bWigout && time >= targetTime) {
        if (doWigout) {
            shuffleSettings();
            targetTime = time + WIGOUT_INTERVAL;
            doWigout = !doWigout;
        }else {
            reset();
            targetTime = time + ofRandom(3.0, 5.0);
            doWigout = !doWigout;
        }

    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    ofBackground(0, 0, 0);
    ofPushMatrix();
    ofScale(-1.0, 1.0);
    ofTranslate(-ofGetWidth(), 0);
    
    cam.begin();
    cam.setPosition(cameraX, cameraY, cameraZ);
    cam.lookAt(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0));
    
    vidGrabber.getTextureReference().bind();
    shader.begin();
    
    shader.setUniform1f("squareSize", squareSize);
    
    mesh.draw();
    
    shader.end();
    vidGrabber.getTextureReference().unbind();
    cam.end();
    ofPopMatrix();
    fbo.end();
    
    fbo.getTextureReference().bind();
    wiggleShader.begin();
    
    wiggleShader.setUniformTexture("video", videoPlayer.getTextureReference(), 1);
    wiggleShader.setUniformTexture("scanlines", scanlineImage.getTextureReference(), 2);
    wiggleShader.setUniform1f("time", time);
    wiggleShader.setUniform1f("wavelength", wavelength);
    wiggleShader.setUniform1f("amplitude", amplitude);
    wiggleShader.setUniform1f("speed", speed);
    wiggleShader.setUniform1i("scanlineHeight", scanlineHeight);
    wiggleShader.setUniform1f("opacity", opacity);
    wiggleShader.setUniform1f("bDistortVideo", (bDistortVideo) ? 1.0 : 0.0);
    wiggleShader.setUniform1f("scrollSpeed", scrollSpeed);
    ofSetColor(overlayColor);
    
    quad.draw();
    wiggleShader.end();
    
    if( bHide ){
		gui.draw();
	}

    adjustOpacity(opacity);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'h' ){
		bHide = !bHide;
	}
    
    if (key == 'r') {
        reset();
    }
    
    if (key == 'w'){
        shuffleSettings();
    }
}

template<typename T> void ofApp::adjustOpacity(T& opacity){
    const float FADE_RATE = 0.03;
    
    if(doFade && bFade && opacity >= 0){
        opacity = opacity - FADE_RATE;
    
    }else if(doFade && !bFade && opacity <= 1.0){
        opacity = opacity + FADE_RATE;
    }
    
    opacity = ofClamp(opacity, 0.0, 1.0);
}

//--------------------------------------------------------------
void ofApp::reset(){
    squareSize = defaultSettings.squareSize;
    wavelength = defaultSettings.wavelength;
    amplitude = defaultSettings.amplitude;
    speed = defaultSettings.speed;
    cameraX = defaultSettings.cameraX;
    cameraY = defaultSettings.cameraY;
    cameraZ = defaultSettings.cameraZ;
    scanlineHeight = defaultSettings.scanlineHeight;
    scrollSpeed = defaultSettings.scrollSpeed;
    
    if(ofGetScreenHeight() != 320 && ofGetScreenWidth() != 540){
        ofSetWindowShape(540, 320);
    }
}

void ofApp::shuffleSettings(){
    squareSize = ofRandom(2.0, 10.0);
    wavelength = ofRandom(5.0, 100.0);
    amplitude = ofRandom(20.0, 80.0);
    speed = ofRandom(180.0, 700.0);
    cameraX = ofRandom(180.0, 380.0);
    cameraY = ofRandom(100.0, 220.0);
    cameraZ = ofRandom(-200.0, -100.0);
    scrollSpeed = ofRandom(100.0, 2000.0);
    
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}


//--------------------------------------------------------------
void ofApp::generateScanlineImage(ofImage& img, int scanLineHeight, float opacity){
    //generate a scanLine pattern in a provided image
    
    
    ofPixels pixels = img.getPixelsRef();
    int currentPixelCount = 0,
    index = 0;
    //start with black
    bool isDark = true;
    
    const ofColor black(0, 0, 0, opacity * 255);
    const ofColor transparent(0, 0, 0, 0);
    ofColor currentColor;
    
    //columns
    for(int i = 0; i < img.getHeight(); ++i){
        //this modulo operation could happen in the shader itself,
        //making the need for this texture generation obsolete
        if(i % scanLineHeight == 0){
            isDark = !isDark;
        }
        
        if(isDark){
            currentColor = black;
        }else{
            currentColor = transparent;
        }
        
        //rows
        for(int j = 0; j < img.getWidth(); ++j){
            pixels.setColor(j, i, currentColor);
        }
    }
    
    img.setFromPixels(pixels);
    img.reloadTexture();
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