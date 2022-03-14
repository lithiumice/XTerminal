#include "HAL/HAL.h"
#include "App/Configs/Version.h"
#include <Arduino.h>
#include "HAL/HAL.h"
#include "Port/Display.h"
#include "App/App.h"
#include "App/ano_dt.hpp"
#include "App/Configs/Config.h"
#include "HAL_Audio.h"
#include "App/rgb_led.h"

Pixel rgb;
TaskHandle_t handleTaskUrl;
TaskHandle_t handleTaskNormal;
data_send dataMonitor;

void notify()
{
    static char progress_chars[] = "|\\-/"; // 0-3
    static int p_index = 0;
    p_index++; // 0-4
    if (p_index >= 4)
        p_index = 0;
    Serial.print("\r");
    Serial.print(progress_chars[p_index]);
    Serial.print("OK");
}

void upload()
{
    dataMonitor.send_vofa_4(
        // irValue,
        // beatsPerMinute,
        // redValue,
        // greenValue
        imuInfo.pitch,
        imuInfo.roll,
        imuInfo.yaw,
        imuInfo.az);
}

void normal()
{
    HAL::Power_Update();
    HAL::Encoder_Update();
    HAL::Audio_Update();
    HAL::IMU_Update();
}

void notifyUrlThread()
{
#ifdef ARDUINO
    HAL::TerminalPrintln("notifyUrlThread");
    xTaskNotifyGive(handleTaskUrl);
#endif
}

void TaskUrlUpdate(void *parameter)
{
    // audio_init();
    // audio_start();
    for (;;)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        HAL::Weather_Update();
        delay(5);
        HAL::Clock_Update();

        UBaseType_t used = uxTaskGetStackHighWaterMark(handleTaskUrl);
        printf("url used: %d KB\n", used * 4 / 1024);
    }
}

void NormalUpdate(void *parameter)
{
    for (;;)
    {
        __IntervalExecute(normal(), 30);
        // __IntervalExecute(upload(), 200);
        // __IntervalExecute(get_sys_info(), 1500);
        // __IntervalExecute(HAL::sensors_max30102_data(), 1000);

        // if (gflag.update_max_flag)
        //     __IntervalExecute(HAL::sensors_max30102_data(), 300);


        delay(1);
        
    }
}

void AudioUpdate(void *parameter)
{
    for (;;)
    {
        if (gflag.audio_en_flag)
            audio_loop();
        delay(1);
    }
}

void HAL::Init()
{
    Serial.begin(115200);

    lv_disp_buf_p = static_cast<lv_color_t *>(
        malloc(DISP_BUF_SIZE * sizeof(lv_color_t)));
    if (lv_disp_buf_p == nullptr)
        LV_LOG_WARN("lv_port_disp_init malloc failed!\n");

    config_load();
    config_weather_load(&HAL::weaInfo);
    config_clock_load(&HAL::time_stamp_info);

    gflag.audio_en_flag = 0;
    gflag.update_max_flag = 0;

    HAL::Power_Init();
    HAL::Backlight_Init();
    HAL::Buzz_init();
    HAL::Audio_Init();

    HAL::wifi_init();
    HAL::wifi_connect();
   

    HAL::Encoder_Init();
    HAL::Audio_PlayMusic("Startup");

    Port_Init();

    // HAL::SD_Init();
    // audio_init();
    //     audio_start();

    App_Init();
    // rgb.init();
    // rgb.setBrightness(0.1).setRGB(0, 0, 122, 204).setRGB(1, 0, 122, 204);
    // HAL::SD_Init();

    // 116-76=40KB
    // xTaskCreate(
    //         TaskUrlUpdate,
    //         "TaskUrlUpdate",
    //         1024*35, //KB
    //         NULL,
    //         1,
    //         &handleTaskUrl
    //         );

    xTaskCreatePinnedToCore(
        TaskUrlUpdate,
        "TaskUrlUpdate",
        // 1420*4/1024 KB=5.54KB
        1024 * 6.0, // KB
        NULL,
        configMAX_PRIORITIES - 1,
        &handleTaskUrl,
        0);

    xTaskCreate(
        NormalUpdate,
        "NormalUpdate",
        1024 * 1.5, // KB
        NULL,
        configMAX_PRIORITIES - 2,
        &handleTaskNormal);

    // pinMode(36, OUTPUT);
}

void test_pin()
{
    digitalWrite(36, 1);
    delay(1000);
    digitalWrite(36, 0);
    delay(1000);
}

void toggle_pin()
{
    digitalWrite(36, !digitalRead(36));
    printf("%d", digitalPinCanOutput(36));
}

void HAL::Update()
{
    // core 1
    lv_task_handler();
    // if (millis() > 3000)
    //     audio_loop();
    // __IntervalExecute(toggle_pin(), 1000);
}
