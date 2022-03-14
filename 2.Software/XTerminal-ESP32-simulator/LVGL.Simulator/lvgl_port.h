#include <Windows.h>
#define IDI_LVGL                       101
#include <stdio.h>
#pragma warning(push)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable:4244)


#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lv_demos/lv_demo.h"
#include "lv_drivers/win32drv/win32drv.h"
#include "lv_lib_freetype/lv_freetype.h"

#pragma warning(pop)

lv_fs_res_t lv_win32_filesystem_driver_error_from_win32(
    DWORD Error);

static void* lv_win32_filesystem_driver_open_callback(
    lv_fs_drv_t* drv,
    const char* path,
    lv_fs_mode_t mode);

static lv_fs_res_t lv_win32_filesystem_driver_close_callback(
    lv_fs_drv_t* drv,
    void* file_p);

void lv_win32_filesystem_driver_initialize();
