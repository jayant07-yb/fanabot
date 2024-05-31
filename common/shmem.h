#pragma once

enum TaskType {
    MOVE,
    ROTATE,
    STOP
};

#typedef struct FanaBotTask FanaBotTask;
struct FanaBotTask {
    TaskType task;
    int magnitude;
};

#typedef  struct FanaBotInfo FanaBotInfo;
struct FanaBotInfo {
    bool isMoving;
    bool obstucleDetected;
    bool lidarFunctional
    FanaBotTask task;
};

extern FanaBotInfo* initialize_shared_memory();