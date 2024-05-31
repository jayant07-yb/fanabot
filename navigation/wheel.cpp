#include "wheel.h"
#include "lidar_reading.h"
#include <iostream>
#include <bcm2835.h>
#include <pthread.h>
#include <unistd.h>
#include <csignal>
#include <wiringPi.h>

Wheel::Wheel(int leftPin, int rightPin)
    : leftPin(leftPin), rightPin(rightPin) {
    // Initialize the GPIO pins
    wiringPiSetupGpio();  // Use GPIO numbering
    pinMode(leftPin, OUTPUT);
    pinMode(rightPin, OUTPUT);
}

void Wheel::move_forward() {
    std::cout << "Moving forward\n";
    digitalWrite(leftPin, HIGH);  // Set the forward pin high
    digitalWrite(rightPin, HIGH);  // Set the backward pin low
}

void Wheel::stop() {
    std::cout << "Stopping\n";
    digitalWrite(leftPin, LOW);  // Set the forward pin low
    digitalWrite(rightPin, LOW);  // Set the backward pin low
}