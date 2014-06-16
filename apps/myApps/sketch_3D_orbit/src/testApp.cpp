#include "testApp.h"
#include <math.h>

#define kMoveInc 10

//--------------------------------------------------------------
void testApp::setup(){
    // this uses depth information for occlusion
	// rather than always drawing things on top of each other
    glEnable(GL_DEPTH_TEST);
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetLineWidth(2);
    ofEnableNormalizedTexCoords();
    
    tRing = Ring(6, 15, 3, 2, 0.0, 0.0, 1.0); //(int _count, int _radius, int _speed, int _size, float xRot, float yRot, float zRot)
    
    layers[0] = Ring(6, 15, 3, 2, 0, 0, 1); //int _count, int _radius, int _speed, int _size, int xRot, int yRot, int zRot
    layers[1] = Ring( 30, 50, 1, 5, 0, 1, 0);
    layers[2] = Ring(8, 58, 2, 3, 1, 0, 1);
    layers[3] = Ring(12, 70, -1, 4, 1, 1, 0);
    layers[4] = Ring(15, 80, -2, 5, 1,1 , 1);
    
    cam.setPosition(145, 145, 145);
    cam.lookAt(ofVec3f(0, 0, 0));
    
    for(int i = 0; i < kNumLights; i++) {
		light[i].enable();
	}
    
    //directional light 1
    light[0].setPosition(100,0,0);
    light[0].setDirectional();
    light[0].setDiffuseColor(ofColor(255, 255 , 0));
    light[0].lookAt(ofVec3f(0, 0, 0));
    
    //directional light 2
    light[1].setPosition(0, 100, 0);
    light[1].setDirectional();
    light[1].setDiffuseColor(ofColor(ofGetWidth()/2, ofGetHeight()/2, 200));
    light[1].lookAt(ofVec3f(0,0,0));
    
    //specular light 1
    /*light[2].setPosition(150, 150, 150);
    light[2].setPointLight();
    light[2].setSpecularColor(ofColor(255, 255, 255));*/
    
    //material setup
    mat.setShininess(500.0);
    mat.setSpecularColor(ofColor(183, 224, 255));
    mat.setEmissiveColor(ofColor(10, 10, 0));
}

//--------------------------------------------------------------
void testApp::update(){
    Ring::counter++;
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    
    
    cam.begin();
    //cam.setTarget(ofVec3f(0, 0, 0)); //default
    //cam.draw();
    
    ofSetColor(255);
    ofBox(0, 0, 0, 10);
    
    light[0].enable();
    light[1].enable();
    
    light[0].draw();
    light[1].draw();
    
    mat.begin();
        
    //ofSetColor(255);

    ofSetColor(175);
    tRing.display();
    layers[0].display();
    layers[1].display();
    layers[2].display();
    layers[3].display();
    layers[4].display();
    mat.end();
    ofDisableLighting();
    
    drawAxes();
    
    
    
    //draw line from camera to origin - right now this never really appears because the view is dead on
    ofSetColor(255);
    glBegin(GL_LINES);
    ofVec3f v1 = cam.getGlobalPosition();
    ofVec3f v2; //origin
    
    cout << "Camera position = " << v1 << endl;
    cout << "vs = " << v2 << endl;
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glEnd();
    
    
    cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    ofNode *n = &cam;
    
    switch(key){
        case 'a': n->truck(-kMoveInc); break;
        case 'd': n->truck(kMoveInc); break;
            
        case 'w': n->dolly(-kMoveInc); break;
        case 's': n->dolly(kMoveInc); break;
            
        case 'r': n->boom(kMoveInc); break;
        case 'f': n->boom(-kMoveInc); break;
    }
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

void testApp::drawAxes(){
    //draw the x/y/z axes
    ofSetColor(255, 0, 0); //R - X axis
    ofLine(-50, 0, 0, 50, 0, 0);
    
    ofSetColor(0, 255, 0); //G - Z axis
    ofLine(0, 0, -50, 0, 0, 50);
    
    ofSetColor(0, 0, 255); //B - Y axis
    ofLine(0, -50, 0, 0, 50, 0);    
}

//--------------  RING CLASS  ----------------------------------
Ring::Ring(){
    //default constructor
    
}


Ring::Ring(int _count, int _radius, int _speed, int _size, float xRot, float yRot, float zRot){
    count = _count;
    radius = _radius;
    speed = _speed;
    size = _size;
    setRotation(xRot, yRot, zRot);
}

float Ring::counter = 0.0;

void Ring::setRotation(float x, float y, float z){
    rotation[0] = x;
    rotation[1] = y;
    rotation[2] = z;
}

void Ring::update(){
    ofRotate(Ring::counter * speed,rotation[0],rotation[1],rotation[2]);
}
void Ring::display(){
    ofPushMatrix();
    update();
    for(int i=0; i < count; i++){
        ofPushMatrix();
        //ofTranslate(radius * sin((i* TWO_PI)/count), radius * cos((i* TWO_PI)/count), 0);
        ofSphere(radius * sin((i* TWO_PI)/count), radius * cos((i* TWO_PI)/count), size);
        ofPopMatrix();
    }
    ofPopMatrix();
}
