#ifndef __SYSTEM_INFOS_VIEW_H
#define __SYSTEM_INFOS_VIEW_H

#include "../Page.h"

namespace Page
{

class SystemInfosView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
    typedef struct
    {
        lv_obj_t* cont;
        lv_obj_t* icon;
        lv_obj_t* labelInfo;
        lv_obj_t* labelData;
    } item_t;

    struct
    {
        item_t wifi;
        item_t system;
        // item_t imu;
        item_t battery;
        item_t storage;
        lv_group_t* group;
    } ui;

public:

    void SetWifiInfo(
        const char* host_name,
        const char* wifi_name,
        const char* password,
        uint8_t is_connected
    );

    void SetIMU(
        const char* info
    );
    void SetBattery(
        int usage,
        float voltage,
        const char* state
    );
    void SetStorage(const char* detect, const char* size, const char* version, int total_heap, int used_heap_percent);
    // void SetStorage(
    //     const char* detect,
    //     const char* size,
    //     const char* version
    // );
    void SetSystem(
        const char* firmVer,
        const char* authorName,
        const char* lvglVer,
        const char* bootTime,
        const char* compilerName,
        const char* bulidTime
    );

    void SetScrollToY(lv_obj_t* obj, lv_coord_t y, lv_anim_enable_t en);
    static void onFocus(lv_group_t* e);

private:
    struct
    {
        lv_style_t icon;
        lv_style_t focus;
        lv_style_t info;
        lv_style_t data;
    } style;

private:
    void Group_Init();
    void Style_Init();
    void Style_Reset();
    void Item_Create(
        item_t* item,
        lv_obj_t* par,
        const char* name,
        const char* img_src,
        const char* infos
    );
};

}

#endif // !__VIEW_H
