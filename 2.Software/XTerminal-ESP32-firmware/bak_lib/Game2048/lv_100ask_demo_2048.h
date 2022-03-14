#ifndef LV_100ASK_DEMO_2048_H
#define LV_100ASK_DEMO_2048_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************
 *      INCLUDES
 *********************/
// #include "../lv_100ask_demo.h"
#include "lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
// void lv_100ask_demo_2048(void);
void lv_100ask_demo_2048(lv_obj_t *root);
void lv_100ask_demo_2048_deinit();
void game_2048_key_cb(lv_dir_t dir);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_100ASK_DEMO_2048_H */





