#include <pthread.h>
#include <iostream>

#pragma once
class Wheel{
public:
    void move_forward();
    void stop();
    // void rotate(int angle);
};

class Navigate {
private:
    Wheel wheel;
    int distance;
    pthread_t servo_thread, lidar_thread, location_thread;

    bool exitFlag = false;
    bool isInMotion = false;
public:
    ~Navigate();
    void setTime(int x): distance(x) {}
    void* runNavigation();
};
Navigate global_navigation;