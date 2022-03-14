#ifndef __GAMEDISP_H
#define __GAMEDISP_H

#include <stdint.h>
#include "lvgl.h"

#define GAME_DISP_WIDTH  128
#define GAME_DISP_HEIGHT 64

typedef struct {
    lv_color_t color;
    lv_coord_t x_ofs;
    lv_obj_t* led;
}LED_TypeDef;

typedef struct {
    const char* sym;
    lv_align_t align;
    lv_coord_t x_mod;
    lv_coord_t y_mod;
}BtnCfg_TypeDef;
void Game_Canvas_DrawBuf(uint8_t* buf, int16_t w, int16_t h);

#endif
