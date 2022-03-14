#ifndef __WifiText_PRESENTER_H
#define __WifiText_PRESENTER_H

#include "App/Utils/PageManager/PageBase.h"
#include "HAL/HAL.h"
#include "../Page.h"
#include "lvgl.h"

namespace Page
{

class WifiText : public PageBase
{
public:
    struct
    {
        lv_obj_t* name_textarea;
        lv_obj_t* pwd_textarea;
        lv_obj_t* pwd_label;
        lv_obj_t* name_label;

        lv_group_t* group;
    } ui;

    lv_obj_t* kb;
    WifiText();
    virtual ~WifiText();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewDidUnload();

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
