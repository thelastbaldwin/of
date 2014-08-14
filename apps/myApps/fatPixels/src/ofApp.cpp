#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int divisionFactor = 8;
    
    //shader loading
    shader.load("shaders/shaderVert.c", "shaders/shaderFrag.c", "shaders/shaderGeometry.c");
    shader.setGeometryInputType(GL_POINTS);
    //this will be a GL_TRIANGLE_STRIP
    shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    shader.setGeometryOutputCount(ofGetWidth() * ofGetHeight()/divisionFactor * 4);
    
    vidGrabber.setDeviceID(1);
    vidGrabber.initGrabber(640, 480, true);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    
    for(int i = 0; i < ofGetHeight(); i+=divisionFactor){
        for(int j = 0; j < ofGetWidth(); j+=divisionFactor){
            mesh.addVertex(ofPoint(j, i, 0));
            mesh.addTexCoord(ofPoint(j, i, 0));
        }
    }
    
    //gui
    gui.setup();
    gui.add(squareSize.setup("square size", 8.0, 0.5, 16.0));
    gui.add(cameraX.setup("cameraX", ofGetWidth()/2, -ofGetWidth()/2, ofGetWidth()));
    gui.add(cameraY.setup("cameraY", ofGetHeight()/2, -ofGetHeight()/2, ofGetHeight()));
    gui.add(cameraZ.setup("cameraZ", -200, -100, -500));
    
    bHide = true;
    
    cam.setPosition(ofGetWidth()/2, ofGetHeight()/2, cameraZ);
    cam.lookAt(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0));
    cam.setFov(60);
    cam.setVFlip(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
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
    
//    mesh.drawWireframe();
    mesh.draw();
    
    shader.end();
    vidGrabber.getTextureReference().unbind();
    cam.end();
    ofPopMatrix();
    
    if( bHide ){
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'h' ){
		bHide = !bHide;
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