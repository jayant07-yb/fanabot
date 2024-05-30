#include <iostream>
#include <bcm2835.h>
#include <pthread.h>
#include <unistd.h>
#include <csignal>
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include "VL53L0X.hpp"

#include "navigation.h"
#include "lidar_reading.h"

Navigate::Navigate(int x, int y) : x_dest(x), y_dest(y) {}

//TODO(janand): Implement this, to ensure that the threads are killed when the object is destroyed
Navigate::~Navigate() {
    //This will kill the threads
    exitFlag = true;
}

void* Naviagte::read_location(){
    while(!exitFlag){
        thread.sleep_for(std::chrono::milliseconds(100));
        if (isInMotion){
            distance -= 100; 
        }
    }
}

int Navigate::runNavigation()
{
    if (pthread_create(&servo_thread, NULL, rotate_servo, &exitFlag) != 0) {
        std::cerr << "Failed to create servo thread" << std::endl;
        return 1;
    }

    if (pthread_create(&lidar_thread, NULL, read_lidar, &exitFlag) != 0) {
        std::cerr << "Failed to create lidar thread" << std::endl;
        return 1;
    }

    if (pthread_create(&location_thread, NULL, read_location, NULL) != 0) {
        std::cerr << "Failed to create location thread" << std::endl;
        return 1;
    }

    while(distance > 0)-{
        wheel.move_forward();
        Thread.sleep(std::chrono::milliseconds(100));
    }

    wheel.stop();
    isInMotion = false;
    exitFlag = true;

    // Wait for threads to finish
    pthread_join(servo_thread, NULL);
    pthread_join(lidar_thread, NULL);
    pthread_join(location_thread, NULL);
}

void Wheel::move_forward(){
    std::cout << "Moving forward\n";
    //TODO(janand): Implement this
}

void Wheel::stop(){
    //TODO(janand): Implement this
    std::cout << "Stopping\n";
}