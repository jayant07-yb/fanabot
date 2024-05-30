#include <iostream>
#include <bcm2835.h>
#include <pthread.h>
#include <unistd.h>
#include <csignal>
#include "VL53L0X.hpp"

#include "lidar_reading.h"

// Calculate pulse width for the given angle
static inline int calculate_pulse_width(int angle) {
    return 1000 + (angle * 1000) / 180;
}

// Set the servo to the specified angle
static inline void set_servo_angle(int angle) {
    int pulse_width = calculate_pulse_width(angle);
    bcm2835_gpio_write(SERVO_PIN, HIGH);
    bcm2835_delayMicroseconds(pulse_width);
    bcm2835_gpio_write(SERVO_PIN, LOW);
    bcm2835_delayMicroseconds(20000 - pulse_width);  // Each pulse is 20ms
}

// Rotate the servo between LEFT_ANGLE and RIGHT_ANGLE
void* rotate_servo(void* arg) {
    bool *exitFlag;
    exitFlag = static_cast<bool*>(arg);
    while (!exitFlag) {
        set_servo_angle(LEFT_ANGLE);
        usleep(39000);  // 81ms delay
        set_servo_angle(RIGHT_ANGLE);
        usleep(39000);  // 50ms delay
    }
    return NULL;
}

// Read distance from the VL53L0X sensor
void* read_lidar(void* arg) {
    bool *exitFlag;
    exitFlag =  static_cast<bool*>(arg);

    while (!exitFlag) {
        try {
            uint16_t distance = sensor.readRangeSingleMillimeters();
            if (sensor.timeoutOccurred()) {
                std::cerr << "Timeout occurred!" << std::endl;
            } else {
                if (distance < 500) {
                    std::cout << "Distance too close: " << distance << " mm" << std::endl;
                }
            }
        } catch (const std::exception& error) {
            std::cerr << "Error getting measurement: " << error.what() << std::endl;
        }
    }
    return NULL;
}


