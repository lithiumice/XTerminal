#ifndef __Pictures_PRESENTER_H
#define __Pictures_PRESENTER_H

#include "PicturesView.h"
#include "PicturesModel.h"

namespace Page
{

class Pictures : public PageBase
{
public:
    Pictures();
    virtual ~Pictures();

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
    PicturesView View;
    PicturesModel Model;
    lv_timer_t* timer;
};

}

#endif
