
/**
 ******************************************************************************
 * @file    lv_100ask_demo_about.c
 * @author  百问科技
 * @version V1.0
 * @date    2021-11-06
 * @brief	天气
 ******************************************************************************
 * Change Logs:
 * Date           Author          Notes
 * 2021-11-06     zhouyuebiao     First version
 ******************************************************************************
 * @attention
 *
 * Copyright (C) 2008-2021 深圳百问网科技有限公司<https://www.100ask.net/>
 * All rights reserved
 *
 ******************************************************************************
 */
/**
 * @file lv_100ask_demo_about.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_100ask_demo.h"

#if LV_USE_100ASK_DEMO_ABOUT_US

#include <stdio.h>
//#include <stdlib.h>
//#include "lv_lib_qrcode/lv_qrcode.h"  //config lv_conf.h: #define LV_USE_QRCODE 1
#include "lv_100ask_demo_about.h"

/*********************
 *      DEFINES
 *********************/
#define QRCODE_PANEL_SIZE   (300)
#define QRCODE_SIZE         (200)
/**********************
 *      TYPEDEFS
 **********************/


/**********************
 *  STATIC VARIABLES
 **********************/


/**********************
 *  STATIC PROTOTYPES
 **********************/


/**********************
 *   STATIC FUNCTIONS
 **********************/
static void close_panel_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);    // 获取事件代码
    lv_obj_t * panel = lv_event_get_user_data(e);      // 获取在对象上注册事件时传递的 user_data

    if ((code == LV_EVENT_CLICKED))
    {
        lv_obj_del(panel);           // 删除对象及其所有子对象
        lv_obj_remove_event_cb(lv_layer_top(), close_panel_event_cb);   // 删除对象的事件处理函数(lv_layer_top层)
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);   // 清除标志(lv_layer_top层)
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);  // 设置透明度(lv_layer_top层)
    }
}


/* Create QR code */
static void create_qrcode(lv_obj_t* parent, const char * data)
{
    lv_color_t bg_color = lv_palette_lighten(LV_PALETTE_LIGHT_BLUE, 5);
    lv_color_t fg_color = lv_palette_darken(LV_PALETTE_BLUE, 4);

    lv_obj_t * qr = lv_qrcode_create(parent, QRCODE_SIZE, fg_color, bg_color);

    /*Set data*/
    lv_qrcode_update(qr, data, strlen(data));
    lv_obj_center(qr);

    /*Add a border with bg_color*/
    lv_obj_set_style_border_color(qr, bg_color, 0);
    lv_obj_set_style_border_width(qr, 5, 0);

    lv_obj_center(qr);
}

static void create_show_qrcode_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);    // 获取事件代码
    const char *str = lv_event_get_user_data(e);      // 获取在对象上注册事件时传递的 user_data

    if ((code == LV_EVENT_CLICKED))
    {
        lv_obj_t * obj_qrcode_panel = lv_obj_create(lv_layer_top());               // 在 lv_layer_top 层
        lv_obj_set_size(obj_qrcode_panel, QRCODE_PANEL_SIZE, QRCODE_PANEL_SIZE);        // 设置对象大小
        lv_obj_align(obj_qrcode_panel, LV_ALIGN_CENTER, 0, 0);                         // 设置对象对齐、偏移

        /* Create a QR code */
        create_qrcode(obj_qrcode_panel, str);

#if 1
        lv_obj_t * label = lv_label_create(obj_qrcode_panel);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
        lv_obj_set_width(label, (QRCODE_PANEL_SIZE - 50));
        //lv_style_set_text_color(label, lv_palette_main(LV_PALETTE_GREEN));
        //lv_style_set_text_font(label, &lv_font_montserrat_10);
        //lv_style_set_text_decor(label, LV_TEXT_DECOR_UNDERLINE);
        lv_label_set_text(label, str);
        lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);                         // 设置对象对齐、偏移
#endif
        lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);                         // 使能 lv_layer_top 点击
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_50, 0);                          // 设置对象透明度
        lv_obj_set_style_bg_color(lv_layer_top(), lv_palette_main(LV_PALETTE_GREY), 0); // 设置对象颜色

        //lv_obj_add_event_cb(obj_qrcode_panel, close_panel_event_cb, LV_EVENT_VALUE_CHANGED, ta);   // 给对象分配事件
        lv_obj_add_event_cb(lv_layer_top(), close_panel_event_cb, LV_EVENT_CLICKED, obj_qrcode_panel); // 给对象分配事件(lv_layer_top层分配点击回调处理函数)

    }

}


