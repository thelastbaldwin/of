#include "ofApp.h"

//require a default constructor because we're allocating memory in the header
ofApp::TrippyQuad::TrippyQuad():rotOffset(0.0), amplitude(0.0){};
ofApp::TrippyQuad::TrippyQuad(float _rotOffset, float _amplitude, float _speed):rotOffset(_rotOffset), amplitude(_amplitude), speed(_speed){};

//--------------------------------------------------------------
void ofApp::setup(){
    
    quadWidth = ofGetWidth() / columns;
    quadHeight = ofGetHeight() / rows;
    padding = quadWidth * 0.5;
    
    for (int i = 0; i < rows * columns; ++i) {
        //rotationOffset, amplitude
        trippyQuads[i] = TrippyQuad(ofRandom(0, 500), ofRandom(2.0, 10.0), ofRandom(0.0, 2.0));
    }
    
    //shader loading
    textureShader.load("textureShaders/shaderVert.c", "textureShaders/shaderFrag.c");
    
    //set up quad mesh - used as frame for fbo in draw loop
    quad.addVertex(ofPoint(0, quadHeight + padding, 0));
    quad.addTexCoord(ofPoint(0, quadHeight + padding, 0));
    quad.addVertex(ofPoint(0, 0, 0));
    quad.addTexCoord(ofPoint(0, 0, 0));
    quad.addVertex(ofPoint(quadWidth + padding, quadHeight + padding, 0));
    quad.addTexCoord(ofPoint(quadWidth + padding, quadHeight + padding, 0));
    quad.addVertex(ofPoint(quadWidth + padding, 0, 0));
    quad.addTexCoord(ofPoint(quadWidth + padding, 0, 0));
    
    quad.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    //allocate memory for frame buffer object
    fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //generate texture in FBO
    fbo.begin();
    textureShader.begin();
    textureShader.setUniform1f("time", time);
    textureShader.setUniform1f("speed", ofDist(0, 0, 0, ofGetMouseY()));
    textureShader.setUniform1f("lineThickness", ofDist(0, 0, 0, ofGetMouseX()));
    ofBackground(255, 0, 0);
    quad.draw();
    textureShader.end();
    fbo.end();
    
    //create texture from FBO
    fbo.getTextureReference().bind();
    
    for (int i = 0, y = 0; i < rows; ++i, y += quadHeight) {
        for (int j = 0, x = 0; j < columns; ++j, x += quadWidth) {
            int index = (i * rows) + j;
            ofPushMatrix();
            ofTranslate(x, y);
            ofRotateZ(sin(time * trippyQuads[index].speed + trippyQuads[index].rotOffset) * trippyQuads[index].amplitude);
            quad.draw();
            ofPopMatrix();
        }
    }
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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
