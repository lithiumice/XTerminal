#ifndef __HAL_H
#define __HAL_H

#include "string"
#include <stdint.h>
#include "HAL_Def.h"
#include "App/Configs/Config.h"
#include "CommonMacro.h"
#include "lvgl/lvgl.h"


#ifdef ARDUINO
#include "Wire.h"
extern TaskHandle_t handleTaskUrl;
extern lv_color_t *lv_disp_buf_p;
#endif


extern HAL::IMU_Info_t imuInfo;
void notifyUrlThread();

namespace HAL
{
/* HAL */
    void Init();
    void Update();

/* Config */
    void sensors_init();
    void sensors_max30102_data();

    /* Config */
    extern Config_t config;
    extern uint8_t wifi_name_passswd;
    extern uint8_t clock_url_get_sucess_flag;
    extern uint8_t weather_url_get_sucess_flag;
    extern uint8_t enc_btn_first_push_flag;
    extern uint8_t game_select_index;

    void config_weather_save(HAL::Weather_Info_t *info);
    void config_weather_load(HAL::Weather_Info_t *info);
    // void config_clock_save(int64_t Timestamp);
    // void config_clock_load(int64_t *Timestamp);
    void config_clock_load(TimeStamp_t *time_stamp_info);
     void config_clock_save(TimeStamp_t *time_stamp_info);
    void config_load();
    void config_save();
    void config_clear();
    void config_num_save();
    void config_num_load();
    void config_wifi_save();
    void config_wifi_load();
    void config_mpu_save();
    void config_mpu_load();

/* Weather */
    extern Weather_Info_t weaInfo;
    extern TimeStamp_t time_stamp_info;
    extern Time_str_t time_info;
    int64_t getTimestampLocal();
    int64_t getTimestampUrl();
    bool getWeatherWeekUrl(short maxT[], short minT[]);
    bool getWeatherNowUrl(Weather_Info_t *info);
    void parseTimeStamp(int64_t timestamp);



/* WIFI */
    void wifi_init();
    void wifi_search();
    bool wifi_connect();
    bool wifi_close();
    bool wifi_open_ap();
    bool wifi_isconnected();
    void wifi_smartConfig();

/* Terminal */
    extern std::string globalTermText;
    extern uint8_t term_text_update_flag;
    void TerminalPrint( char* text);
    void TerminalPrintln( char* text);
    void TerminalPrintln( String text);

/* Backlight */
    void Backlight_Init();
    uint32_t Backlight_GetValue();
    void Backlight_SetValue(int32_t val);
    void Backlight_SetGradual(uint32_t target, uint16_t time = 500);
    void Backlight_ForceLit(bool en);

/* I2C */
    void I2C_Init(bool startScan);

#ifdef ARDUINO
    void I2C_Scan(TwoWire* Wire);
#endif

/* IMU */
    void IMU_Init();
    void IMU_Update();
    void Clock_Update();
    void Weather_Update();
    void IMU_Calibrate();

/* SD */
    bool SD_Init();
    void SD_Update();
    bool SD_GetReady();
    float SD_GetCardSizeMB();
    typedef void(* SD_CallbackFunction_t)(bool insert);
    void SD_SetEventCallback(SD_CallbackFunction_t callback);


/* Power */
    void Power_Init();
    void Power_HandleTimeUpdate();
    void Power_SetAutoLowPowerTimeout(uint16_t sec);
    uint16_t Power_GetAutoLowPowerTimeout();
    void Power_SetAutoLowPowerEnable(bool en);
    void Power_Shutdown();
    void Power_Update();
    void Power_EventMonitor();
    void Power_GetInfo(Power_Info_t* info);
    typedef void(* Power_CallbackFunction_t)(void);
    void Power_SetEventCallback(Power_CallbackFunction_t callback);

/* Buzzer */
    void Buzz_init();
    void Buzz_SetEnable(bool en);
    void Buzz_Tone(uint32_t freq, int32_t duration = 0);

/* Encoder */
    void Encoder_Init();
    void Encoder_Update();
    int16_t Encoder_GetDiff();
    bool Encoder_GetIsPush();
    void Encoder_SetEnable(bool en);

/* Audio */
    void Audio_Init();
    void Audio_Update();
    bool Audio_PlayMusic(const char* name);


/* Bluetooth */
    bool BT_Init();
    void BT_Update();
    bool BluetoothConnected();
}

#endif
