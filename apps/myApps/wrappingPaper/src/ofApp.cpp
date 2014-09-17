#include "ofApp.h"

//require a default constructor because we're allocating memory in the header
ofApp::TrippyQuad::TrippyQuad():rotOffset(0.0), amplitude(0.0){};
ofApp::TrippyQuad::TrippyQuad(float _rotOffset, float _amplitude, float _speed):rotOffset(_rotOffset), amplitude(_amplitude), speed(_speed){};

//--------------------------------------------------------------
void ofApp::setup(){
    
    quadWidth = ofGetWidth() / columns;
    quadHeight = ofGetHeight() / rows;
    padding = quadWidth * 0.15;
    
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
    
//    quad.addVertex(ofPoint(0 - (quadWidth + padding)/2, quadHeight + padding - (quadHeight + padding)/2, 0));
//    quad.addTexCoord(ofPoint(0 - (quadWidth + padding)/2, quadHeight + padding - (quadHeight + padding)/2, 0));
//    quad.addVertex(ofPoint(0 - (quadWidth + padding)/2, 0 - (quadHeight + padding)/2, 0));
//    quad.addTexCoord(ofPoint(0 - (quadWidth + padding)/2, 0 - (quadHeight + padding)/2, 0));
//    quad.addVertex(ofPoint(quadWidth + padding - (quadWidth + padding)/2, quadHeight + padding - (quadHeight + padding)/2, 0));
//    quad.addTexCoord(ofPoint(quadWidth + padding - (quadWidth + padding)/2, quadHeight + padding - (quadHeight + padding)/2, 0));
//    quad.addVertex(ofPoint(quadWidth + padding - (quadWidth + padding)/2, 0 - (quadHeight + padding)/2, 0));
//    quad.addTexCoord(ofPoint(quadWidth + padding - (quadWidth + padding)/2, 0 - (quadHeight + padding)/2, 0));
    
    quad.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    //allocate memory for frame buffer object
    fbo.allocate(quadWidth + padding, quadHeight + padding);
}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::draw(){
    float speed = ofDist(0, 0, 0, ofGetMouseY()),
    lineThickness = ofDist(0, 0, 0, ofGetMouseX());
    
    //generate texture in FBO
    fbo.begin();
    textureShader.begin();
    textureShader.setUniform1f("time", time);
    textureShader.setUniform1f("speed", speed);
    textureShader.setUniform1f("lineThickness", lineThickness);
    ofBackground(255, 0, 0);
    ofPushMatrix();
//    ofTranslate((quadWidth + padding)/2, (quadHeight + padding)/2, 0);
    quad.draw();
    ofPopMatrix();
    textureShader.end();
    fbo.end();

//    fbo.draw(0, 0);
    
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
    
    //ofSetColor(ofColor::black);
    //ofFill();
    std::stringstream ss;
    
    ss << "line width: " << lineThickness << ", speed: " << speed << endl;
    ofDrawBitmapString(ss.str(), ofPoint(ofGetWidth() - 250, ofGetHeight() - 5));
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
