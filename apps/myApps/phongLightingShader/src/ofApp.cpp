#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    hideGui = false;
    
    pointLight = ofLight();
    material = ofMaterial();
    
    gui.setup();
    gui.add(radius.setup("radius", 100, 10, 300));
    gui.add(sphereResolution.setup("resolution", 5, 3, 90));
    gui.add(sphereCenter.setup("center",ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0),
                                        ofVec3f(-ofGetWidth(), -ofGetHeight(), -100),
                                        ofVec3f(ofGetWidth(), ofGetHeight(), 100)));

    
    gui.add(lightPosition.setup("light position", ofVec3f(ofGetWidth()/2 + 100, ofGetWidth()/2 + 100, 500),
                                                ofVec3f(-ofGetWidth(), -ofGetHeight(), -500),
                                                ofVec3f(ofGetWidth(), ofGetHeight(), 500)));
    gui.add(diffuseLightColor.setup("diffuse light color", ofColor(100, 0),
                                                    ofColor(0),
                                                    ofColor(255)));
    gui.add(specularLightColor.setup("specular light color", ofColor(100),
                                    ofColor(0),
                                    ofColor(255)));
    
    gui.add(ambientLightColor.setup("ambient light color", ofColor(50, 50, 50),
                                     ofColor(0),
                                     ofColor(255)));
    
    gui.add(applyMaterial.setup("apply material", true));

    gui.add(diffuseMaterialColor.setup("diffuse material color", ofColor(100),
                                       ofColor(0),
                                       ofColor(255)));
    gui.add(specularMaterialColor.setup("specular material color", ofColor(255),
                                       ofColor(0),
                                       ofColor(255)));
    gui.add(ambientMaterialColor.setup("ambient material color", ofColor(255),
                                        ofColor(0),
                                        ofColor(255)));
    //confirmed that this must be > 0 and <= 128
    gui.add(shininess.setup("shininess", 50.0, 0.1, 128.0));
    
    //this is part of the default constructor;
    pointLight.setPointLight();
}

//--------------------------------------------------------------
void ofApp::update(){
    //update attributes of light, material and sphere
    sphere.setRadius(radius);
    sphere.setResolution(sphereResolution);
    sphere.setPosition(sphereCenter);
    
    
    ofColor dmColor = diffuseMaterialColor;
    //no conversion from ofxColorSlider to ofFloatColor
    material.setDiffuseColor(dmColor);
    ofColor smColor = specularMaterialColor;
    material.setSpecularColor(smColor);
    material.setShininess(shininess);
    ofColor ambColor = ambientMaterialColor;
    material.setAmbientColor(ambColor);
    
    pointLight.setPosition(lightPosition);
    ofColor dlColor = diffuseLightColor;
    pointLight.setDiffuseColor(dlColor);
    ofColor slColor = specularLightColor;
    pointLight.setSpecularColor(slColor);
    ofColor ambLColor = ambientLightColor;
    pointLight.setAmbientColor(ambLColor);
    
    pointLight.lookAt(sphereCenter);
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    ofEnableLighting();
    ofEnableDepthTest();


    pointLight.enable();
    pointLight.draw();
    
    //somehow this allows the light color and material color to blend
    glDisable(GL_COLOR_MATERIAL);
    if(applyMaterial){
        material.begin();
    }
    
    sphere.draw();
    
    pointLight.disable();
    if(applyMaterial){
        material.end();
    }
    ofDisableDepthTest();
    ofDisableLighting();
    fbo.end();

    //prevents strange layering of gui
    fbo.draw(0, 0);
    if(!hideGui){
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    hideGui = !hideGui;
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
