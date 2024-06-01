#include "wheel.h"
#include "shmem.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

FanaBotInfo* botInfo;
void* read_location(void* remaining_distance_void) {
    int* remaining_distance = static_cast<int*>(remaining_distance_void);
    while(!botInfo->isMoving && *remaining_distance > 0){
        usleep(100000); //100 ms
        if (botInfo->obstacleDetected)
        {
            std::cout << "Obstacle detected\n";
            continue;
        }

        *remaining_distance -= 100;
    }
    return NULL;
}

void runNavigation(Wheel& wheel)
{
    pthread_t location_thread;
    botInfo->isMoving = true;

    int remaining_distance = botInfo->task.magnitude;
    if (pthread_create(&location_thread, NULL, read_location, &remaining_distance) != 0) {
        std::cerr << "Failed to create location thread" << std::endl;
        return;
    }

    while(remaining_distance > 0){
        usleep(100000);  // 100 ms
        if (botInfo->obstacleDetected)
        {
            std::cout << "Obstacle detected\n";
            wheel.stop();
            continue;
        }
        wheel.move_forward();
    }

    wheel.stop();
    botInfo->isMoving = false;
    botInfo->task.magnitude = 0;
    botInfo->task.task = TaskType::STOP;

    pthread_join(location_thread, NULL);
}

void stopNavigation(Wheel& wheel)
{
    wheel.stop();
    botInfo->isMoving = false;
    botInfo->task.magnitude = 0;
    botInfo->task.task = TaskType::STOP;
}

int main() {
    botInfo = initialize_shared_memory();
    Wheel wheel(5, 6);
    wheel.stop();

    while (true)
    {
        // Delay is starting or stopping the value
        usleep(100000); // 100 ms -- Need to decrease this value
        
        if (botInfo->task.task == TaskType::MOVE)
        {
            runNavigation(wheel);
        }
        else if (botInfo->task.task == TaskType::STOP)
        {
            stopNavigation(wheel);
        }
        else
        {
            std::cerr << "Invalid task" << std::endl;
        }
    }
}