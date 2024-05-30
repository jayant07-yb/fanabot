#include "VL53L0X.hpp"

#pragma once

#define LEFT_ANGLE 60
#define RIGHT_ANGLE 130
#define SERVO_PIN RPI_GPIO_P1_12  // GPIO 18

VL53L0X sensor;  // Device instance for the VL53L0X

extern void* rotate_servo(void* arg);
extern void* read_lidar(void* arg);

