#include "wheel.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <csignal>
#include <wiringPi.h>

Wheel::Wheel(int leftFrontPin, int leftBackPin, int rightFrontPin, int rightBackPin)
    : leftBackPin(leftBackPin), rightBackPin(rightBackPin), leftFrontPin(leftFrontPin), rightFrontPin(rightFrontPin) {
    // Initialize the GPIO pins
    wiringPiSetupGpio();  // Use GPIO numbering
    pinMode(leftFrontPin, OUTPUT);
    pinMode(leftBackPin, OUTPUT);
    pinMode(rightFrontPin, OUTPUT);
    pinMode(rightBackPin, OUTPUT);
}

void Wheel::move_forward() {
    std::cout << "Moving forward\n";
    digitalWrite(leftBackPin, LOW);  // Set the left back pin low
    digitalWrite(rightBackPin, LOW);  // Set the right back pin low
    digitalWrite(leftFrontPin, HIGH);  // Set the left front pin high
    digitalWrite(rightFrontPin, HIGH);  // Set the right front pin high
}

void Wheel::stop() {
    std::cout << "Stopping\n";
    digitalWrite(leftBackPin, LOW);  // Set the left back pin low
    digitalWrite(rightBackPin, LOW);  // Set the right back pin low
    digitalWrite(leftFrontPin, LOW);  // Set the left front pin low
    digitalWrite(rightFrontPin, LOW);  // Set the right front pin low
}

