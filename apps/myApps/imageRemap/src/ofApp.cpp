#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ocean.loadImage("ocean.jpg");
    forest.loadImage("forest.jpg");
    
    ocean.resize(ofGetWidth(), ofGetHeight());
    forest.resize(ofGetWidth(), ofGetHeight());
    
//    //check if this is necessary
    
    remapColors(forest, ocean);
    ocean.reloadTexture();
    forest.reloadTexture();

    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    forest.draw(0, 0);
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
//can't use a lambda until OF 1.0
//this can't be in the ofApp. why?
bool compareColors(const ofColor& a, const ofColor& b){
    return a.getBrightness() > b.getBrightness();
}


struct colorCompare

//return a vector of sorted Pixels
std::vector<ofColor> ofApp::sortPixels(const ofImage &source){
    std::vector<ofColor> sorted;
    sorted.reserve(source.width * source.height);
    
    //row - y
    for (int i = 0; i < source.height; ++i) {
        //column - x
        for (int j = 0; j < source.width; ++j) {
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
//may not need this
ofImage ofApp::getSortedImage(ofImage& source){

}


void ofApp::remapColors(const ofImage &source, ofImage &destination){
    typedef std::pair<ofColor, ofColor> colorPair;
    
    std::vector<ofColor> sortedSource = sortPixels(source),
                        sortedDestination = sortPixels(destination);
    
    //map the source and destination colors
    std::map<ofColor, ofColor, compareColors> mappedColors;
    for (int i = 0; i < sortedSource.size(); ++i) {
        mappedColors.insert(colorPair(sortedSource[i].getBrightness(), sortedDestination[i]));
    }
    
    ofPixels destinationPixels = destination.getPixelsRef();
    
    for (int i = 0; i < destination.height; ++i) {
        //column - x
        for (int j = 0; j < destination.width; ++j) {
            destinationPixels.setColor(j, i, mappedColors[destinationPixels.getColor(j, i).getBrightness()]);
        }
    }
    
    //ofImage.reloadTexture is insufficient for some reason
    destination.setFromPixels(destinationPixels);

}