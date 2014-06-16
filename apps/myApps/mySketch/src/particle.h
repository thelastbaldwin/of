#ifndef particle_h
#define particle_h

#include "ofMain.h"
#include "ball.h"

class Particle{

    public:
    //constructor
    Particle();

    //methods
    void update(); //update the position of the particle
    void update(Ball target);
    void display(); //draw the particle

    private:
    //properties
    //vectors will be converted to 3D vectors in final phase
    ofVec2f location;
    ofVec2f velocity;
    ofVec2f acceleration;
    ofVec2f dir; //used to calculate the direction of the particle
    float scalar;
    float topspeed;

    ofColor color; //final particle should probably glow or something
};

#endif
