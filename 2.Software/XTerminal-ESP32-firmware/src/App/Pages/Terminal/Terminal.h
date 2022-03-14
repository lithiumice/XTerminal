// #ifndef __Terminal_PRESENTER_H
// #define __Terminal_PRESENTER_H
#pragma once

#include "TerminalView.h"
#include "TerminalModel.h"

namespace Page
{

class Terminal : public PageBase
{
public:
    Terminal();
    virtual ~Terminal();

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
    TerminalView View;
    TerminalModel Model;
    lv_timer_t* timer;
};

}

// #endif
