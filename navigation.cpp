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
#include "main.h"

#include "navigation.h"
#include "lidar_reading.h"
#include <iostream>
#include <bcm2835.h>
#include <pthread.h>
#include <unistd.h>
#include <csignal>
#include "VL53L0X.hpp"
#include <wiringPi.h>


using namespace std;

Navigate global_navigation;
//TODO(janand): Implement this, to ensure that the threads are killed when the object is destroyed
Navigate::~Navigate() {
    //This will kill the threads
    exitFlag = true;
}

Navigate::Navigate(){
    distance = 0;   
    wheel = Wheel(5, 6);
}

void* Navigate::read_location(){
    while(!exitFlag){
        usleep(100000); //100 ms
        if (isInMotion){
            distance -= 100; 
        }
    }
}

void *read_loc(void* arg){
    global_navigation.read_location();
}

void* Navigate::runNavigation()
{
    if (pthread_create(&servo_thread, NULL, rotate_servo, &exitFlag) != 0) {
        std::cerr << "Failed to create servo thread" << std::endl;
        return NULL;
    }

    if (pthread_create(&lidar_thread, NULL, read_lidar, &exitFlag) != 0) {
        std::cerr << "Failed to create lidar thread" << std::endl;
        return NULL;
    }

    if (pthread_create(&location_thread, NULL, read_loc, NULL) != 0) {
        std::cerr << "Failed to create location thread" << std::endl;
        return NULL;
    }

    while(distance > 0){
        wheel.move_forward();
        usleep(100000);
    }

    wheel.stop();
    isInMotion = false;
    exitFlag = true;

    // Wait for threads to finish
    pthread_join(servo_thread, NULL);
    pthread_join(lidar_thread, NULL);
    pthread_join(location_thread, NULL);
}

Navigate::Navigate(int leftPin, int rightPin)
    : wheel(leftPin, rightPin) {
}


////////////////////////


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