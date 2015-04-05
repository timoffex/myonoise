//
//  Synthesizer.h
//  myonoise
//
//  Created by Tima Peshin on 4/5/15.
//  Copyright (c) 2015 Tima Peshin. All rights reserved.
//

#ifndef myonoise_Synthesizer_h
#define myonoise_Synthesizer_h

#include "CFugueLib.h"
#include "common.h"

// In theme of happy => C major and D major
class Synthesizer {
public:
    // Takes Gesture and does _____
    void incorporate(Gesture g);
private:
    //A sin(wt + j)
    int tempo; // number of beating gestures
    int beats; // number of beats within a time range
};


#endif
