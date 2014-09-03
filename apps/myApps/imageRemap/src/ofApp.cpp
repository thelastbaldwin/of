#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ocean.loadImage("ocean.jpg");
    forest.loadImage("forest.jpg");
    colorMap.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    
    ocean.resize(ofGetWidth(), ofGetHeight());
    forest.resize(ofGetWidth(), ofGetHeight());
    
//    remapColors(forest, ocean);
//    ocean.reloadTexture();
//    forest.reloadTexture();
    
//    std::vector<ofColor> sortedForestColors = sortPixels(forest.getPixelsRef());
    
//    //row - y
//    int colorIndex = 0;
//    for (int i = 0; i < forest.getHeight(); ++i) {
//        //column - x
//        for (int j = 0; j < forest.getWidth(); ++j) {
//            forest.setColor(j, i,sortedForestColors[colorIndex]);
//            ++colorIndex;
//        }
//    }
//
//    forest.reloadTexture();
    
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(640, 480, true);
    
    shader.load("shaders/shaderVert.c", "shaders/shaderFrag.c");
    
    //set up quad mesh
    quad.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    quad.addVertex(ofPoint(0, ofGetHeight(), 0));
    quad.addTexCoord(ofPoint(0, ofGetHeight(), 0));
    quad.addVertex(ofPoint(0, 0, 0));
    quad.addTexCoord(ofPoint(0, 0, 0));
    quad.addVertex(ofPoint(ofGetWidth(), ofGetHeight(), 0));
    quad.addTexCoord(ofPoint(ofGetWidth(), ofGetHeight(), 0));
    quad.addVertex(ofPoint(ofGetWidth(), 0, 0));
    quad.addTexCoord(ofPoint(ofGetWidth(), 0, 0));
    
    
    // prefill array with transparent black
    // we'll be mixing colors in the shader
    // and this will allow the original color to come through
    // if necessary
    ofFloatColor transBlack = ofFloatColor(0.0, 0.0, 0.0, 1.0);
    //rows
    for (int i = 0; i < colorMap.getHeight(); ++i) {
        //columns
        for (int j = 0; j < colorMap.getWidth(); ++j) {
            colorMap.getPixelsRef().setColor(j, i, transBlack);
        }
    }

    colorMap.reloadTexture();

}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
   
    ofPixels vidPix = vidGrabber.getPixelsRef();
    
    for (int i = 0; i < colorMap.getHeight(); ++i) {
        //columns
        for (int j = 0; j < colorMap.getWidth(); ++j) {
            ofFloatColor currentColor = vidPix.getColor(j, i);
            //the y value below could be 0, but adding a y value looks crazy!
            colorMap.getPixelsRef().setColor((int)(currentColor.getBrightness() * 255), i, currentColor);
        }
    }
    
//    for (int i = 0; i < colorMap.getHeight(); ++i) {
//        //columns
//        for (int j = 0; j < colorMap.getWidth(); ++j) {
//            ofFloatColor currentColor = forest.getColor(j, i);
//            //the y value below could be 0, but adding a y value looks crazy!
//            colorMap.getPixelsRef().setColor((int)(currentColor.getBrightness() * 255), i, currentColor);
//        }
//    }
    
    colorMap.reloadTexture();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //    goal: get a static image to display with colors from
    //    the webcam
    vidGrabber.getTextureReference().bind();
    shader.begin();
    shader.setUniformTexture("vidGrabber", vidGrabber.getTextureReference(), 1);
    shader.setUniformTexture("mappedColors", colorMap.getTextureReference(), 2);
    
    quad.draw();
    
    shader.end();
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
struct colorCompare{
    bool operator() (const ofColor& lhs, const ofColor& rhs) const
    {
        return lhs.getBrightness() > rhs.getBrightness();
    }
}compareColors;

//return a vector of sorted Pixels
std::vector<ofColor> ofApp::sortPixels(const ofPixels& source){
    std::vector<ofColor> sorted;
    sorted.reserve(source.getWidth() * source.getHeight());
    
    //row - y
    for (int i = 0; i < source.getHeight(); ++i) {
        //column - x
        for (int j = 0; j < source.getWidth(); ++j) {
            sorted.push_back(source.getColor(j, i));
        }
    }
    
    std::sort(sorted.begin(), sorted.end(), compareColors);
    return sorted;
}



//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::remapColors(const ofPixels& source, ofPixels& destination){
    typedef std::pair<ofColor, ofColor> colorPair;
    
    std::vector<ofColor> sSource = sortPixels(source),
                        sDestination = sortPixels(destination);
    
    //map the source and destination colors
    std::map<ofColor, ofColor, colorCompare> mappedColors;
    for (int i = 0; i < sSource.size(); ++i) {
        mappedColors.insert(colorPair(sDestination[i], sSource[i]));
    }

    
    //row - y
    for (int i = 0; i < destination.getHeight(); ++i) {
        //column - x
        for (int j = 0; j < destination.getWidth(); ++j) {
            destination.setColor(j, i, mappedColors[destination.getColor(j, i)]);
        }
    }
    //now need to call setFromPixels or reloadTexture

}