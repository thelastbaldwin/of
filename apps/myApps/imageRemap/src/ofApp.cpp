#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ocean.loadImage("ocean.jpg");
    forest.loadImage("forest.jpg");
    
    ocean.resize(ofGetWidth(), ofGetHeight());
    forest.resize(ofGetWidth(), ofGetHeight());
    
    remapColors(forest, ocean);
    ocean.reloadTexture();
    forest.reloadTexture();
    
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
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
        ocean.draw(0, 0);
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