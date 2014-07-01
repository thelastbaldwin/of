//
//  camThread.h
//  fullscreenCamThreaded
//
//  Created by Minor, Steve on 6/23/14.
//
//
#pragma once

#include "ofApp.h"

class CamThread: public ofThread{
public:
    std::vector<ofVideoGrabber> vidGrabbers;
    ofPixels         pixels;

    CamThread(std::vector<int> & videoIds, int width, int height){
        //this might puke. try hard coded values or static constants from app
        
        for (int i : videoIds){
            ofVideoGrabber grabber;
            grabber.setDeviceId(i);
            grabber.setDesiredFrameRate(60);
            grabber.initGrabber(width, height, false);
            vidGrabbers.push_back(grabber);
        
        }
    }

    void threadedFunction(){

        while( isThreadRunning() != 0 ){
            vidGrabber.update();

            if(vidGrabber.isFrameNew()){
                lock();
                pixels = vidGrabber.getPixelsRef();
                unlock();
            }
        }
    }

};

