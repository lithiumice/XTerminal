//
// Created by lithiumice on 2021/11/29.
//
#include <Preferences.h>
#include "HAL.h"

namespace HAL {
    Config_t config;
    Preferences prefs;
    uint8_t wifi_name_passswd;
    uint8_t clock_url_get_sucess_flag;
    uint8_t weather_url_get_sucess_flag;
    uint8_t enc_btn_first_push_flag;
    uint8_t game_select_index;
}

#define AUTO_ENTER_WEATHER "K1"
#define AUTO_ENTER_WEATHER_DELAY_SEC "K2"
#define BACKLIGHT_256 "K3"
#define UPDATE_CLOCK_INTERVAL "K4"
#define UPDATE_WEATHER_INTERVAL "K5"
#define DATA_UPLOAD_INTERVAL "K6"
#define AUTO_CALIBRATE_MPU "K7"

// enum ConfigAlterName
// {
//     AUTO_ENTER_WEATHER=1,
//     AUTO_ENTER_WEATHER_DELAY_SEC,
//     BACKLIGHT_256,
//     UPDATE_CLOCK_INTERVAL,
//     UPDATE_WEATHER_INTERVAL,
//     DATA_UPLOAD_INTERVAL
// };

void HAL::config_load()
{
    config_wifi_load();
    config_num_load();
    HAL::TerminalPrintln("auto_enter_weather_delay_sec"+String((int)config.auto_enter_weather_delay_sec));
    HAL::TerminalPrintln("update_weather_interval_minute"+String((int)config.update_weather_interval_minute));
}

void HAL::config_clear()
{
    prefs.begin("Config");
    prefs.clear();
    prefs.end();
}

void HAL::config_save()
{
    config_wifi_save();
    config_num_save();
}

void HAL::config_mpu_load()
{
    prefs.begin("Config_mpu");

    config.mpu_config.x_gyro_offset=prefs.getInt("gx", 0);
    config.mpu_config.y_gyro_offset=prefs.getInt("gy", 0);
    config.mpu_config.z_gyro_offset=prefs.getInt("gz", 0);
    config.mpu_config.x_accel_offset=prefs.getInt("ax", 0);
    config.mpu_config.y_accel_offset=prefs.getInt("ay", 0);
    config.mpu_config.z_accel_offset=prefs.getInt("az", 0);

    prefs.end();
}

void HAL::config_mpu_save()
{
    prefs.begin("Config_mpu");

    prefs.putInt("gx", config.mpu_config.x_gyro_offset);
    prefs.getInt("gy", config.mpu_config.y_gyro_offset);
    prefs.getInt("gz",  config.mpu_config.z_gyro_offset);
    prefs.getInt("ax", config.mpu_config.x_accel_offset);
    prefs.getInt("ay", config.mpu_config.y_accel_offset);
    prefs.getInt("az", config.mpu_config.z_accel_offset);

    prefs.end();
}

void HAL::config_wifi_load()
{
    prefs.begin("Config");

    config.host_name=prefs.getString("host_name", "LithiumPeak");
    config.wifi_name=prefs.getString("wifi_name", "LithiumMe");
    config.wifi_pwd=prefs.getString("wifi_pwd", "1234qwer");

    prefs.end();
}

void HAL::config_wifi_save()
{
    prefs.begin("Config");

    prefs.putString("host_name", config.host_name);
    prefs.putString("wifi_name", config.wifi_name);
    prefs.putString("wifi_pwd", config.wifi_pwd);

    prefs.end();
}

void HAL::config_num_save()
{
    prefs.begin("Config_num");

    prefs.putBool(AUTO_ENTER_WEATHER,config.auto_enter_weather);
    prefs.putBool(AUTO_CALIBRATE_MPU,config.auto_calibrate_mpu);

    prefs.putInt(AUTO_ENTER_WEATHER_DELAY_SEC,config.auto_enter_weather_delay_sec);
    prefs.putInt(BACKLIGHT_256,config.backlight_256);
    prefs.putInt(UPDATE_CLOCK_INTERVAL, config.update_clock_interval_minute);
    prefs.putInt(UPDATE_WEATHER_INTERVAL,config.update_weather_interval_minute);
    prefs.putInt(DATA_UPLOAD_INTERVAL,config.data_upload_interval);

    prefs.end();
}

void HAL::config_num_load()
{
    prefs.begin("Config_num");

    config.auto_enter_weather=prefs.getBool(AUTO_ENTER_WEATHER,0);
    config.auto_calibrate_mpu=prefs.getBool(AUTO_CALIBRATE_MPU,0);

    config.auto_enter_weather_delay_sec=prefs.getInt(AUTO_ENTER_WEATHER_DELAY_SEC,5);
    config.backlight_256=prefs.getInt(BACKLIGHT_256,256);
    config.update_clock_interval_minute=prefs.getInt(UPDATE_CLOCK_INTERVAL, 2);
    config.update_weather_interval_minute=prefs.getInt(UPDATE_WEATHER_INTERVAL, 5);
    config.data_upload_interval=prefs.getInt(DATA_UPLOAD_INTERVAL, 200);

    prefs.end();
}

void HAL::config_clock_save(TimeStamp_t* time_stamp_info)
{
//prefs.remove("naisu");
//prefs.end();
//Serial.println(prefs.freeEntries());
    prefs.begin("Config");

    prefs.putLong64("Timestamp",time_stamp_info->preNetTimestamp);

    prefs.end();
}

void HAL::config_clock_load(TimeStamp_t* time_stamp_info)
{
    prefs.begin("Config");

    time_stamp_info->preNetTimestamp=prefs.getLong64("Timestamp",0);
    time_stamp_info->preLocalTimestamp = millis();
    HAL::parseTimeStamp(HAL::getTimestampLocal());

    prefs.end();


}

void HAL::config_weather_save(HAL::Weather_Info_t* info)
{
    prefs.begin("Config_wea");

    prefs.putString("cityname", info->cityname);
    prefs.putString("weather", info->weather);
    prefs.putInt("humidity", info->humidity);
    prefs.putInt("temperature", info->temperature);
    prefs.putInt("maxTmep", info->maxTmep);
    prefs.putInt("minTemp", info->minTemp);
    prefs.putInt("windLevel", info->windLevel);
    prefs.putInt("airQulity", info->airQulity);
    prefs.putString("windDir", info->windDir);

//    HAL::TerminalPrintln("pref:" + String(prefs.freeEntries()));
    prefs.end();
}

void HAL::config_weather_load(HAL::Weather_Info_t* info)
{
    prefs.begin("Config_wea");

    String tmp=prefs.getString("cityname", "Chongqing");
    strcpy(info->cityname,tmp.c_str());
    tmp=prefs.getString("weather", "yun").c_str();
    strcpy(info->weather,tmp.c_str());
    info->humidity=prefs.getInt("humidity", 25);
    info->temperature=prefs.getInt("temperature", 12);
    info->maxTmep=prefs.getInt("maxTmep", 15);
    info->minTemp=prefs.getInt("minTemp", 10);
    info->windLevel=prefs.getInt("windLevel", 1);
    info->airQulity=prefs.getInt("airQulity", 1);
    tmp=prefs.getString("windDir", "east").c_str();
    strcpy(info->windDir,tmp.c_str());

    prefs.end();
}