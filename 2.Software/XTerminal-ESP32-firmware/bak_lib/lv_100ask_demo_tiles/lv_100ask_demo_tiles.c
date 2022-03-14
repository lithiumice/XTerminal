
/**
 ******************************************************************************
 * @file    lv_100ask_demo_tiles.c
 * @author  百问科技
 * @version V1.0
 * @date    2021-10-17
 * @brief	将数字滑动到位的拼图游戏
 *          单击靠近空正方形的方格以交换位置。你能把方格从左到右，从下到上顺序摆放吗？
 ******************************************************************************
 * Change Logs:
 * Date           Author          Notes
 * 2021-10-16     zhouyuebiao     First version
 ******************************************************************************
 * @attention
 *
 * Copyright (C) 2008-2021 深圳百问网科技有限公司<https://www.100ask.net/>
 * All rights reserved
 *
 ******************************************************************************
 */
/**
 * @file lv_100ask_demo_tiles.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_100ask_demo.h"

#if LV_USE_100ASK_DEMO_GAME_TILES

#include <stdio.h>
#include <stdlib.h>
#include "lv_100ask_demo_tiles.h"

/*********************
 *      DEFINES
 *********************/
#define OBJ_COUNT_HOR   (4)
#define OBJ_COUNT_VER   (4)
#define OBJ_MAX_COUNT   ((OBJ_COUNT_HOR * OBJ_COUNT_VER))
#define OBJ_RAND_COUNT  ((OBJ_COUNT_HOR * OBJ_COUNT_VER) - 1)

/**********************
 *      TYPEDEFS
 **********************/


/**********************
 *  STATIC VARIABLES
 **********************/
//static int g_rand_number[OBJ_COUNT_HOR][OBJ_COUNT_VER] = {0};
static int g_rand_number[OBJ_COUNT_HOR][OBJ_COUNT_VER] = {{1,2},{3,0}};
static lv_obj_t * g_obj[OBJ_COUNT_HOR][OBJ_COUNT_VER];   /* 方块 */
static lv_obj_t * g_game_win;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void init_list_rand_number(void);
static void get_list_rand_number(int arry[], int max_count, int count);
static void load_resoure(void);
static void game_win_tip(void);
static bool check_sort(void);

static void game_win_event_cb(lv_event_t * e);
static void event_handler(lv_event_t * e);




/**********************
 *   STATIC FUNCTIONS
 **********************/

static void game_win_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_current_target(e);
    LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));

    init_list_rand_number();
    load_resoure();
}

