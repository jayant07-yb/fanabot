#include "wheel.h"
#include "map.h"
#include "shmem.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <utility>


using namespace std;

int remaining_distance = 0;

FanaBotInfo* botInfo;
void* read_location(void* remaining_distance_void) {
    while(botInfo->isMoving && remaining_distance > 0){
        usleep(100000); //100 ms
        if (botInfo->obstacleDetected)
        {
            std::cout << "Obstacle detected\n";
            continue;
        }

        remaining_distance -= 100;
    }
    return NULL;
}

void moveStraightLine(Wheel& wheel)
{
    pthread_t location_thread;
    botInfo->isMoving = true;

    remaining_distance = botInfo->task.magnitude;
    if (pthread_create(&location_thread, NULL, read_location, &remaining_distance) != 0) {
        std::cerr << "Failed to create location thread" << std::endl;
        return;
    }

    while(remaining_distance > 0) {
        usleep(100000);  // 100 ms
        if (botInfo->obstacleDetected)
        {
            std::cout << "Obstacle detected\n";
            wheel.stop();
            continue;
        }
        wheel.move_forward();

        std::cout << "Remaining distance: " << remaining_distance << std::endl;
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
    botInfo->task.task = CommandType::STOP;
}

void goToLocation(Wheel& wheel, pair<int, int> coordinates)
{
    std::vector<WheelCommands> commands = getRoute(coordinates);
    for (auto command : commands)
    {
        switch (command.type)
        {
        case CommandType::MOVE:
            moveStraightLine(wheel);
            break;
        case CommandType::ROTATE_LEFT:
            wheel.turn_left();
            break;
        case CommandType::ROTATE_RIGHT:
            wheel.turn_right();
            break;
        case CommandType::STOP:
            stopNavigation(wheel);
            break;
        default:
            std::cerr << "Invalid command" << std::endl;
            break;
        }
    }

}

void setupGyro() {
    if (!lsm.begin()) {
        std::cerr << "Failed to initialize the gyroscope!" << std::endl;
        exit(1);
    }
    lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
}

int main() {
    botInfo = initialize_shared_memory();
    Wheel wheel(27, 22, 5, 6);
    wheel.setupGyro();
    wheel.stop();
    while (true)
    {
        // Delay is starting or stopping the value
        usleep(100000); // 100 ms -- Need to decrease this value
        
        if (botInfo->task.task == TaskType::MOVE)
        {
            // goToLocation(wheel, {0, 0}); // Dummy coordinates
            moveStraightLine(wheel);
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