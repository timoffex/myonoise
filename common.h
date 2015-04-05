//
//  common.h
//  myonoise
//
//  Created by Tima Peshin on 4/5/15.
//  Copyright (c) 2015 Tima Peshin. All rights reserved.
//

#ifndef myonoise_common_h
#define myonoise_common_h

struct Angles {
    float roll, pitch, yaw;
};

enum GestureType {
    Beat, Motion
};

enum Direction {
    Forward, Backward, Left, Right, Up, Down
};

class Gesture {
public:
    virtual ~Gesture() {}
    virtual GestureType type() = 0;
    int get_id() { return g_id; }
protected:
    int g_id;
};

class GestureBeat : public Gesture {
public:
    GestureType type() { return Beat; }
    ~GestureBeat() {}
    
    Direction direction;
    float strength;
};

class GestureMotion : public Gesture {
public:
    GestureType type() { return Motion; }
    ~GestureMotion() {}
    
    Direction direction;
    float rate;
};

#endif
