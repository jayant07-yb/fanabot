#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>

#include "shared.h"

const int SHM_SIZE = sizeof(FanaBotInfo); // Size of the shared memory segment
#define SHMEM_KEY = 1123

FanaBotInfo* initialize_shared_memory() {
    key_T key = SHMEM_KEY;

    // Create a shared memory segment
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666)
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
    if (std::strlen(shm) == 0) {
        shm->isMoving = false;
        shm->obstucleDetected = false;
    } else {
        std::cout << "Shared memory segment already initialized with message: " << shm << std::endl;
    }
    return shm;
}

