#include "wheel.h"
#include "angle.h"
#include <unistd.h>  // For usleep
#include <iostream>  // For std::cout

Wheel::Wheel(int leftFrontPin, int leftBackPin, int rightFrontPin, int rightBackPin)
    : leftFrontPin(leftFrontPin), leftBackPin(leftBackPin),
      rightFrontPin(rightFrontPin), rightBackPin(rightBackPin){
    
    wiringPiSetupGpio();  // Use GPIO numbering
    pinMode(leftFrontPin, OUTPUT);
    pinMode(leftBackPin, OUTPUT);
    pinMode(rightFrontPin, OUTPUT);
    pinMode(rightBackPin, OUTPUT);
}

void Wheel::setupGyro() {
    sleep(1); // Wait for the MPU6050 to stabilize
    // Optionally calculate offsets here if needed
    // device.calc_yaw = true;
}

float Wheel::readYaw() {
    float yaw;
    // device.getAngle(2, &yaw);  // Yaw axis is 2
    return yaw;
}

void Wheel::move_forward() {
    std::cout << "Moving forward " << leftFrontPin << " " << rightFrontPin << std::endl ;

    digitalWrite(leftFrontPin, HIGH);
    digitalWrite(rightFrontPin, HIGH);
    digitalWrite(leftBackPin, LOW);
    digitalWrite(rightBackPin, LOW);
}

void Wheel::stop() {
    std::cout << "Stopping\n";
    digitalWrite(leftFrontPin, LOW);
    digitalWrite(rightFrontPin, LOW);
    digitalWrite(leftBackPin, LOW);
    digitalWrite(rightBackPin, LOW);
}

void Wheel::turn_left() {
    std::cout << "Turning left\n";
    float initialYaw = readYaw();
    float targetYaw = initialYaw - 90.0;

    if (targetYaw < -180.0) {
        targetYaw += 360.0;
    }

    digitalWrite(leftFrontPin, LOW);
    digitalWrite(leftBackPin, HIGH);
    digitalWrite(rightFrontPin, HIGH);
    digitalWrite(rightBackPin, LOW);

    while (true) {
        float currentYaw = readYaw();
        if ((initialYaw >= 0 && targetYaw <= currentYaw && currentYaw <= initialYaw) ||
            (initialYaw < 0 && targetYaw <= currentYaw) ||
            (initialYaw >= 0 && targetYaw < -180 && currentYaw < 0)) {
            break;
        }
        usleep(10000);  // Sleep for 10ms
    }

    stop();
}

void Wheel::turn_right() {
    std::cout << "Turning right\n";

    digitalWrite(leftFrontPin, HIGH);
    digitalWrite(leftBackPin, LOW);
    digitalWrite(rightFrontPin, LOW);
    digitalWrite(rightBackPin, HIGH);

    delay(300); //sleep for 300ms and hope that the bot has turned 90 degrees
    stop();
}
