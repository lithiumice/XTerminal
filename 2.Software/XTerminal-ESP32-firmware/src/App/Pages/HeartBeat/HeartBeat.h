#ifndef __HeartBeat_PRESENTER_H
#define __HeartBeat_PRESENTER_H

#include "App/Utils/PageManager/PageBase.h"
#include "HAL/HAL.h"
#include "../Page.h"
#include "lvgl.h"

namespace Page
{

class HeartBeat : public PageBase
{
public:
    struct
    {
        lv_obj_t* rate_text;
        lv_obj_t* avg_bpm_text;
        lv_chart_series_t* rate_ser;
        lv_chart_series_t* bmp_ser;
        lv_obj_t* rate_chart;
        lv_group_t* group;
    } ui;

    HeartBeat();
    virtual ~HeartBeat();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewDidUnload();

    void ArcValueCtrl(int step);
    void Chart_Create();
    void Ser_Create();
    void Anim_Create();
    void Labels_Create();
    void GUICreate();
    void Chart_AutoRangeProcess();
    void Chart_AutoRangeProcess(lv_obj_t *chart, lv_chart_series_t *series, lv_chart_axis_t axis);

private:
    void Update();
    void AttachEvent(lv_obj_t* obj);
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);
    

private:
    lv_timer_t* timer;
};

}

#endif
