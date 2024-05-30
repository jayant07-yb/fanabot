#include <pthread.h>

#pragma once
class Wheel{
public:
    void move_forward();
    void stop();
    // void rotate(int angle);
};

class Naviagte{
private:
    Wheel wheel;
    int distance;
    pthread_t servo_thread, lidar_thread, location_thread;

    bool exitFlag = false;
    bool isInMotion = false;
public:
    Naviagte();
    ~Naviagte();
    void* runNavigation(int distance);
};
