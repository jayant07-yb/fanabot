#include <iostream>
#include <bcm2835.h>
#include <pthread.h>
#include <unistd.h>
#include <csignal>
#include "VL53L0X.hpp"

#include "lidar_reading.h"
#include "navigation.h"
using namespace std;
// SIGINT (CTRL-C) exit flag and signal handler
volatile sig_atomic_t exitFlag = 0;
void sigintHandler(int) {
    exitFlag = 1;
}

int main() {
    // Register SIGINT handler
    signal(SIGINT, sigintHandler);

    if (!bcm2835_init()) {
        std::cerr << "Failed to initialize bcm2835" << std::endl;
        return 1;
    }

    bcm2835_gpio_fsel(SERVO_PIN, BCM2835_GPIO_FSEL_OUTP);

    // Initialize VL53L0X
    try {
        sensor.initialize();
        sensor.setTimeout(200);
    } catch (const std::exception& error) {
        std::cerr << "Error initializing sensor: " << error.what() << std::endl;
        return 1;
    }


    runApp();
    bcm2835_close();
    return 0;
}
