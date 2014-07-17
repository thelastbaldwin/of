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
    std::vector<ofPixels> pixels;

    CamThread(std::vector<int> & videoIds, int width, int height){
        //make sure that we only hold as many pixels as we have cameras
        pixels.resize(videoIds.size());
        
        for (int i : videoIds){
            ofVideoGrabber grabber;
            grabber.setDeviceID(i);
            //at 30fps, will use significantly less bandwidth
            grabber.setDesiredFrameRate(60);
            //the false tells the grabber not to use GL textures
            grabber.initGrabber(width, height, false);
            vidGrabbers.push_back(grabber);
        
        }
    }

    void threadedFunction(){

        while( isThreadRunning() != 0 ){
            for (int i = 0; i < vidGrabbers.size(); ++i){
                vidGrabbers[i].update();
                if(vidGrabbers[i].isFrameNew()){
                    lock();
                    pixels[i] = vidGrabbers[i].getPixelsRef();
                    unlock();
                }
            }
        }
    }
};

