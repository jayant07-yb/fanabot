#include "angle.h"
#include <unistd.h>  // For usleep
#include <chrono>

unsigned long local_mills() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

AngleTracker::AngleTracker()
    : device(0x68), currentAngle(0.0), lastUpdateTime(0) {
    setupGyro();
}

void AngleTracker::setupGyro() {
    sleep(1); // Wait for the MPU6050 to stabilize
    device.calc_yaw = true;
    lastUpdateTime = local_mills();
}

float AngleTracker::readGyroZ() {
    float gr, gp, gz;
    device.getGyro(&gr, &gp, &gz);
    return gz;
}

float AngleTracker::integrateGyro(float gyroRate, float dt) {
    return gyroRate * dt;
}

void AngleTracker::updateAngle() {
    unsigned long currentTime = local_mills();
    float dt = (currentTime - lastUpdateTime) / 1000.0;  // Convert local_millseconds to seconds
    float gyroZ = readGyroZ();
    currentAngle += integrateGyro(gyroZ, dt);
    lastUpdateTime = currentTime;
}

float AngleTracker::getCurrentAngle() {
    return currentAngle;
}
