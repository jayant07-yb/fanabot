#include <iostream>
#include <bcm2835.h>
#include <pthread.h>
#include <unistd.h>
#include <csignal>
#include "VL53L0X.hpp"

#define LEFT_ANGLE 45
#define RIGHT_ANGLE 135

#define SERVO_PIN RPI_GPIO_P1_12  // GPIO 18

VL53L0X sensor;  // Device instance for the VL53L0X

// SIGINT (CTRL-C) exit flag and signal handler
volatile sig_atomic_t exitFlag = 0;
void sigintHandler(int) {
    exitFlag = 1;
}

void set_servo_angle(int angle) {
    int pulse_width = 1000 + (angle * 1000) / 180;  // Calculate pulse width for the angle
    bcm2835_gpio_write(SERVO_PIN, HIGH);
    bcm2835_delayMicroseconds(pulse_width);
    bcm2835_gpio_write(SERVO_PIN, LOW);
    bcm2835_delayMicroseconds(20000 - pulse_width);  // Each pulse is 20ms
}

void* rotate_servo(void* arg) {
    while (!exitFlag) {
        //Move the servo from 0 to 180 degrees
        set_servo_angle(LEFT_ANGLE);
        usleep(50000);  // 50ms delay
        //Move the servo from 180 to 0 degrees
        set_servo_angle(RIGHT_ANGLE);
        usleep(50000);  // 50ms delay
    }
    return NULL;
}

void* read_lidar(void* arg) {
    while (!exitFlag) {
        uint16_t distance;
        try {
            distance = sensor.readRangeSingleMillimeters();
        } catch (const std::exception & error) {
            std::cerr << "Error getting measurement: " << error.what() << std::endl;
            distance = 8096; // Error code
        }

        if (sensor.timeoutOccurred()) {
            std::cout << "Timeout occurred!" << std::endl;
        } else {
            if (distance < 500)
                std::cout << "Distance too close: " << distance << " mm" << std::endl;
        }

    }
    return NULL;
}

int main() {
    // Register SIGINT handler
    signal(SIGINT, sigintHandler);

    if (!bcm2835_init()) {
        return 1;
    }

    bcm2835_gpio_fsel(SERVO_PIN, BCM2835_GPIO_FSEL_OUTP);

    // Initialize VL53L0X
    try {
        sensor.initialize();
        sensor.setTimeout(200);
    } catch (const std::exception & error) {
        std::cerr << "Error initializing sensor: " << error.what() << std::endl;
        return 1;
    }

    pthread_t servo_thread, lidar_thread;

    pthread_create(&servo_thread, NULL, rotate_servo, NULL);
    pthread_create(&lidar_thread, NULL, read_lidar, NULL);

    pthread_join(servo_thread, NULL);
    pthread_join(lidar_thread, NULL);

    bcm2835_close();
    return 0;
}
