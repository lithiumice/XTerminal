#ifndef __CONFIG_H
#define __CONFIG_H

/*=========================
   Application configuration
 *=========================*/

#define CONFIG_SYSTEM_SAVE_FILE_PATH "S:/SystemSave.json"
#define CONFIG_SYSTEM_LANGUAGE_DEFAULT \
  {                                    \
    'e', 'n', '-', 'G', 'B'            \
  }
#define CONFIG_SYSTEM_GMT_OFFSET_DEFAULT 8 // GMT+ 8
#define CONFIG_WEIGHT_DEFAULT 65           // kg
#define CONFIG_GPS_REFR_PERIOD 1000        // ms
#define CONFIG_GPS_LNG_DEFAULT 116.391332
#define CONFIG_GPS_LAT_DEFAULT 39.907415
#define CONFIG_TRACK_FILTER_OFFSET_THRESHOLD 2 // pixel
#define CONFIG_TRACK_RECORD_FILE_DIR_NAME "Track"
#define CONFIG_MAP_USE_WGS84_DEFAULT false
#define CONFIG_MAP_DIR_PATH \
  {                         \
    '/', 'M', 'A', 'P'      \
  } //"/MAP"
#define CONFIG_ARROW_THEME_DEFAULT "default"
#define CONFIG_LIVE_MAP_LEVEL_DEFAULT 16
#define CONFIG_LIVE_MAP_VIEW_WIDTH LV_HOR_RES
#define CONFIG_LIVE_MAP_VIEW_HEIGHT LV_VER_RES
#define CONFIG_TRACK_VIRTUAL_GPX_FILE_PATH "S:/TRK_20210801_203324.gpx"

/*=========================
   Hardware Configuration
 *=========================*/


#if defined(TFT240X320)
#define HOR_RES 320
#define VER_RES 240
#define DISP_ROTATE 1
#elif defined(TFT240X240)
#define HOR_RES 240
#define VER_RES 240
#define DISP_ROTATE 1
#elif defined(TFT240X280)
#define HOR_RES 280
#define VER_RES 240
#define DISP_ROTATE 1
#endif

#if DISP_ROTATE==0
#define DISP_HOR_RES VER_RES
#define DISP_VER_RES HOR_RES
#elif DISP_ROTATE==1
#define DISP_HOR_RES HOR_RES
#define DISP_VER_RES VER_RES
#endif

#define DISP_BUF_SIZE (DISP_HOR_RES * DISP_VER_RES / 10) 
#define CONFIG_BUZZ_CHANNEL 2
#define CONFIG_SOUND_ENABLE_DEFAULT true

#if defined(DEVICE0)

#define CONFIG_POWER_EN_PIN 21
#define CONFIG_SD_DET_PIN 37
#define CONFIG_BUZZ_PIN 5
#define CONFIG_SCREEN_BLK_PIN 12
#define CONFIG_BAT_DET_PIN 37
#define CONFIG_BAT_CHG_DET_PIN 38
#define CONFIG_IIC1_SDA_PIN -1
#define CONFIG_IIC1_SCL_PIN -1
#define CONFIG_IIC2_SDA_PIN 10
#define CONFIG_IIC2_SCL_PIN 9
#define CONFIG_ENCODER_DOWN_PIN 34
#define CONFIG_ENCODER_UP_PIN 35
#define CONFIG_ENCODER_PUSH_PIN 27
#define CONFIG_BTN_A_PIN 32
#define CONFIG_BTN_B_PIN 33
// #define CONFIG_BTN_A_PIN 19
// #define CONFIG_BTN_B_PIN 25
#define CONFIG_SD_CS 15
#define CONFIG_SPI_MOSI 13
#define CONFIG_SPI_MISO 26
#define CONFIG_SPI_SCK 14
#define CONFIG_I2S_DOUT 25
#define CONFIG_I2S_BCLK 19
#define CONFIG_I2S_LRC 22

#elif defined(DEVICE3)

#define CONFIG_POWER_EN_PIN 21
#define CONFIG_SD_DET_PIN 22
#define CONFIG_BUZZ_PIN 25
#define CONFIG_SCREEN_BLK_PIN 27
#define CONFIG_BAT_DET_PIN 39
#define CONFIG_BAT_CHG_DET_PIN 32
#define CONFIG_IIC1_SDA_PIN 15
#define CONFIG_IIC1_SCL_PIN 2
#define CONFIG_IIC2_SDA_PIN 21
#define CONFIG_IIC2_SCL_PIN 22
#define CONFIG_ENCODER_DOWN_PIN 34
#define CONFIG_ENCODER_UP_PIN 36
#define CONFIG_ENCODER_PUSH_PIN 35
#define CONFIG_BTN_A_PIN -1
#define CONFIG_BTN_B_PIN -1
#define CONFIG_SD_CS 4
#define CONFIG_SPI_MOSI 15
#define CONFIG_SPI_MISO 2
#define CONFIG_SPI_SCK 14
#define CONFIG_I2S_DOUT 19
#define CONFIG_I2S_BCLK 26
#define CONFIG_I2S_LRC 25

#else

#endif

#endif
