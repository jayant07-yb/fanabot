#include "wheel.h"

Wheel::Wheel(int leftFrontPin, int leftBackPin, int rightFrontPin, int rightBackPin)
    : leftFrontPin(leftFrontPin), leftBackPin(leftBackPin),
      rightFrontPin(rightFrontPin), rightBackPin(rightBackPin), lsm() {
    // Initialize the pins for PWM
    softPwmCreate(leftFrontPin, 0, 100);
    softPwmCreate(rightFrontPin, 0, 100);
    pinMode(leftBackPin, OUTPUT);
    pinMode(rightBackPin, OUTPUT);
}

void Wheel::setupGyro() {
    if (!lsm.begin()) {
        std::cerr << "Failed to initialize the gyroscope!" << std::endl;
        exit(1);
    }
    lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
}

float Wheel::readGyro() {
    sensors_event_t gyroEvent;
    lsm.getEvent(&gyroEvent);
    return gyroEvent.gyro.z;
}

void Wheel::move_forward() {
    std::cout << "Moving forward\n";
    
    float angularVelocityZ = readGyro();

    // Adjust the speeds based on the angular velocity
    int adjustedSpeedLeft = baseSpeedLeft - correctionFactor * angularVelocityZ;
    int adjustedSpeedRight = baseSpeedRight + correctionFactor * angularVelocityZ;

    // Ensure speeds are within the 0-100 range
    adjustedSpeedLeft = std::max(0, std::min(100, adjustedSpeedLeft));
    adjustedSpeedRight = std::max(0, std::min(100, adjustedSpeedRight));

    softPwmWrite(leftFrontPin, adjustedSpeedLeft);
    softPwmWrite(rightFrontPin, adjustedSpeedRight);
    digitalWrite(leftBackPin, LOW);
    digitalWrite(rightBackPin, LOW);
}

void Wheel::stop() {
    std::cout << "Stopping\n";
    softPwmWrite(leftFrontPin, 0);
    softPwmWrite(rightFrontPin, 0);
    digitalWrite(leftBackPin, LOW);
    digitalWrite(rightBackPin, LOW);
}

void Wheel::turn_left() {
    std::cout << "Turning left\n";
    softPwmWrite(leftFrontPin, 0);
    softPwmWrite(rightFrontPin, 50);
    digitalWrite(leftBackPin, LOW);
    digitalWrite(rightBackPin, LOW);
}

void Wheel::turn_right() {
    std::cout << "Turning right\n";
    softPwmWrite(leftFrontPin, 50);
    softPwmWrite(rightFrontPin, 0);
    digitalWrite(leftBackPin, LOW);
    digitalWrite(rightBackPin, LOW);
}
