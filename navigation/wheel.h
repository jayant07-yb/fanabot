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

    const int baseSpeedLeft = 50;  // Base speed for the left wheel (0-100)
    const int baseSpeedRight = 50;  // Base speed for the right wheel (0-100)
    const float correctionFactor = 0.1;  // Factor to adjust the wheel speeds

    MPU6050 mpu;

public:
    Wheel(int leftFrontPin, int leftBackPin, int rightFrontPin, int rightBackPin);
    void move_forward();
    void stop();
    void turn_left();
    void turn_right();
    void setupGyro();
    float readGyro();
};
