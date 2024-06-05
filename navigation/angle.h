#pragma once

#include <MPU6050.h>
#include <wiringPi.h>
#include <iostream>

class AngleTracker {
private:
    MPU6050 device;
    float currentAngle;
    unsigned long lastUpdateTime;

    float readGyroZ();
    float integrateGyro(float gyroRate, float dt);

public:
    AngleTracker();
    void setupGyro();
    void updateAngle();
    float getCurrentAngle();
};
