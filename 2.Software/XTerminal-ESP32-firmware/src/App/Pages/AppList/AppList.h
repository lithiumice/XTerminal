#ifndef __AppList_PRESENTER_H
#define __AppList_PRESENTER_H

#include "AppListView.h"

namespace Page
{

class AppList : public PageBase
{
public:

public:
    AppList();
    virtual ~AppList();

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
    AppListView View;
    lv_timer_t* timer;
};

}

#endif
