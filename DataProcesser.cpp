//
//  DataProcesser.cpp
//  myonoise
//
//  Created by Tima Peshin on 4/5/15.
//  Copyright (c) 2015 Tima Peshin. All rights reserved.
//

#include <stdio.h>

#include "DataProcesser.h"


bool find_beat(DataAnalyzer<Angles>, Gesture*);
bool find_motion(DataAnalyzer<Angles>, Gesture*);

// a beat may require up to half a second
// beat: sudden stop or sudden velocity reversal

Gesture* DataProcesser::analyze(DataAnalyzer<Angles> data, int new_samples) {
    Gesture* gb;
    
    if (find_beat(data, gb))
        return gb;
    else if (find_motion(data, gb))
        return gb;
    else
        return gb;
}

bool find_beat(DataAnalyzer<Angles> data, Gesture* gesture) {
    return false;
}

bool find_motion(DataAnalyzer<Angles> data, Gesture* gesture) {
    return false;
}