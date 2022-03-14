#include "ESP32Time.h"
#include "ArduinoJson.h"
#include <map>
#include <string>
#include "HAL.h"


#define TIMEZERO_OFFSIZE (28800000) // 时区偏移(小时) 8*60*60
#define WEATHER_NOW_API "https://www.tianqiapi.com/free/day?appid=%s&appsecret=%s&unescape=1"
#define WEATHER_WEEK_API "https://www.tianqiapi.com/free/week?unescape=1&appid=%s&appsecret=%s"
#define TIMESTAMP_API "http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp"
//{"api":"mtop.common.getTimestamp","v":"*","ret":["SUCCESS::接口调用成功"],"data":{"t":"1638190161601"}}
#define  tianqi_appid  "59977553"
#define tianqi_appsecret  "HLSZf6pn"
#define WEATHER_NOW_FULL_API "https://www.tianqiapi.com/free/day?appid=59977553&appsecret=HLSZf6pn&unescape=1"
//{"cityid":"101040100","city":"重庆","update_time":"22:52","wea":"晴","wea_img":"qing","tem":"9","tem_day":"16","tem_night":"9","win":"西北风","win_speed":"1级","win_meter":"2km\/h","air":"82"}

ESP32Time esp_rtc;

namespace HAL {
    Weather_Info_t weaInfo;
    TimeStamp_t time_stamp_info;
    Time_str_t time_info;
};

static int parseWindLevel(String str)
{
    int ret = 0;
    for (char ch : str)
    {
        if (ch >= '0' && ch <= '9')
        {
            ret = ret * 10 + (ch - '0');
        }
    }
    return ret;
}

static int parseAirLevel(int q)
{
    if (q < 50)
    {
        return 0;
    }
    else if (q < 100)
    {
        return 1;
    }
    else if (q < 150)
    {
        return 2;
    }
    else if (q < 200)
    {
        return 3;
    }
    else if (q < 300)
    {
        return 4;
    }
    return 5;
}

void HAL::parseTimeStamp(int64_t timestamp)
{
    esp_rtc.setTime(timestamp / 1000);
    time_info.month = esp_rtc.getMonth() + 1;
    time_info.day = esp_rtc.getDay();
    time_info.hour = esp_rtc.getHour(true);
    time_info.minute = esp_rtc.getMinute();
    time_info.second = esp_rtc.getSecond();
    time_info.weekday = esp_rtc.getDayofWeek();
    Serial.printf("time : %d-%d-%d\n",time_info.hour, time_info.minute, time_info.second);
}

bool HAL::getWeatherNowUrl(Weather_Info_t* info)
{
    if (WL_CONNECTED != WiFi.status())
    {
        HAL::TerminalPrintln("wifi not ready");
        return false;
    }

    bool ret=false;
    HTTPClient http;
    http.setTimeout(1000);
//    char api[128] = "";
//    snprintf(api, 128, WEATHER_NOW_API, tianqi_appid, tianqi_appsecret);
//    http.begin(api);
    http.begin(WEATHER_NOW_FULL_API);
    HAL::TerminalPrintln("start net weather");

    int httpCode = http.GET();
    if (httpCode > 0)
    {
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
        {
            String payload = http.getString();
//            HAL::TerminalPrintln(payload);
            Serial.println(payload);

            DynamicJsonDocument doc(1024);
            deserializeJson(doc, payload);
            JsonObject sk = doc.as<JsonObject>();

            strcpy(info->cityname, city_cn[sk["city"].as<String>().c_str()].c_str());
            strcpy(info->weather, sk["wea_img"].as<String>().c_str());
            //TODO
            info->humidity=23;
            info->temperature = sk["tem"].as<int>();
            info->maxTmep = sk["tem_day"].as<int>();
            info->minTemp = sk["tem_night"].as<int>();
            strcpy(info->windDir, windir_cn2en[sk["win"].as<String>().c_str()].c_str());
//            strcpy(info->windDir, sk["win"].as<String>().c_str());
            info->windLevel = parseWindLevel(sk["win_speed"].as<String>());
            info->airQulity = parseAirLevel(sk["air"].as<int>());

            config_weather_save(info);
            gflag.fisrt_get_weather_flag=1;
            HAL::weather_url_get_sucess_flag=1;
            ret=true;
        }
    }
    else
    {
        ret=false;
        HAL::TerminalPrintln("http get failed with code "+http.errorToString(httpCode));
    }
    http.end();
    return ret;
}

bool HAL::getWeatherWeekUrl(short maxT[], short minT[])
{
    if (WL_CONNECTED != WiFi.status())
        return false;

    bool ret=false;
    HTTPClient http;
    http.setTimeout(1000);
    char api[128] = "";
    snprintf(api, 128, WEATHER_WEEK_API, tianqi_appid, tianqi_appsecret);
    http.begin(api);
    HAL::TerminalPrintln("start net week weather");

    int httpCode = http.GET();
    if (httpCode > 0)
    {
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
        {
            String payload = http.getString();
            Serial.println(payload);
            DynamicJsonDocument doc(2048);
            deserializeJson(doc, payload);
            JsonObject sk = doc.as<JsonObject>();
            for (int gDW_i = 0; gDW_i < 7; ++gDW_i)
            {
                maxT[gDW_i] = sk["data"][gDW_i]["tem_day"].as<int>();
                minT[gDW_i] = sk["data"][gDW_i]["tem_night"].as<int>();
            }
            gflag.fisrt_get_weather_flag=1;
            ret=true;
        }
    }
    else
    {
        ret=false;
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    return ret;
}

int64_t HAL::getTimestampLocal()
{
    time_stamp_info.preNetTimestamp = time_stamp_info.preNetTimestamp +
            (millis() - time_stamp_info.preLocalTimestamp);
    time_stamp_info.preLocalTimestamp = millis();
    return time_stamp_info.preNetTimestamp;
}

int64_t HAL::getTimestampUrl()
{
    if (WL_CONNECTED != WiFi.status())
    {
        HAL::TerminalPrintln("wifi not ready");
        return 0;
    }
    String time = "";
    HTTPClient http;
    http.setTimeout(1000);
    http.begin(TIMESTAMP_API);

    int httpCode = http.GET();
    if (httpCode > 0)
    {
        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http.getString();
            Serial.println(payload);
            int time_index = (payload.indexOf("data")) + 12;
            time = payload.substring(time_index, payload.length() - 3);
            // 以网络时间戳为准
            time_stamp_info.preNetTimestamp = atoll(time.c_str()) + time_stamp_info.errorNetTimestamp + TIMEZERO_OFFSIZE;
            time_stamp_info.preLocalTimestamp = millis();

            config_clock_save(&time_stamp_info);
            HAL::clock_url_get_sucess_flag=1;
            gflag.fisrt_get_clock_flag=1;
        }
    }
    else
    {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        // 得不到网络时间戳时
        time_stamp_info.preNetTimestamp = time_stamp_info.preNetTimestamp + (millis() - time_stamp_info.preLocalTimestamp);
        time_stamp_info.preLocalTimestamp = millis();
    }
    http.end();

    return time_stamp_info.preNetTimestamp;
}

void HAL::Weather_Update()
{
    HAL::getWeatherNowUrl(&weaInfo);
    // AccountSystem::Weather_Commit(&weaInfo);
}

void HAL::Clock_Update()
{
    HAL::parseTimeStamp(HAL::getTimestampUrl());
}