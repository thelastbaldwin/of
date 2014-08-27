#include "ofApp.h"

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
    gui.add(wavelength.setup("wavelength", defaultSettings.wavelength, 0.01, 100.0));
    gui.add(amplitude.setup("amplitude", defaultSettings.amplitude, 0.1, 100.0));
    gui.add(speed.setup("speed", defaultSettings.speed, 1.0, 1000.0));
    gui.add(cameraX.setup("cameraX", defaultSettings.cameraX, -ofGetWidth()/2, ofGetWidth()));
    gui.add(cameraY.setup("cameraY", defaultSettings.cameraY, -ofGetHeight()/2, ofGetHeight()));
    gui.add(cameraZ.setup("cameraZ", defaultSettings.cameraZ, -100, -500));
    gui.add(scanlineHeight.setup("scanline height", 10, 4, 20));
    gui.add(doFade.setup("enable fading", true));
    gui.add(opacity.setup("opacity", defaultSettings.opacity, 0.0, 1.0));
    
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
    
    scanLineImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    
    if(videoPlayer.getIsMovieDone()){
        cout << "video complete" << endl;
        bFade = !bFade;
		videoPlayer.setPosition(0.0);
        videoPlayer.play();
    }
    videoPlayer.update();
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
    wiggleShader.setUniform1f("time", ofGetElapsedTimef());
    wiggleShader.setUniform1f("wavelength", wavelength);
    wiggleShader.setUniform1f("amplitude", amplitude);
    wiggleShader.setUniform1f("speed", speed);
    wiggleShader.setUniform1i("scanlineHeight", scanlineHeight);
    wiggleShader.setUniform1f("opacity", opacity);
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
void ofApp::keyReleased(int key){
    
}


//--------------------------------------------------------------
void generateScanlineImage(ofImage& img, int scanLineHeight, float opacity){
    ofPixels pixels = img.getPixelsRef();
    int currentPixelCount = 0,
        index = 0,
        totalPixels = img.getWidth() * img.getHeight() * 4,
//        since the pixels are a 1D array, we need to
//        traverse the array in terms of sections of the scanline images
//        total width
        scanLineWidth = scanLineHeight * img.getWidth();
    //start with filled in
    bool isDark = true;

    while(index != totalPixels){
        if(currentPixelCount < scanLineWidth){

        }
        
        ++currentPixelCount;
        ++index;
    }
    
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