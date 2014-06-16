//
//  EMScreenCap.h
//  colors
//
//  Created by Minor, Steve on 6/6/14.
//
//

#pragma once

#include "ofImage.h"
#include "ofUtils.h"
#include "ofAppRunner.h"
#include <exception>
#include <sstream>

#define STR(a) #a
#define STRINGIFY(a) STR(a)

namespace EM{
    void takeScreenShot();
}
    
