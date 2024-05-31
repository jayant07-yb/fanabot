#pragma once
class Wheel{
    int leftPin, rightPin;
public:
    Wheel(int leftPin, int rightPin);
    Wheel() {}
    void move_forward();
    void stop();
};
