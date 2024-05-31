#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>

#include "shmem.h"

const int SHM_SIZE = sizeof(FanaBotInfo); // Size of the shared memory segment
#define SHMEM_KEY 1123;

FanaBotInfo* initialize_shared_memory() {
    key_t key = SHMEM_KEY;

    // Create a shared memory segment
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        std::cerr << "shmget error" << std::endl;
        exit(1);
    }

    // Attach to the shared memory segment
    FanaBotInfo *shm = static_cast<FanaBotInfo*>(shmat(shmid, nullptr, 0));
    if (shm == (FanaBotInfo*) -1) {
        std::cerr << "shmat error" << std::endl;
        exit(1);
    }

    // Check if the shared memory segment is initialized
    // TODO:: Need to add a check here
    shm->isMoving = false;
    shm->obstacleDetected = false;
    return shm;
}

