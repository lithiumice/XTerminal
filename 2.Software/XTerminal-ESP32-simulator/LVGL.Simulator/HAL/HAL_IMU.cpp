#include "HAL/HAL_IMU.h"
#include <stdlib.h>
#include "App/Accounts/Account_Master.h"
namespace HAL {
    HAL::Config_t config;
    uint8_t wifi_name_passswd;
    uint8_t clock_url_get_sucess_flag;
    uint8_t weather_url_get_sucess_flag;
    uint8_t enc_btn_first_push_flag;
    uint8_t game_select_index;
    Weather_Info_t weaInfo;
    TimeStamp_t time_stamp_info;
    Time_str_t time_info;
}

ACTIVE_TYPE mpu_action = ACTIVE_TYPE_MAX;
uint8_t mpu_act_valid = 0;
HAL::IMU_Info_t imuInfo;
uint8_t enc_long_push_flag = 0;

void HAL::IMU_Init()
{
}
void notifyUrlThread()
{
    
}
uint32_t HAL::Backlight_GetValue()
{
    return 500;
}
void HAL::Backlight_SetValue(int target_val)
{
    
}

void HAL::IMU_Update()
{
    IMU_Info_t imuInfo;

    imuInfo.ax = rand() % 1000 - 500;
    imuInfo.ay = rand() % 1000 - 500;
    imuInfo.az = rand() % 1000 - 500;
    imuInfo.gx = rand() % 1000 - 500;
    imuInfo.gy = rand() % 1000 - 500;
    imuInfo.gz = rand() % 1000 - 500;
    imuInfo.mx = rand() % 1000 - 500;
    imuInfo.my = rand() % 1000 - 500;
    imuInfo.mz = rand() % 1000 - 500;
    imuInfo.roll= rand() % 1000 - 500;
    imuInfo.yaw =rand() % 1000 - 500;
    imuInfo.pitch=rand() % 1000 - 500;

    AccountSystem::IMU_Commit(&imuInfo);
}
HAL::Weather_Info_t weaInfo;
HAL::TimeStamp_t time_stamp_info;
HAL::Time_str_t time_info;

void HAL::Weather_Update()
{
    

    strcpy(weaInfo.windDir, "win");
    strcpy(weaInfo.cityname, "Chongqing");
    strcpy(weaInfo.weather, "yin");
    weaInfo.temperature = rand() % 1000 - 500;
    weaInfo.humidity = rand() % 1000 - 500;
    weaInfo.maxTmep = rand() % 1000 - 500;
    weaInfo.minTemp = rand() % 1000 - 500;
    weaInfo.windLevel = rand() % 1000 - 500;
    weaInfo.airQulity = rand() % 6;

    time_info.month = rand() % 6;
    time_info.day = rand() % 6;
    time_info.hour = rand() % 6;
    time_info.minute = rand() % 6;
    // time_info.second = rand() % 6;
    time_info.weekday =rand() % 6;

    AccountSystem::Weather_Commit(&weaInfo);
}
