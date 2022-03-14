// #ifndef __Russian_PRESENTER_H
// #define __Russian_PRESENTER_H
#pragma once


#include "App/Utils/PageManager/PageBase.h"
#include "HAL/HAL.h"
#include "../Page.h"
#include "lvgl.h"

namespace Page
{

class Game2048 : public PageBase
{
public:
    struct
    {
        lv_group_t* group;
    } ui;
    lv_obj_t* level_label;
    lv_obj_t* score_label;
    lv_obj_t* next_label;

    lv_obj_t* canvas;
    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_t empty_rect_dsc;

    void DrawBlock(int x, int y, int block_type);

    int Rotate(int S, int I);

    int Display(int x, int y, int CAC, int Mode);

    int DoBlocks();

    int CheckCollision();

    void GameInit();

    Game2048();
    virtual ~Game2048();

    virtual void onCustomAttrConfig();
    void Draw_Block();
    void Draw_Block(int x, int y, int block_type);
    void Canvas_Init();
    void Canvas_Clear();
    void Labels_Init();
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

// #endif
