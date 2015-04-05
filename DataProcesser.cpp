//
//  DataProcesser.cpp
//  myonoise
//
//  Created by Tima Peshin on 4/5/15.
//  Copyright (c) 2015 Tima Peshin. All rights reserved.
//

#include <stdio.h>

#include "DataProcesser.h"

Gesture& DataProcesser::analyze(DataAnalyzer<Angles> data) {
    GestureBeat* gb = new GestureBeat();
    return *gb;
}