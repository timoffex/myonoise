//
//  DataProcesser.h
//  myonoise
//
//  Created by Tima Peshin on 4/5/15.
//  Copyright (c) 2015 Tima Peshin. All rights reserved.
//

#ifndef myonoise_DataProcesser_h
#define myonoise_DataProcesser_h

#include "DataAnalyzer.h"
#include "common.h"

class DataProcesser {
public:
    Gesture analyze(DataAnalyzer<Angles>);
};

#endif
