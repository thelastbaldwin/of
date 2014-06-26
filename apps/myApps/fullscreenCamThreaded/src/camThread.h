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
    ofVideoGrabber 		vidGrabber;
    int 				camWidth;
    int 				camHeight;
    ofPixels         pixels;

    CamThread(int id = 0){
        camWidth = ofGetWidth();
        camHeight = ofGetHeight();

        //this might puke. try hard coded values or static constants from app
        vidGrabber.setDeviceID(id);
        vidGrabber.setDesiredFrameRate(60);
        //false tells us not to use gl textures
        vidGrabber.initGrabber(camWidth,camHeight, false);
    }

    void threadedFunction(){

        while( isThreadRunning() != 0 ){
            vidGrabber.update();

            if(vidGrabber.isFrameNew()){
                lock();
                pixels = vidGrabber.getPixelsRef();
//                seems that gl textures can't be used
//            hCamTex = vidGrabber.getTexture();
//            camTex = vidGrabber.getTextureReference();
                unlock();
            }
        }
    }

};

