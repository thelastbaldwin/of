#ifndef particle_h
#define particle_h

#include "ofMain.h"

class Particle{
    public:
    Particle(); // default constructor
    Particle(int homeX, int homeY, int targetX, int targetY); //real constructor

    //methods
    void update(); //update the position of the particle
    void display(); //draw the particle
    void blowAway(float force); //move away from home
    void comeBack(); //return to the origin


    //properties
    ofVec2f location; //current location
    ofVec2f velocity;
    ofVec2f acceleration;
    ofVec2f target;
    ofVec2f dir; //used to calculate the direction of the particle
    ofVec2f home;
    float scalar;
    float topspeed;
    unsigned static int score; //share accross instances

    private:
    //flags to determine whether to add vertical vector
    bool firstBlow;
    bool firstComingBack;
    bool atHome;
    bool atTarget;
    float minDist;    
    
};

int genParticleXRange();
int genParticleYRange();

#endif
