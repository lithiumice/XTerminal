#ifndef __Settings_PRESENTER_H
#define __Settings_PRESENTER_H

#include "App/Utils/PageManager/PageBase.h"
#include "HAL/HAL.h"
#include "../Page.h"
#include "lvgl.h"

namespace Page
{

    class Settings : public PageBase
    {
    public:
        struct
        {
#define SET_DEF(icon, className) \
    lv_obj_t *className;

#define SET_DEF2(className)

    #define SET_DEF3(icon, className) \
    lv_obj_t *className;\
    lv_obj_t *className##_sw;

#include "_Setting_DEF.inc"
#undef SET_DEF3
#undef SET_DEF2
#undef SET_DEF

            lv_obj_t *list1;
            lv_obj_t *btn;
            lv_obj_t *spinbox;
            lv_group_t *group;
        } ui;

        Settings();
        virtual ~Settings();

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
        void AttachEvent(lv_obj_t *obj);
        static void onTimerUpdate(lv_timer_t *timer);
        static void onEvent(lv_event_t *event);

    private:
        lv_timer_t *timer;
    };

}

#endif
