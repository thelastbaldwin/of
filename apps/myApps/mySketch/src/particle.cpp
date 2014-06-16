#include "particle.h"

Particle::Particle(){
    //set the initial color
    //color.set(ofRandom(255), ofRandom(255), ofRandom(255));
    color.set(255);

    location.set(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight())); //random start location
    velocity.set(0, 0);
    topspeed = ofRandom(6, 20);
    scalar = 0.5;
}

void Particle::update(){
    //contains pointer to base app variable
    ofVec2f target(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY); //should be able to pass in the vector of the target
    dir = target - location;
    dir.normalize();
    dir *= scalar;
    acceleration = dir;

    velocity += acceleration;
    velocity.limit(topspeed);
    location+=velocity;
}

//essential to pass Ball by reference
void Particle::update(Ball target){
    //contains pointer to base app variable
    ofVec2f t(target.getXPosition(), target.getYPosition()); //should be able to pass in the vector of the target
    dir = t - location;
    dir.normalize();
    dir *= scalar;
    acceleration = dir;
    
    velocity += acceleration;
    velocity.limit(topspeed);
    location+=velocity;
    
}

void Particle::display(){
    ofSetColor(color);
    ofFill();
    ofCircle( location.x, location.y, 1);
}

