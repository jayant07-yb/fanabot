#include <pthread.h>
#include <iostream>

#pragma once

class Wheel{
    int rightPin, rightPin;
public:
    Wheel(int leftPin, int rightPin);
    void move_forward();
    void stop();
};

class Navigate {
private:
    Wheel wheel;
    int distance;
    pthread_t servo_thread, lidar_thread, location_thread;

    bool exitFlag = false;
    bool isInMotion = false;


public:    
    void *read_location();

    Navigate(int leftPin, int rightPin);
    ~Navigate();
    void setTime(int x) {distance  = x;}
    void* runNavigation();
};

extern Navigate global_navigation;