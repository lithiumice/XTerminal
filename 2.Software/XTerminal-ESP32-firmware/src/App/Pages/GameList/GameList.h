#ifndef __GameList_PRESENTER_H
#define __GameList_PRESENTER_H

#include "GameListView.h"

namespace Page
{

class GameList : public PageBase
{
public:

public:
    GameList();
    virtual ~GameList();

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

// private:
public:
    GameListView View;
    lv_timer_t* timer;
};

}

#endif
