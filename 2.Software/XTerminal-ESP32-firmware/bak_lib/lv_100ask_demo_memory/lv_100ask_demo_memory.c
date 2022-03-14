/**
 ******************************************************************************
 * @file    lv_100ask_demo_memory.c
 * @author  百问科技
 * @version V1.0
 * @date    2021-10-11
 * @brief	数字对拼图小游戏
 ******************************************************************************
 * Change Logs:
 * Date           Author          Notes
 * 2021-10-11     zhouyuebiao     First version
 ******************************************************************************
 * @attention
 *
 * Copyright (C) 2008-2021 深圳百问网科技有限公司<https://www.100ask.net/>
 * All rights reserved
 *
 ******************************************************************************
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_100ask_demo.h"

#if LV_USE_100ASK_DEMO_GAME_MEMORY

#include<time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lv_100ask_demo_memory.h"


/*********************
 *      DEFINES
 *********************/
#define OBJ_COUNT_HOR   (6)
#define OBJ_COUNT_VER   (6)
#define OBJ_MAX_COUNT   (OBJ_COUNT_HOR * OBJ_COUNT_VER)
#define OBJ_COUNT       (OBJ_MAX_COUNT / 2)

/**********************
 *      TYPEDEFS
 **********************/


/**********************
 *  STATIC VARIABLES
 **********************/
static int list_number[OBJ_MAX_COUNT];
static lv_obj_t * g_obj[OBJ_MAX_COUNT];   /* 方块 */
static lv_obj_t * g_befObj;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void list_rand_number(int arry[], int max_count, int count);


// 生成个数为max_count的指定count范围内count个只重复一次的随机数的算法
static void list_rand_number(int arry[], int max_count, int count)
{
	int w, t;

	srand((unsigned)time(NULL));
	//srand(seed);
	for (int i = 0; i < max_count; i++)
	    arry[i] = (i % count) + 1;
	for (int i = 0; i < max_count; i++)
	{
		w = rand() % (count - (i % count)) + i;
	    t = arry[i];
	    arry[i] = arry[w];
	    arry[w] = t;
	}
}


static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED)
    {
        lv_obj_t *current_obj;
        if (NULL == g_befObj)
        {
            g_befObj = lv_event_get_target(e);
            lv_obj_set_style_text_opa(g_befObj, LV_OPA_100, 0);
            return;
        }
        else
        {
            current_obj = lv_event_get_target(e);
            if(current_obj == g_befObj) return;
        }

        if (strcmp(\
                   lv_label_get_text(lv_obj_get_child(current_obj, 0)),\
                   lv_label_get_text(lv_obj_get_child(g_befObj, 0))) == 0)
        {
            lv_obj_set_style_bg_opa(current_obj, LV_OPA_0, 0);
            lv_obj_set_style_text_opa(current_obj, LV_OPA_0, 0);
            lv_obj_set_style_border_opa(current_obj, LV_OPA_0, 0);
            lv_obj_set_style_shadow_opa(current_obj, LV_OPA_0, 0);
            lv_obj_clear_flag(current_obj, LV_OBJ_FLAG_CLICKABLE);

            lv_obj_set_style_bg_opa(g_befObj, LV_OPA_0, 0);
            lv_obj_set_style_text_opa(g_befObj, LV_OPA_0, 0);
            lv_obj_set_style_border_opa(g_befObj, LV_OPA_0, 0);
            lv_obj_set_style_shadow_opa(g_befObj, LV_OPA_0, 0);
            lv_obj_clear_flag(g_befObj, LV_OBJ_FLAG_CLICKABLE);
        }
        else
        {
            lv_obj_set_style_text_opa(current_obj, LV_OPA_100, 0);
            lv_obj_set_style_text_opa(g_befObj, LV_OPA_0, 0);
        }

        g_befObj = current_obj;
    }
}


void lv_100ask_demo_memory(void)
{
	static lv_style_t cont_style;
	static lv_style_t obj_style;

    // 初始化随机数
    list_rand_number(list_number, OBJ_MAX_COUNT, OBJ_COUNT);

    // 使用PNG作为底图
	lv_obj_t * img = lv_img_create(lv_scr_act());
	lv_img_set_src(img, "./test.png");
	lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

	/* 整个容器的样式 */
	lv_style_init(&cont_style);
	lv_style_set_bg_opa(&cont_style, 0);
	lv_style_set_radius(&cont_style, 0);
	lv_style_set_pad_all(&cont_style, 0);  // 铺满

	/* 方块的样式 */
	lv_style_init(&obj_style);
	lv_style_set_radius(&obj_style, 0);
    lv_style_set_border_width(&obj_style, 1);
    lv_style_set_border_color(&obj_style, lv_color_hex(0xffffff));
    lv_style_set_text_opa(&obj_style, LV_OPA_0);
    //lv_style_set_bg_color(&obj_style, lv_color_hex(0xefddd5));
    lv_style_set_text_font(&obj_style, &lv_font_montserrat_40);

	/* Create a container with flex */
    lv_obj_t * cont = lv_obj_create(lv_scr_act());
    lv_obj_set_style_base_dir(cont, LV_BASE_DIR_LTR, 0);
    lv_obj_set_style_pad_row(cont, 0, 0);
    lv_obj_set_style_pad_column(cont, 0, 0);
    lv_obj_set_size(cont, LV_HOR_RES, LV_VER_RES);
    lv_obj_align(cont, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_add_style(cont, &cont_style, 0);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW_WRAP);
    //lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    uint32_t i;
    for(i = 0; i < OBJ_MAX_COUNT; i++) {
        g_obj[i] = lv_btn_create(cont);
        lv_obj_add_event_cb(g_obj[i], event_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_set_size(g_obj[i], (LV_HOR_RES-4) / OBJ_COUNT_HOR, LV_VER_RES / OBJ_COUNT_VER);
        lv_obj_add_style(g_obj[i], &obj_style, 0);

        lv_obj_t * label = lv_label_create(g_obj[i]);
        lv_label_set_text_fmt(label, "%d", list_number[i]);
        lv_obj_center(label);
    }
}


#endif /* LV_USE_100ASK_DEMO_GAME_MEMORY */
