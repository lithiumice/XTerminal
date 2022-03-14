#ifndef __HAL_IMU_H__
#define __HAL_IMU_H__ 1
#include "HAL/HAL.h"

// #include "App/quaternions.hpp"
// MPU6050 mpu;//mpu(0x69);
// bool dmpReady = false;
// uint8_t fifoBuffer[64];
// uint8_t mpuIntStatus;
// uint8_t devStatus;
// uint16_t packetSize;
// uint16_t fifoCount;

enum ACTIVE_TYPE
{
    TURN_RIGHT = 0,
    TURN_LEFT,
    TURN_UP,
    TURN_DOWN,
    FORWORD,
    BACKWARD,
    TURN_NONE,
    ACTIVE_TYPE_MAX
};

extern ACTIVE_TYPE mpu_action;
extern uint8_t mpu_act_valid;

#endif // !__HAL_IMU_H__