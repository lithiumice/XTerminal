/**
 * @file lv_gif.h
 *
 */

#ifndef LV_GIF_H
#define LV_GIF_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#if LV_LVGL_H_INCLUDE_SIMPLE
#include <lvgl.h>
#else
#include <lvgl/lvgl.h>
#endif

#include "gifdec.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    lv_img_t img;
    gd_GIF *gif;
    lv_timer_t * timer;
    lv_img_dsc_t imgdsc;
    uint32_t last_call;
}lv_gif_t;

extern const lv_obj_class_t lv_gif_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * lv_gif_create_from_file(lv_obj_t * parent, const char * path);
lv_obj_t * lv_gif_create_from_data(lv_obj_t * parent, const void * data);
void lv_gif_restart(lv_obj_t * gif);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_GIFDEC_H*/
