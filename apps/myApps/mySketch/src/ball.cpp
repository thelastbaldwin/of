#include "ball.h"

Ball::Ball(){
    //set the initial color
    color.set(ofRandom(255), ofRandom(255), ofRandom(255));
    
    //counter TODO: make this exist in the main app
    counter = 0.0;
    
    speed = 0.008;
    
    radius = ofGetWindowWidth()/4;

    //initial x position of the ball - center
    x = ofGetWindowWidth()/2;

    //initial y position of the ball - center
    y = ofGetWindowHeight()/2;

}

void Ball::orbit(){    
    
    //update x and y to create an orbit effect the center of the screen
    x = ofGetWindowWidth()/2 + radius * cos(counter);
    y = ofGetWindowHeight()/2 + radius * sin(counter);
    
    std::cout << counter<< std::endl;
    
    //increment counter
    counter += speed;
    
    this->draw(); //hopefully refer to ball
    
}

int Ball::getXPosition(){
    return x;
}

int Ball::getYPosition(){
    return y;
}

void Ball::draw(){
    ofSetColor(ofColor::black);
    //ofFill(255); //no fill?
    ofCircle( x, y, 30);
}
