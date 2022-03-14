#include "Account_Master.h"
#include "HAL/HAL.h"

static Account* actIMU;

void AccountSystem::IMU_Commit(HAL::IMU_Info_t* info)
{
    actIMU->Commit(info, sizeof(HAL::IMU_Info_t));
}

ACCOUNT_INIT_DEF(IMU)
{
    actIMU = account;
}

static Account* actWeather;

void AccountSystem::Weather_Commit(HAL::Weather_Info_t* info)
{
    actWeather->Commit(info, sizeof(HAL::Weather_Info_t));
    actWeather->Publish();
}

ACCOUNT_INIT_DEF(Weather)
{
    actWeather = account;
}