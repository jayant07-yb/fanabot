#include "navigation.h"
#include "wheel.h"
#include "shmem.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream

using namespace std;

FanaBotInfo* botInfo;
void* read_location(int* remaining_distance) {
    while(!exitFlag){
        usleep(100000); //100 ms
        if (botInfo->isMoving && *remaining_distance > 0){
            *remaining_distance -= 100;
        }
    }
}

void runNavigation()
{
    pthread_t location_thread;
    botInfo->isMoving = true;

    int remaining_distance = 0;
    if (pthread_create(&location_thread, NULL, read_location, &remaining_distance) != 0) {
        std::cerr << "Failed to create location thread" << std::endl;
        return NULL;
    }

    while(botInfo->task.magnitude > 0){
        wheel.move_forward();
        usleep(100000);
    }

    wheel.stop();
    botInfo->isMoving = false;
    botInfo->task.magnitude = 0;
    botInfo->task.task = TaskType::STOP;

    pthread_join(location_thread, NULL);
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
            runNavigation();
        }
        else if (botInfo->task.task == TaskType::STOP)
        {
            
            botInfo->isMoving = true;
            wheel.stop();
        }
        else
        {
            std::cerr << "Invalid task" << std::endl;
        }
    }
}