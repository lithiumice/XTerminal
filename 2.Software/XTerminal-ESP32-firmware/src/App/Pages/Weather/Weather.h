#ifndef __Weather_PRESENTER_H
#define __Weather_PRESENTER_H

#include "WeatherView.h"
#include "WeatherModel.h"

namespace Page
{

class Weather : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    Weather();
    virtual ~Weather();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewDidUnload();

private:
    void updateWeather();
    void img_animing();
    void Update();
    void AttachEvent(lv_obj_t* obj);
    void updateSeconds();
    void updateSpaceImg();
    void updateClockInfo();
    static void onTimerUpdate(lv_timer_t* timer);
    static int onWeatherEvent(Account* account, Account::EventParam_t* param);
    int onClockEvent(Account* account, Account::EventParam_t* param);
    static void onEvent(lv_event_t* event);
    

private:
    WeatherView View;
    WeatherModel Model;
    lv_timer_t* timer;
};

}

#endif