/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*
 *  函数名：   void lv_100ask_demo_about(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用初始化入口
*/
void lv_100ask_demo_about(void)
{

    lv_obj_t * obj_layout;
    lv_obj_t * info_list1;
    lv_obj_t * info_list2;
    lv_obj_t * info_list3;
    static lv_style_t obj_layout_style;   // 容器的样式

    lv_style_init(&obj_layout_style);
    //lv_style_set_pad_all(&obj_layout_style, 0);
    //lv_style_set_bg_opa(&obj_layout_style, 0);
    //lv_style_set_shadow_opa(&obj_layout_style, 0);
    lv_style_set_border_opa(&obj_layout_style, 0);

    /* Layout Init */
    obj_layout = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj_layout,  LV_PCT(100), LV_PCT(100));
    lv_obj_set_layout(obj_layout, LV_LAYOUT_FLEX);
    lv_obj_set_style_base_dir(obj_layout, LV_BASE_DIR_RTL, 0);
    lv_obj_set_flex_flow(obj_layout, LV_FLEX_FLOW_COLUMN);
    lv_obj_center(obj_layout);
    lv_obj_add_style(obj_layout, &obj_layout_style, 0);

    /* Create title */
    lv_obj_t * label_title = lv_label_create(obj_layout);
    lv_obj_set_width(label_title, LV_PCT(100));
    lv_obj_set_style_text_font(label_title, &lv_font_montserrat_32, 0);
    lv_obj_set_style_text_align(label_title, LV_TEXT_ALIGN_CENTER, 0);
    //lv_label_set_recolor(label_title, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label_title, "ABOUT");
    lv_obj_align(label_title, LV_ALIGN_CENTER, 0, 0); //lv_obj_center(label_title);

#if LV_100ASK_IMX6ULL_PRO
    lv_obj_t * btn;

    /* Create info list1 */
    info_list1 = lv_list_create(obj_layout);
    //lv_obj_set_style_text_align(info_list1, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_size(info_list1, LV_PCT(100), LV_PCT(42));
    lv_obj_center(info_list1);

    /* Add buttons to the list */
    lv_list_add_text(info_list1, "Hardware Specifications");
    btn = lv_list_add_btn(info_list1, "\xef""100ASK_IMX6ULL_Pro  "LV_SYMBOL_RIGHT, "Name");
    lv_obj_add_event_cb(btn, create_show_qrcode_event_cb, LV_EVENT_CLICKED, "https://download.100ask.org/boards/Nxp/100ask_imx6ull_pro/index.html");
    lv_list_add_btn(info_list1, "\xef""ARM Cortex-A 800M", "CPU");
    lv_list_add_btn(info_list1, "\xef""512MB DDR3L", "Memory");
    lv_list_add_btn(info_list1, "\xef""4GB EMMC FLASH", "FLASH");
    lv_list_add_btn(info_list1, "\xef""7-inch(1024x600) RGB", "Screen");

    /* Create info list2 */
    info_list2 = lv_list_create(obj_layout);
    //lv_obj_set_style_text_align(info_list2, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_size(info_list2, LV_PCT(100), LV_PCT(42));
    lv_obj_center(info_list2);

    /*Add buttons to the list*/
    lv_list_add_text(info_list2, "Software Specifications");
    lv_list_add_btn(info_list2, "\xef""100ASK Linux GUI(POWER BY LVGL)", "Name");
    lv_list_add_btn(info_list2, "\xef""V2.0", "Version");
    lv_list_add_btn(info_list2, "\xef""2021-11-11", "Updated");
    btn = lv_list_add_btn(info_list2, LV_SYMBOL_EYE_OPEN" https://www.100ask.net  "LV_SYMBOL_RIGHT, "Source code");
    lv_obj_add_event_cb(btn, create_show_qrcode_event_cb, LV_EVENT_CLICKED, "https://www.100ask.net");
    lv_list_add_btn(info_list2, LV_SYMBOL_WARNING" Copyright @ 2019-2021 Shenzhen Baiwenwang Technology Co., Ltd. All Rights Reserved.", "Copyright");

    /* Create info list3 */
    info_list3 = lv_list_create(obj_layout);
    //lv_obj_set_style_text_align(info_list3, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_size(info_list3, LV_PCT(100), LV_PCT(78));
    lv_obj_center(info_list3);

    /*Add buttons to the list*/
    lv_list_add_text(info_list3, "About the Authors");
    lv_list_add_btn(info_list3, "\xef""Shenzhen Baiwenwang Technology Co., Ltd.(weidongshan)", "Name");
    lv_list_add_btn(info_list3, LV_SYMBOL_CALL" 0755-86200561", "Phone");
    btn = lv_list_add_btn(info_list3, LV_SYMBOL_HOME" https://www.100ask.net  "LV_SYMBOL_RIGHT, "Official website");
    lv_obj_add_event_cb(btn, create_show_qrcode_event_cb, LV_EVENT_CLICKED, "https://www.100ask.net");
    btn = lv_list_add_btn(info_list3, "\xef""baiwenkeji  "LV_SYMBOL_RIGHT, "WeChat");
    lv_obj_add_event_cb(btn, create_show_qrcode_event_cb, LV_EVENT_CLICKED, "http://weixin.qq.com/r/M0hvd2-EwjK9rSsU9x0h");
    btn = lv_list_add_btn(info_list3, "\xef""https://download.100ask.org  "LV_SYMBOL_RIGHT, "Data Download Center");
    lv_obj_add_event_cb(btn, create_show_qrcode_event_cb, LV_EVENT_CLICKED, "https://download.100ask.org");
    btn = lv_list_add_btn(info_list3, "\xef""http://bbs.100ask.net  "LV_SYMBOL_RIGHT, "Forum");
    lv_obj_add_event_cb(btn, create_show_qrcode_event_cb, LV_EVENT_CLICKED, "http://bbs.100ask.net");
    btn = lv_list_add_btn(info_list3, "\xef""https://100ask.taobao.com  "LV_SYMBOL_RIGHT, "Taobao");
    lv_obj_add_event_cb(btn, create_show_qrcode_event_cb, LV_EVENT_CLICKED, "https://100ask.taobao.com");
    btn = lv_list_add_btn(info_list3, "\xef""https://weidongshan.tmall.com  "LV_SYMBOL_RIGHT, "Tmall");
    lv_obj_add_event_cb(btn, create_show_qrcode_event_cb, LV_EVENT_CLICKED, "https://weidongshan.tmall.com");
    btn = lv_list_add_btn(info_list3, "\xef""https://blog.csdn.net/thisway_diy  "LV_SYMBOL_RIGHT, "CSDN");
    lv_obj_add_event_cb(btn, create_show_qrcode_event_cb, LV_EVENT_CLICKED, "https://blog.csdn.net/thisway_diy");
    btn = lv_list_add_btn(info_list3, "\xef""https://space.bilibili.com/275908810  "LV_SYMBOL_RIGHT, "Bilibili");
    lv_obj_add_event_cb(btn, create_show_qrcode_event_cb, LV_EVENT_CLICKED, "https://space.bilibili.com/275908810");
#endif // LV_100ASK_IMX6ULL_PRO

    lv_obj_t * spans = lv_spangroup_create(obj_layout);
    lv_obj_set_size(spans, LV_PCT(100), LV_PCT(30));

    lv_spangroup_set_align(spans, LV_TEXT_ALIGN_LEFT);
    lv_spangroup_set_overflow(spans, LV_SPAN_OVERFLOW_CLIP);
    lv_spangroup_set_indent(spans, 20);
    lv_spangroup_set_mode(spans, LV_SPAN_MODE_BREAK);

    lv_span_t * span = lv_spangroup_new_span(spans);
    lv_span_set_text_static(span, "\nhttps://www.100ask.net");
    lv_style_set_text_color(&span->style, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_text_decor(&span->style, LV_TEXT_DECOR_UNDERLINE);
    lv_style_set_text_opa(&span->style, LV_OPA_70);

    span = lv_spangroup_new_span(spans);
    lv_span_set_text_static(span, "\nCopyright @ 2019-2021 Shenzhen Baiwenwang Technology Co., Ltd. All Rights Reserved.");
    lv_style_set_text_opa(&span->style, LV_OPA_70);

}


#endif /* LV_USE_100ASK_DEMO_GAME_TRON*/
