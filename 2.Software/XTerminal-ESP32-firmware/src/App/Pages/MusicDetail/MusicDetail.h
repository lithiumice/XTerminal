#ifndef __MusicDetail_PRESENTER_H
#define __MusicDetail_PRESENTER_H

#include "App/Utils/PageManager/PageBase.h"
#include "HAL/HAL.h"
#include "../Page.h"
#include "lvgl.h"

namespace Page
{

    class MusicDetail : public PageBase
    {
    public:
        struct
        {
            lv_style_t style_bg;
            lv_style_t style_indic;

            lv_obj_t* album;
            lv_obj_t* btn_pause;
            lv_obj_t* btn_pause_label;
            
            lv_obj_t* btn_prev;
            lv_obj_t* btn_next;
            lv_obj_t* btn_list;
            lv_obj_t* btn_vol_plus;
            lv_obj_t* btn_vol_minus;
            lv_obj_t* duration_bar;
            lv_obj_t* song_name;
            lv_obj_t* duration_label;

            lv_group_t *group;
        } ui;

        MusicDetail();
        virtual ~MusicDetail();

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
