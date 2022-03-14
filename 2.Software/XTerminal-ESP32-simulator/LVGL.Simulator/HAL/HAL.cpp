#include "HAL.h"
// using namespace HAL;


bool HAL::wifi_isconnected()
{
    return 1;
}

void HAL::Init()
{
    HAL::Buzz_init();
    HAL::Audio_Init();
    // GPS_Init();
}

void HAL::Update()
{
    IMU_Update();
    __IntervalExecute(Weather_Update(), 5000);
    HAL::Audio_Update();
}
