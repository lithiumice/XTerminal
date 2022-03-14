#include <HAL/HAL.h>
#include "Weather.h"
#include <map>
#include "stdio.h"

using namespace Page;
extern std::map<String, int> weather_str2int;
extern String *ari_level_int2str;
uint8_t anim_img_select = 1;
#define MAX_ANIM_IMG_NUM 4 

Weather::Weather()
{
}

Weather::~Weather()
{
}

void Weather::onCustomAttrConfig()
{
    // SetCustomCacheEnable(true);
    // SetCustomLoadAnimType(PageManager::LOAD_ANIM_FADE_ON, 500, lv_anim_path_bounce);
    // SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_bounce);
}

void Weather::onViewLoad()
{
    Model.Init();
    View.Create(root);
    AttachEvent(root);
}

void Weather::onViewDidLoad()
{
}

void Weather::onViewWillAppear()
{
    lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), View.ui.group);

    StatusBar::SetStyle(StatusBar::STYLE_TRANSP);

    lv_obj_set_style_bg_color(root, lv_color_white(), LV_PART_MAIN);

    timer = lv_timer_create(onTimerUpdate, 10, this);
    lv_timer_ready(timer);

    lv_obj_fade_in(root, 600, 0);

#ifdef ARDUINO
    notifyUrlThread();
#endif

    updateClockInfo();
    updateWeather();
}

void Weather::onViewDidAppear()
{
    // lv_group_focus_obj(View.ui.cityLabel);
}

void Weather::onViewWillDisappear()
{
    lv_obj_fade_out(root, 800, 0);
}

void Weather::onViewDidDisappear()
{
    lv_timer_del(timer);
}

void Weather::onViewDidUnload()
{
    View.Delete();
    Model.DeInit();
}

void Weather::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Weather::updateSeconds()
{
    HAL::time_info.second++;
    if (HAL::time_info.second >= 60) // 60s
    {
        HAL::time_info.second = 0;

#ifdef ARDUINO
        HAL::parseTimeStamp(HAL::getTimestampLocal());
#endif
        updateClockInfo();
    }
    View.SetClockSec(HAL::time_info.second);
}

void Weather::updateSpaceImg()
{
    static int _spaceIndex = 0;

    if (anim_img_select == 0)
    {

        lv_img_set_src(View.ui.spaceImg, View.manImage_map[_spaceIndex]);
        _spaceIndex = (_spaceIndex + 1) % 10;
    }
    else  if (anim_img_select == 1)
    {

        lv_img_set_src(View.ui.spaceImg, View.treeImage_map[_spaceIndex]);
        _spaceIndex = (_spaceIndex + 1) % 27;
    }
    else  if (anim_img_select == 2)
    {

        lv_img_set_src(View.ui.spaceImg, View.plusImage_map[_spaceIndex]);
        _spaceIndex = (_spaceIndex + 1) % 30;
    }
    else  if (anim_img_select == 3)
    {

        lv_img_set_src(View.ui.spaceImg, View.loveImage_map[_spaceIndex]);
        _spaceIndex = (_spaceIndex + 1) % 30;
    }
}

void Weather::updateClockInfo()
{
    View.SetClockDay(HAL::time_info.month, HAL::time_info.day);
    View.SetClockHour(HAL::time_info.hour, HAL::time_info.minute);
}

void Weather::updateWeather()
{
    View.SetWeather(HAL::weaInfo.weather);
    View.SetAirLevel(HAL::weaInfo.airQulity);
    View.SetCityName(HAL::weaInfo.cityname);
    View.SetHuminature(HAL::weaInfo.humidity);
    View.SetTemperatue(HAL::weaInfo.temperature);
    View.SetTextInfo(HAL::weaInfo.minTemp, HAL::weaInfo.maxTmep, HAL::weaInfo.windDir, HAL::weaInfo.windLevel);
}

// void Weather::img_animing()
// {
//     lv_obj_t *animimg1 = lv_animimg_create(root);
//     lv_animimg_set_src(animimg1, View.loveImage_map, 27);
//     lv_animimg_set_duration(animimg1, 600);
//     lv_animimg_set_repeat_count(animimg1, LV_ANIM_REPEAT_INFINITE);
//     lv_animimg_start(animimg1);
// }

void Weather::Update()
{
    __IntervalExecute(updateSpaceImg(), 50);
    __IntervalExecute(updateSeconds(), 1000);
    __IntervalExecute(updateWeather(), 1000 * 5);
    __IntervalExecute(notifyUrlThread(), (1000 * 60 * HAL::config.update_weather_interval_minute));

    if (HAL::weather_url_get_sucess_flag)
    {
        HAL::weather_url_get_sucess_flag = 0;
        updateWeather();
    }

    if (HAL::clock_url_get_sucess_flag)
    {
        HAL::clock_url_get_sucess_flag = 0;
        updateClockInfo();
        updateSeconds();
    }
}

void Weather::onTimerUpdate(lv_timer_t *timer)
{
    Weather *instance = (Weather *)timer->user_data;
    instance->Update();
}

void Weather::onEvent(lv_event_t *event)
{
    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    auto *instance = (Weather *)lv_obj_get_user_data(obj);

    if (code == LV_EVENT_RELEASED) {
        __ValuePlus(anim_img_select, 1, 0, MAX_ANIM_IMG_NUM - 1);
    } else if (code == LV_EVENT_LONG_PRESSED) {
        instance->Manager->Pop();
    }
    //
    // if (code == LV_EVENT_KEY)
    // {
    //     HAL::TerminalPrintln("Russian LV_EVENT_KEY");
    //     uint32_t key = (*(uint32_t *)event->param);
    //     if (key == LV_KEY_LEFT)
    //     {
    //         __ValuePlus(anim_img_select, -1, 0, MAX_ANIM_IMG_NUM-1);
    //     }
    //     else if (key == LV_KEY_RIGHT)
    //     {
    //         __ValuePlus(anim_img_select, 1, 0, MAX_ANIM_IMG_NUM-1);
    //     }
    //     else if (key == LV_KEY_ENTER)
    //     {
    //         instance->Manager->Pop();
    //     }
    // }
}
