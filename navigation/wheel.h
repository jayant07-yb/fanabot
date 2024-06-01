#pragma once

class Wheel{
    int leftFrontPin;
    int leftBackPin;
    int rightFrontPin;
    int rightBackPin;
public:
    Wheel(int leftFrontPin, int leftBackPin, int rightFrontPin, int rightBackPin);
    Wheel() {}
    void move_forward();
    void stop();
};
