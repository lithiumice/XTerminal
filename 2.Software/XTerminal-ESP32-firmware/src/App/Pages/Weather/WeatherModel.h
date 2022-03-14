#ifndef __Weather_MODEL_H
#define __Weather_MODEL_H

#include "lvgl.h"
#include "HAL/HAL.h"
#include "App/Utils/AccountSystem/Account.h"

namespace Page
{

class WeatherModel
{
public:
    void Init();
    void DeInit();

    void GetWeather();
    void GetWeatherInfo();
    void GetWeatherInfo(HAL::Weather_Info_t* info);

    void GetTimeStamp();
    void GetRTCTime();
    void GetDailyWeather();

    uint32_t TickSave;
    uint32_t GetData();
// private:
    Account* account;
    HAL::Weather_Info_t info;
    int data_reved_flag = 0;

};

}

#endif
