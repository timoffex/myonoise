//
//  DataProcesser.cpp
//  myonoise
//
//  Created by Tima Peshin on 4/5/15.
//  Copyright (c) 2015 Tima Peshin. All rights reserved.
//

#include <stdio.h>

#include "DataProcesser.h"

// beat patterns are either spikes or edges; adjust sensitivity??
float test_beat[] = {-0.128567,-0.131404,-0.019066,0.147021,0.204086,0.126065,0.106526,0.076327,0.05503,0.024727,0.008506,-0.013855,-0.030347,-0.050455,-0.068329,-0.090588,-0.102469,-0.1132};
float edge[2] = {-1, 1};
float spike[3] = {-1, 2, -1};

bool find_beat(DataAnalyzer<Angles>, Gesture**);
bool find_motion(DataAnalyzer<Angles>, Gesture**);

Gesture* DataProcesser::analyze(DataAnalyzer<Angles> data, int new_samples) {
    Gesture* gb;
    
    if (find_beat(data, &gb))
        return gb;
    else if (find_motion(data, &gb))
        return gb;
    else
        return nullptr;
}

float* inner(float* mask, int mask_length, uint64_t time_scale, DataAnalyzer<Angles> data) {
    int num_elems = static_cast<int>(time_scale / data.get_time_difference());
    
    int elems_delta = num_elems / (mask_length - 1);
    
    float* sums = new float[3];
    sums[0] = sums[1] = sums[2] = 0;
    for (int i = 0; i < mask_length; i++) {
        sums[0] += mask[mask_length-1-i] * data.get_elem_in_past(i*elems_delta).pitch;
        sums[1] += mask[mask_length-1-i] * data.get_elem_in_past(i*elems_delta).roll;
        sums[2] += mask[mask_length-1-i] * data.get_elem_in_past(i*elems_delta).yaw;
    }
    
    return sums;
}

bool find_beat(DataAnalyzer<Angles> data, Gesture** gesture) {
//    static float max = 0;
    float threshold = 0.1;
    // a beat may require up to half a second
    // beat: sudden stop or sudden velocity reversal
    
    float* in = inner(spike, 3, 75000, data);
    
    if (in[0] > threshold || in[2] > threshold) {
        std::cout << in[0] << std::endl << std::flush;
        delete [] in;
        gesture[0] = new GestureBeat();
        ((GestureBeat*)gesture[0])->strength = 13;
        return true;
    }
    
    delete [] in;
    
    return false;
}

bool find_motion(DataAnalyzer<Angles> data, Gesture** gesture) {
    return false;
}