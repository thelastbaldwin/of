//
//  EMScreenCap.cpp
//  colors
//
//  Created by Minor, Steve on 6/6/14.
//
//

#include "EMScreenCap.h"

#define STR(a) #a
#define STRINGIFY(a) STR(a)

namespace EM{
    void takeScreenShot(){
        //save a fullscreen, timestamped jpeg of the current frame
        
        std::stringstream ss;
        
        std::string projectName;
        #ifdef PROJECT_NAME
        projectName = STRINGIFY(PROJECT_NAME);
        #endif
        std::string timeStamp = ofGetTimestampString("%m%d%Y-%H%M%s");
        
        //build filename
        ss << projectName << timeStamp << ".jpg";
        
        ofImage image;
        image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        image.saveImage(ss.str());
    }
}
