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

void* read_location(FanaBotInfo* botStatus) {
    while(!exitFlag){
        usleep(100000); //100 ms
        if (isInMotion){
            distance -= 100; 
        }
    }
}


void* Navigate::runNavigation()
{

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

int main() {

}