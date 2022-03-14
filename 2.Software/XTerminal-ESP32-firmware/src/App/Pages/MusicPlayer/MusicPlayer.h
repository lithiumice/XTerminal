#ifndef __MusicPlayer_PRESENTER_H
#define __MusicPlayer_PRESENTER_H

#include "App/Utils/PageManager/PageBase.h"
#include "HAL/HAL.h"
#include "../Page.h"
#include "lvgl.h"


#ifdef ARDUINO
#include "HAL/HAL_SdCard.h"
#else
namespace fs
{
    class FS
    {
    public:

    };
};

#endif

// extern fs::FS SD;


namespace Page
{

    class MusicPlayer : public PageBase
    {
    public:
        struct
        {
        lv_obj_t* play_disp;

        lv_obj_t* file_list;
            lv_group_t *group;
        } ui;

        MusicPlayer();
        virtual ~MusicPlayer();

        virtual void onCustomAttrConfig();
        virtual void onViewLoad();
        virtual void onViewDidLoad();
        virtual void onViewWillAppear();
        virtual void onViewDidAppear();
        virtual void onViewWillDisappear();
        virtual void onViewDidDisappear();
        virtual void onViewDidUnload();

        void ListDirFiles(fs::FS& fs, const char* dirname, uint8_t levels);

    private:
        void Update();
        void AttachEvent(lv_obj_t *obj);
        static void onTimerUpdate(lv_timer_t *timer);
        static void onEvent(lv_event_t *event);
    // void SplitString(const std::string &s, std::vector<std::string> &v, const std::string &c);

private:
    lv_timer_t *timer;
    };

}

#endif
