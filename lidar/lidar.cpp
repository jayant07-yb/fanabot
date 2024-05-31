#include <iostream>
#include <bcm2835.h>
#include <pthread.h>
#include <unistd.h>
#include <csignal>
#include "VL53L0X.hpp"
#include "shmem.h"

using namespace std;

#define LEFT_ANGLE 60
#define RIGHT_ANGLE 130
#define SERVO_PIN RPI_GPIO_P1_12  // GPIO 18

VL53L0X sensor;  // Device instance for the VL53L0X

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
    FanaBotInfo* botStatus = static_cast<FanaBotInfo*>(arg);
    while (true) {
        if (!(botStatus->isMoving)) {
            usleep(100000); // 100 ms delay
            continue;
        }

        botStatus->lidarFunctional = true;
        set_servo_angle(LEFT_ANGLE);
        usleep(39000);  // 81ms delay
        set_servo_angle(RIGHT_ANGLE);
        usleep(39000);  // 50ms delay
    }
    return nullptr;
}

// Read distance from the VL53L0X sensor
void* read_lidar(void* arg) {
    FanaBotInfo* botStatus = static_cast<FanaBotInfo*>(arg);
    while (true) {
        if (!(botStatus->isMoving)) {
            usleep(100000);
            continue;
        }

        usleep(50000);  // 50ms delay
        try {
            uint16_t distance = sensor.readRangeSingleMillimeters();
            if (sensor.timeoutOccurred()) {
                std::cerr << "Timeout occurred!" << std::endl;
            } else {
                if (distance < 500) {
                    botStatus->obstacleDetected = true;
                } else {
                    botStatus->obstacleDetected = false;
                }
            }
        } catch (const std::exception& error) {
            std::cerr << "Error getting measurement: " << error.what() << std::endl;
        }
    }
    return nullptr;
}

int main() {
    // Initialize the bcm2835 library
    if (!bcm2835_init()) {
        std::cerr << "Failed to initialize bcm2835 library" << std::endl;
        return 1;
    }

    // Set the servo pin as an output
    bcm2835_gpio_fsel(SERVO_PIN, BCM2835_GPIO_FSEL_OUTP);

    // Initialize the VL53L0X sensor
    sensor.initialize();
    sensor.setTimeout(500);
    sensor.startContinuous();

    // Initialize the shared memory
    FanaBotInfo* fanaBotInfo = initialize_shared_memory();
    if (fanaBotInfo == nullptr) {
        std::cerr << "Failed to initialize shared memory" << std::endl;
        return 1;
    }

    // Create threads
    pthread_t servo_thread, lidar_thread;
    if (pthread_create(&servo_thread, nullptr, rotate_servo, fanaBotInfo) != 0) {
        std::cerr << "Failed to create servo thread" << std::endl;
        return 1;
    }
    if (pthread_create(&lidar_thread, nullptr, read_lidar, fanaBotInfo) != 0) {
        std::cerr << "Failed to create lidar thread" << std::endl;
        return 1;
    }

    // Wait for threads to finish
    pthread_join(servo_thread, nullptr);
    pthread_join(lidar_thread, nullptr);

    // Clean up
    bcm2835_close();
    std::cout << "Exiting..." << std::endl;
    return 0;
}
