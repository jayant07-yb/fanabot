#include "wheel.h"
#include <iostream>
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
    digitalWrite(leftPin, HIGH);  // Set the left pin high
    digitalWrite(rightPin, HIGH);  // Set the right pin high
}

void Wheel::stop() {
    std::cout << "Stopping\n";
    digitalWrite(leftPin, LOW);  // Set the left pin low
    digitalWrite(rightPin, LOW);  // Set the right pin low
}
