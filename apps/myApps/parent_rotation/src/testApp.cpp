#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	// link all testNodes (parent to each other)
	for(int i=0; i<kNumTestNodes; i++) {
		if(i>0) testNodes[i].setParent(testNodes[i-1]);
		
		// draw the vertices in pathLines as a line strip
		pathLines[i].setMode(OF_PRIMITIVE_LINE_STRIP);
	}
	
	cam.setPosition(ofVec3f(100, 100, 100));
	cam.lookAt(ofVec3f(0, 0, 0));
	
	pointLight.setPosition(ofVec3f(0, 0, 100));
	pointLight.setPointLight();
}

//--------------------------------------------------------------
void testApp::update(){
	
	float freqMult = 1;
	float amp = 30;
	float scale = 1;
	
	// all testNodes move in simple circles
	// but because they are parented to each other, complex paths emerge
	for(int i=0; i<kNumTestNodes; i++) {
		previous[i] = current[i];
		
		testNodes[i].setPosition(ofVec3f(sin(ofGetElapsedTimef() * freqMult) * amp, cos(ofGetElapsedTimef() * freqMult) * amp, sin(ofGetElapsedTimef() * freqMult * 0.7) * amp));		
		testNodes[i].setOrientation(ofVec3f(sin(ofGetElapsedTimef() * freqMult * 0.2) * amp * 5, cos(ofGetElapsedTimef() * freqMult * 0.2) * amp * 5, sin(ofGetElapsedTimef() * freqMult * 0.2 * 0.7) * amp * 5));
		testNodes[i].setScale(scale);
		
		current[i] = testNodes[i].getGlobalPosition();
		
		//modify variables for next node
		freqMult *= 1;
		amp *= 0.8;
		scale *= 0.8;
		
		// add the current position to the pathVertices deque
		pathVertices[i].push_back(current[i]);
		// if we have too many vertices in the deque, get rid of the oldest ones
		while(pathVertices[i].size() > 1000) {
			pathVertices[i].pop_front();
		}
		
		// clear the pathLines ofMesh from any old vertices
		pathLines[i].clear();
		// add all the vertices from pathVertices
		for(int j = 0; j < pathVertices[i].size(); j++) {
			pathLines[i].addVertex(pathVertices[i][j]);
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0);
	
	cam.begin();
	glEnable(GL_CULL_FACE);
	
	pointLight.enable();
	pointLight.draw();
	
	// draw world axis
	//ofDrawAxis(100);
	
	// draw testNodes
	for(int i=0; i<kNumTestNodes; i++) {
		ofSetColor(255, 128, 255);
		testNodes[i].draw();
		
		//path of the nodes
		ofSetLineWidth(2);
		ofSetColor(100, 100, 255);
		pathLines[i].draw();
	}
	
	//ofSphere(testNodes[0].getPosition(),20); //can use the node in this way
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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