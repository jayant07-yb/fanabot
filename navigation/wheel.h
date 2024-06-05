#pragma once

#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include "MPU6050.h"

class Wheel {
    int leftFrontPin;
    int leftBackPin;
    int rightFrontPin;
    int rightBackPin;

    const int baseSpeed = 50;  // Base speed for turning
    const float correctionFactor = 0.1;  // Factor to adjust the wheel speeds

    MPU6050 device;

public:
    Wheel(int leftFrontPin, int leftBackPin, int rightFrontPin, int rightBackPin);
    void move_forward();
    void stop();
    void turn_left();
    void turn_right();
    void setupGyro();
    float readGyro();
    float readYaw();
};
