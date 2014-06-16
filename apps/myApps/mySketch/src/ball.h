#ifndef ball_h
#define ball_h

#include "ofMain.h"

class Ball{
    public:
        //constructor
        Ball();

        //Methods
        void orbit();
        void draw();
        int getXPosition();
        int getYPosition();

        //Properties
        int x;
        int y;
        int radius;
        float speed;
        float counter;
        ofColor color;
};
#endif
