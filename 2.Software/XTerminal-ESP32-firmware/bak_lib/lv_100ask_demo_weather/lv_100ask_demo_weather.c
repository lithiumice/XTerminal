
/**
 ******************************************************************************
 * @file    lv_100ask_demo_weather.c
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
 * @file lv_100ask_demo_weather.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_100ask_demo.h"

#if LV_USE_100ASK_DEMO_WEATHER

#include <stdio.h>
//#include <stdlib.h>
#include "lv_100ask_demo_weather.h"

/*********************
 *      DEFINES
 *********************/


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

#if 0
static lv_obj_t * meter1;
static lv_obj_t * create_meter_box(lv_obj_t * parent, const char * title, const char * text1, const char * text2, const char * text3)
{
    static lv_style_t style_title;
    static lv_style_t style_bullet;

    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title, &lv_font_montserrat_14);

    lv_style_init(&style_bullet);
    lv_style_set_border_width(&style_bullet, 0);
    lv_style_set_radius(&style_bullet, LV_RADIUS_CIRCLE);


    lv_obj_t * cont = lv_obj_create(parent);
    lv_obj_set_height(cont, LV_SIZE_CONTENT);
    lv_obj_set_flex_grow(cont, 1);

    lv_obj_t * title_label = lv_label_create(cont);
    lv_label_set_text(title_label, title);
    lv_obj_add_style(title_label, &style_title, 0);

    lv_obj_t * meter = lv_meter_create(cont);
    lv_obj_remove_style(meter, NULL, LV_PART_MAIN);
    lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);
    lv_obj_set_width(meter, LV_PCT(100));

    lv_obj_t * bullet1 = lv_obj_create(cont);
    lv_obj_set_size(bullet1, 13, 13);
    lv_obj_remove_style(bullet1, NULL, LV_PART_SCROLLBAR);
    lv_obj_add_style(bullet1, &style_bullet, 0);
    lv_obj_set_style_bg_color(bullet1, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_t * label1 = lv_label_create(cont);
    lv_label_set_text(label1, text1);

    lv_obj_t * bullet2 = lv_obj_create(cont);
    lv_obj_set_size(bullet2, 13, 13);
    lv_obj_remove_style(bullet2, NULL, LV_PART_SCROLLBAR);
    lv_obj_add_style(bullet2, &style_bullet, 0);
    lv_obj_set_style_bg_color(bullet2, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_obj_t * label2 = lv_label_create(cont);
    lv_label_set_text(label2, text2);

    lv_obj_t * bullet3 = lv_obj_create(cont);
    lv_obj_set_size(bullet3, 13, 13);
    lv_obj_remove_style(bullet3,  NULL, LV_PART_SCROLLBAR);
    lv_obj_add_style(bullet3, &style_bullet, 0);
    lv_obj_set_style_bg_color(bullet3, lv_palette_main(LV_PALETTE_GREEN), 0);
    lv_obj_t * label3 = lv_label_create(cont);
    lv_label_set_text(label3, text3);

#if 0
    static lv_coord_t grid_col_dsc[] = {LV_GRID_CONTENT, LV_GRID_FR(1), LV_GRID_CONTENT,LV_GRID_FR(8), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t grid_row_dsc[] = {LV_GRID_CONTENT, LV_GRID_FR(1), LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_grid_dsc_array(cont, grid_col_dsc, grid_row_dsc);
    lv_obj_set_grid_cell(title_label, LV_GRID_ALIGN_START, 0, 4, LV_GRID_ALIGN_START, 0, 1);
    lv_obj_set_grid_cell(meter, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 1, 3);
    lv_obj_set_grid_cell(bullet1, LV_GRID_ALIGN_START, 2, 1, LV_GRID_ALIGN_CENTER, 2, 1);
    lv_obj_set_grid_cell(bullet2, LV_GRID_ALIGN_START, 2, 1, LV_GRID_ALIGN_CENTER, 3, 1);
    lv_obj_set_grid_cell(bullet3, LV_GRID_ALIGN_START, 2, 1, LV_GRID_ALIGN_CENTER, 4, 1);
    lv_obj_set_grid_cell(label1, LV_GRID_ALIGN_STRETCH, 3, 1, LV_GRID_ALIGN_CENTER, 2, 1);
    lv_obj_set_grid_cell(label2, LV_GRID_ALIGN_STRETCH, 3, 1, LV_GRID_ALIGN_CENTER, 3, 1);
    lv_obj_set_grid_cell(label3, LV_GRID_ALIGN_STRETCH, 3, 1, LV_GRID_ALIGN_CENTER, 4, 1);

#endif
    static lv_coord_t grid_col_dsc[] = {LV_GRID_CONTENT, LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t grid_row_dsc[] = {LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(cont, grid_col_dsc, grid_row_dsc);
    lv_obj_set_grid_cell(title_label, LV_GRID_ALIGN_START, 0, 2, LV_GRID_ALIGN_START, 0, 1);
    lv_obj_set_grid_cell(meter, LV_GRID_ALIGN_START, 0, 2, LV_GRID_ALIGN_START, 1, 1);
    lv_obj_set_grid_cell(bullet1, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 2, 1);
    lv_obj_set_grid_cell(bullet2, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 3, 1);
    lv_obj_set_grid_cell(bullet3, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 4, 1);
    lv_obj_set_grid_cell(label1, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_START, 2, 1);
    lv_obj_set_grid_cell(label2, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_START, 3, 1);
    lv_obj_set_grid_cell(label3, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_START, 4, 1);


    return meter;

}

static void meter1_indic1_anim_cb(void * var, int32_t v)
{
    lv_meter_set_indicator_end_value(meter1, var, v);

    lv_obj_t * card = lv_obj_get_parent(meter1);
    lv_obj_t * label = lv_obj_get_child(card, -5);
    lv_label_set_text_fmt(label, "Revenue: %d %%", v);
}

static void meter1_indic2_anim_cb(void * var, int32_t v)
{
    lv_meter_set_indicator_end_value(meter1, var, v);

    lv_obj_t * card = lv_obj_get_parent(meter1);
    lv_obj_t * label = lv_obj_get_child(card, -3);
    lv_label_set_text_fmt(label, "Sales: %d %%", v);

}

static void meter1_indic3_anim_cb(void * var, int32_t v)
{
    lv_meter_set_indicator_end_value(meter1, var, v);

    lv_obj_t * card = lv_obj_get_parent(meter1);
    lv_obj_t * label = lv_obj_get_child(card, -1);
    lv_label_set_text_fmt(label, "Costs: %d %%", v);
}

static void lvgl_demo(void)
{
       lv_meter_scale_t * scale;
    lv_meter_indicator_t *indic;
    lv_obj_set_flex_flow(lv_scr_act(), LV_FLEX_FLOW_ROW_WRAP);
    meter1 = create_meter_box(lv_scr_act(), "Monthly Target", "Revenue: 63%", "Sales: 44%", "Costs: 58%");
    lv_obj_add_flag(lv_obj_get_parent(meter1), LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    scale = lv_meter_add_scale(meter1);
    lv_meter_set_scale_range(meter1, scale, 0, 100, 270, 90);
    lv_meter_set_scale_ticks(meter1, scale, 0, 0, 0, lv_color_black());

#if 1
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_values(&a, 20, 100);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);

    indic = lv_meter_add_arc(meter1, scale, 15, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_anim_set_exec_cb(&a, meter1_indic1_anim_cb);
    lv_anim_set_var(&a, indic);
    lv_anim_set_time(&a, 4100);
    lv_anim_set_playback_time(&a, 2700);
    lv_anim_start(&a);

    indic = lv_meter_add_arc(meter1, scale, 15, lv_palette_main(LV_PALETTE_RED), -20);
    lv_anim_set_exec_cb(&a, meter1_indic2_anim_cb);
    lv_anim_set_var(&a, indic);
    lv_anim_set_time(&a, 2600);
    lv_anim_set_playback_time(&a, 3200);
    a.user_data = indic;
    lv_anim_start(&a);

    indic = lv_meter_add_arc(meter1, scale, 15, lv_palette_main(LV_PALETTE_GREEN), -40);
    lv_anim_set_exec_cb(&a, meter1_indic3_anim_cb);
    lv_anim_set_var(&a, indic);
    lv_anim_set_time(&a, 2800);
    lv_anim_set_playback_time(&a, 1800);
    lv_anim_start(&a);
#endif

    lv_obj_set_size(meter1, 200, 200);
}
#endif


////////////////////////////////////
static lv_obj_t * meter;

#define WIN_HEADER_HEIGHT       (40)
#define WIN_BTN_WIDTH           (40)
static lv_obj_t * g_path_label;


static void set_value(void * indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter, indic, v);
}

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*
 *  函数名：   void lv_100ask_demo_weather(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用初始化入口
*/
void lv_100ask_demo_weather(void)
{
    // win风格样式
    static lv_style_t win_sytle;
    lv_style_init(&win_sytle);
    //lv_style_set_bg_opa(&win_sytle, 0);
    lv_style_set_radius(&win_sytle, 0);
    //lv_style_set_text_font(&win_sytle, &lv_font_montserrat_14);
    lv_style_set_bg_color(&win_sytle, lv_color_hex(0xff813f));

    // win中btn的风格样式
    static lv_style_t win_btn;
    lv_style_init(&win_btn);
    //lv_style_set_bg_opa(&win_btn, 0);
    lv_style_set_border_opa(&win_btn, 0);
    lv_style_set_outline_opa(&win_btn, 0);
    lv_style_set_radius(&win_btn, 12);
    lv_style_set_text_font(&win_btn, &lv_font_montserrat_14);

    // win展示区域风格样式
    static lv_style_t win_cont_style;
    lv_style_init(&win_cont_style);
    //lv_style_set_bg_opa(&win_cont_style, 0);
    //lv_style_set_border_opa(&win_cont_style, 0);
    lv_style_set_bg_color(&win_cont_style, lv_color_hex(0xffffff));
    lv_style_set_pad_column(&win_cont_style, 0);
    lv_style_set_pad_row(&win_cont_style, 0);
    lv_style_set_flex_flow(&win_cont_style, LV_FLEX_FLOW_ROW_WRAP);
    lv_style_set_pad_all(&win_cont_style, 0);
    lv_style_set_layout(&win_cont_style, LV_LAYOUT_FLEX);

    // 左侧菜单的风格样式
    static lv_style_t list_menu_style;
    lv_style_init(&list_menu_style);
    //lv_style_set_bg_color(&list_menu_style, lv_color_hex(0x222d36));
    lv_style_set_radius(&list_menu_style, 0);
    lv_style_set_pad_row(&list_menu_style, 5);
    lv_style_set_pad_all(&list_menu_style, 0);
    lv_style_set_text_font(&list_menu_style, &lv_font_montserrat_20);
    lv_style_set_border_opa(&list_menu_style, 0);

    // 左侧菜单按钮的风格样式
    static lv_style_t list_menu_btn;
    lv_style_init(&list_menu_btn);
    lv_style_set_bg_opa(&list_menu_btn, 0);
    lv_style_set_border_opa(&list_menu_btn, 0);
    lv_style_set_text_color(&list_menu_btn, lv_color_hex(0xffffff));

    // 右侧文件浏览区域的样式风格
    static lv_style_t file_list_style;
    lv_style_init(&file_list_style);
    //lv_style_set_bg_opa(&file_list_style, 0);
    //lv_style_set_border_opa(&file_list_style, 0);
    lv_style_set_pad_all(&file_list_style, 0);
    lv_style_set_radius(&file_list_style, 0);
    lv_style_set_text_font(&file_list_style, &lv_font_montserrat_20);
    //lv_style_set_text_color(&file_list_style, lv_color_hex(0xffffff));

    // 顶部按钮
    lv_obj_t * win = lv_win_create(lv_scr_act(), WIN_HEADER_HEIGHT);
    lv_obj_add_style(win, &win_sytle, 0);

    // 当前路径
    g_path_label = lv_win_add_title(win, "Path://");
    //lv_label_set_text(g_path_label, "中国 广东省 深圳市 天气概况");
    lv_label_set_text(g_path_label, "Shenzhen City, Guangdong Province, China     Weather");

    lv_obj_t * btn;
    btn = lv_win_add_btn(win, LV_SYMBOL_REFRESH, WIN_BTN_WIDTH);
    lv_obj_add_style(btn, &win_btn, 0);
    //lv_obj_add_event_cb(btn, click_menu_item_event_handler, LV_EVENT_CLICKED, "..");

    // 展示区域
    lv_obj_t * win_cont = lv_win_get_content(win);  /*Content can be aded here*/
    lv_obj_add_style(win_cont, &win_cont_style, 0);


    lv_obj_t * obj = lv_obj_create(win_cont);
    lv_obj_set_size(obj, LV_PCT(50), LV_PCT(50));
    lv_obj_set_style_border_opa(obj,0 ,0);
    lv_obj_set_style_pad_all(obj, 0, 0);


    lv_obj_t * obj2 = lv_obj_create(win_cont);
    lv_obj_set_size(obj2, LV_PCT(50), LV_PCT(50));
    lv_obj_set_style_border_opa(obj2,0 ,0);
    lv_obj_set_style_pad_all(obj2, 0, 0);

    meter = lv_meter_create(obj2);
    lv_obj_center(meter);
    lv_obj_set_size(meter, 200, 200);

    /*Remove the circle from the middle*/
    lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);

    /*Add a scale first*/
    lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 11, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter, scale, 1, 2, 30, lv_color_hex3(0xeee), 10);
    lv_meter_set_scale_range(meter, scale, 0, 100, 270, 90);

    /*Add a three arc indicator*/
    lv_meter_indicator_t * indic1 = lv_meter_add_arc(meter, scale, 10, lv_palette_main(LV_PALETTE_RED), 0);
    lv_meter_indicator_t * indic2 = lv_meter_add_arc(meter, scale, 10, lv_palette_main(LV_PALETTE_GREEN), -10);
    lv_meter_indicator_t * indic3 = lv_meter_add_arc(meter, scale, 10, lv_palette_main(LV_PALETTE_BLUE), -20);

    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_set_repeat_delay(&a, 100);
    lv_anim_set_playback_delay(&a, 100);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);

    lv_anim_set_time(&a, 2000);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_var(&a, indic1);
    lv_anim_start(&a);

    lv_anim_set_time(&a, 1000);
    lv_anim_set_playback_time(&a, 1000);
    lv_anim_set_var(&a, indic2);
    lv_anim_start(&a);

    lv_anim_set_time(&a, 1000);
    lv_anim_set_playback_time(&a, 2000);
    lv_anim_set_var(&a, indic3);
    lv_anim_start(&a);

    // 天气信息表格
    lv_obj_t * table = lv_table_create(win_cont);
    lv_obj_set_size(table, LV_PCT(50), LV_PCT(50));
    lv_obj_set_style_border_opa(table,0 ,0);
    lv_obj_set_style_pad_all(table, 0, 0);

    lv_table_set_col_width(table, 0, 400);  // 150
    lv_table_set_col_width(table, 1, 100);  // 800

    /*Fill the first column*/
    lv_table_set_cell_value(table, 0, 0, "H&L");
    lv_table_set_cell_value(table, 1, 0, "shidu");
    lv_table_set_cell_value(table, 2, 0, "qiya");
    lv_table_set_cell_value(table, 3, 0, "nengjiandu");

    /*Fill the second column*/
    lv_table_set_cell_value(table, 0, 1, "Price");
    lv_table_set_cell_value(table, 1, 1, "$7");
    lv_table_set_cell_value(table, 2, 1, "$4");
    lv_table_set_cell_value(table, 3, 1, "$6");

    //////
    lv_obj_t * table2 = lv_table_create(win_cont);
    lv_obj_set_size(table2, LV_PCT(50), LV_PCT(50));
    lv_obj_set_style_border_opa(table2,0 ,0);
    lv_obj_set_style_pad_all(table2, 0, 0);

    lv_table_set_col_width(table2, 0, 400);  // 150
    lv_table_set_col_width(table2, 1, 100);  // 800

    /*Fill the first column*/
    lv_table_set_cell_value(table2, 0, 0, "win");
    lv_table_set_cell_value(table2, 1, 0, "win_speed");
    lv_table_set_cell_value(table2, 2, 0, "win_meter");
    lv_table_set_cell_value(table2, 3, 0, "nengjiandu");

    /*Fill the second column*/
    lv_table_set_cell_value(table2, 0, 1, "Price");
    lv_table_set_cell_value(table2, 1, 1, "$7");
    lv_table_set_cell_value(table2, 2, 1, "$4");
    lv_table_set_cell_value(table2, 3, 1, "$6");

}


#endif /* LV_USE_100ASK_DEMO_GAME_TRON*/