static void game_win_tip(void)
{
    static const char * btns[] ={"Play again", "Quit", ""};

    g_game_win = lv_msgbox_create(lv_scr_act(), "victory", "That is great! You win!", btns, true);
    lv_obj_move_background(g_game_win);
    //lv_obj_move_foreground(g_game_win);
    lv_obj_add_event_cb(g_game_win, game_win_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_center(g_game_win);
}


static void init_list_rand_number(void)
{
    int tmp_rand_number[OBJ_MAX_COUNT] = {0};

    get_list_rand_number(tmp_rand_number, OBJ_RAND_COUNT, OBJ_RAND_COUNT);

    int row, col;
    /* 一维数组转为二维数组 */
    for(row = 0; row < OBJ_COUNT_VER; row++)
        for(col = 0; col < OBJ_COUNT_VER; col++)
            g_rand_number[row][col] = tmp_rand_number[((row * OBJ_COUNT_VER) + col)];
}


// 生成个数为max_count的指定count范围内count个只重复一次的随机数的算法
static void get_list_rand_number(int arry[], int max_count, int count)
{
	int w, t;

	srand((unsigned)time(NULL));
	for (int i = 0; i < max_count; i++)
	    arry[i] = i + 1;
	for (int i = 0; i < max_count; i++)
	{
		w = rand() % (count - i) + i;
	    t = arry[i];
	    arry[i] = arry[w];
	    arry[w] = t;
	}
}

static void load_resoure(void)
{
    static lv_style_t cont_style;
	static lv_style_t obj_style;
	static lv_style_t extra_obj_style;

    /* 整个容器的样式 */
    lv_style_init(&cont_style);
	lv_style_set_bg_opa(&cont_style, 0);
	lv_style_set_radius(&cont_style, 0);
	lv_style_set_pad_all(&cont_style, 0);  // 铺满

    /* 正常方块样式 */
	lv_style_init(&obj_style);
	lv_style_set_radius(&obj_style, 0);
    lv_style_set_border_width(&obj_style, 1);
    lv_style_set_border_color(&obj_style, lv_color_hex(0xffffff));
    //lv_style_set_text_opa(&obj_style, LV_OPA_0);
    //lv_style_set_bg_color(&obj_style, lv_color_hex(0xefddd5));
    lv_style_set_text_font(&obj_style, &lv_font_montserrat_40);

    /* 多出的一个方块样式 */
	lv_style_init(&extra_obj_style);
	lv_style_set_radius(&extra_obj_style, 0);
    lv_style_set_border_width(&extra_obj_style, 1);
    lv_style_set_border_color(&extra_obj_style, lv_color_hex(0xffffff));
    lv_style_set_bg_color(&extra_obj_style, lv_color_hex(0xefddd5));
    lv_style_set_text_font(&extra_obj_style, &lv_font_montserrat_40);
    lv_style_set_text_opa(&extra_obj_style, LV_OPA_0);

	/* Create a container with flex */
    lv_obj_t * cont = lv_obj_create(lv_scr_act());
    //lv_obj_set_style_base_dir(cont, LV_BASE_DIR_LTR, 0);
    lv_obj_set_style_pad_row(cont, 0, 0);
    lv_obj_set_style_pad_column(cont, 0, 0);
    lv_obj_set_size(cont, LV_HOR_RES, LV_VER_RES);
    lv_obj_align(cont, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_add_style(cont, &cont_style, 0);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW_WRAP);

    uint32_t row, col;
    for(row = 0; row < OBJ_COUNT_VER; row++)
    {
        for(col = 0; col < OBJ_COUNT_VER; col++)
        {
            g_obj[row][col] = lv_btn_create(cont);
            lv_obj_add_event_cb(g_obj[row][col], event_handler, LV_EVENT_CLICKED, NULL);
            lv_obj_set_size(g_obj[row][col], (LV_HOR_RES - 4) / OBJ_COUNT_HOR, LV_VER_RES / OBJ_COUNT_VER);
            if (0 == g_rand_number[row][col])   lv_obj_add_style(g_obj[row][col], &extra_obj_style, 0);
            else    lv_obj_add_style(g_obj[row][col], &obj_style, 0);

            lv_obj_add_style(g_obj[row][col], &obj_style, 0);

            lv_obj_t * label = lv_label_create(g_obj[row][col]);
            lv_label_set_text_fmt(label, "%d", g_rand_number[row][col]);
            lv_obj_center(label);
        }
    }
}


static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_CLICKED)
    {
        int click_number = 0, str_count, str_len;
        char * tmp_str_click_number = lv_label_get_text(lv_obj_get_child(obj, 0));

        // 将点击的数字字符串转为整型
        // click_number = atoi(tmp_str_click_number);  // 使用标准库函数
        for(str_count = 0, str_len = strlen(tmp_str_click_number); str_count < str_len; str_count++)
        {
            click_number = (click_number * (str_count * 10)) + (tmp_str_click_number[str_count] - '0');
        }
        //printf("%d\n", click_number);

        int click_row, click_col;
        int row, col;
        // 第一次遍历，找出选中方块的位置
        for(row = 0; row < OBJ_COUNT_VER; row++)
        {
            for(col = 0; col < OBJ_COUNT_VER; col++)
            {
                if(click_number == g_rand_number[row][col])
                {
                    click_row = row;
                    click_col = col;
                    break;
                }
            }
        }

        // 第二次遍历，找出空白方块的位置
        for(row = 0; row < OBJ_COUNT_VER; row++)
        {
            for(col = 0; col < OBJ_COUNT_VER; col++)
            {
                if(0 == g_rand_number[row][col])
                {
                    if (((abs(click_row - row) != 1) || (abs(click_col - col) != 1)) &&
                        ((abs(click_row - row) == 0) || (abs(click_row - row) == 1)) &&
                        ((abs(click_col - col) == 0) || (abs(click_col - col) == 1)))
                    {
                        int tmp_number;
                        tmp_number = g_rand_number[row][col];
                        g_rand_number[row][col] = g_rand_number[click_row][click_col];
                        g_rand_number[click_row][click_col] = tmp_number;
                        load_resoure();
                    }
                }
            }
        }
        if (check_sort() == 1)
            lv_obj_move_foreground(g_game_win);
    }
}


static bool check_sort(void)
{
    int row, col, count = 0, ret = 0;
    int buffer[OBJ_COUNT_VER*OBJ_COUNT_VER] = {0};

    for(row = 0; row < OBJ_COUNT_VER; row++)
    {
        for(col = 0; col < OBJ_COUNT_VER; col++)
        {
            buffer[count++] = g_rand_number[row][col];
        }
    }

    printf("\n\n-----------------\n");

    for (count = 0; count < ((OBJ_COUNT_VER*OBJ_COUNT_VER) - 2); count++)
    {
        printf("%d ", buffer[count]);
        if (buffer[count] < buffer[count+1])
            ret = 1;
        else
        {
            printf("\nelse:%d ", buffer[count]);
            ret = 0;
            break;
        }
    }
    printf("\n\n");
    return ret;
}


/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*
 *  函数名：   void lv_100ask_demo_tiles(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用初始化入口
*/
void lv_100ask_demo_tiles(void)
{
    // 初始化随机数
    init_list_rand_number();
    load_resoure();
    game_win_tip();
}


#endif /* LV_USE_100ASK_DEMO_GAME_TRON*/
