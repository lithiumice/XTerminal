/**
 ******************************************************************************
 * @file    lv_100ask_demo_2048.c
 * @author  百问科技
 * @version V1.0
 * @date    2021-09-16
 * @brief	贪吃蛇小游戏
 ******************************************************************************
 * Change Logs:
 * Date           Author          Notes
 * 2021-09-16     zhouyuebiao     First version
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
// #include "../../lv_100ask_demo.h"

// #if LV_USE_100ASK_DEMO_GAME_2048

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lv_100ask_demo_2048.h"

/*********************
 *      DEFINES
 *********************/
#define SIZE 4

/* 2048 Sizes */
#define LV_100ASK_2048_GAME_BOX_W (200)
#define LV_100ASK_2048_GAME_BOX_H (200)//200*200*(16/8)B=200*200/1024KB
#define LV_100ASK_2048_NUMBER_BOX_W (30)
#define LV_100ASK_2048_NUMBER_BOX_H (30)
// #define LV_100ASK_2048_CURRENT_SCORE_W			(135)
// #define LV_100ASK_2048_CURRENT_SCORE_H			(75)
// #define LV_100ASK_2048_BEST_SCORE_W				(135)
// #define LV_100ASK_2048_BEST_SCORE_H				(75)

// 2048»­¿òÑÕÉ«
#define LV_100ASK_2048_GAME_BG_COLOR lv_color_hex(0xfaf8ef) // LV_COLOR_MAKE(0xCD, 0xC1, 0xB4)
#define LV_100ASK_2048_GAME_BOX_COLOR lv_color_hex(0xBBADA0)
#define LV_100ASK_2048_NUMBER_BOX_COLOR lv_color_hex(0xCDC1B4)
#define LV_100ASK_2048_NUMBER_2_COLOR lv_color_hex(0xeee4da)
#define LV_100ASK_2048_NUMBER_4_COLOR lv_color_hex(0xeee1c9)
#define LV_100ASK_2048_NUMBER_8_COLOR lv_color_hex(0xf3b27a)
#define LV_100ASK_2048_NUMBER_16_COLOR lv_color_hex(0xf69664)
#define LV_100ASK_2048_NUMBER_32_COLOR lv_color_hex(0xf77c5f)
#define LV_100ASK_2048_NUMBER_64_COLOR lv_color_hex(0xf75f3b)
#define LV_100ASK_2048_NUMBER_128_COLOR lv_color_hex(0xedd073)
#define LV_100ASK_2048_NUMBER_256_COLOR lv_color_hex(0xEDCC61)
#define LV_100ASK_2048_NUMBER_512_COLOR lv_color_hex(0xEDCC61)
#define LV_100ASK_2048_NUMBER_1024_COLOR lv_color_hex(0xEDCC61)
#define LV_100ASK_2048_NUMBER_2048_COLOR lv_color_hex(0xEDC22E)

/**********************
 *  STATIC VARIABLES
 **********************/
bool play_game = true;
static uint8_t game_2048_board[SIZE][SIZE];
static uint32_t game_2048_current_score = 0;
static lv_obj_t *game_2048_canvas;
// static lv_obj_t *game_2048_best_score;
// static lv_obj_t *game_2048_current_score_text;
// static lv_indev_t * play_2048_indev;
static lv_obj_t *root;
static void *cbuf;
// static struct NUMBER_BOX** s_number_cbuf;
// static struct NUMBER_BOX s_number_cbuf[SIZE][SIZE];

// struct NUMBER_BOX
// {
// 	lv_color_t number_cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(LV_100ASK_2048_NUMBER_BOX_W, LV_100ASK_2048_NUMBER_BOX_H)];
// };
	lv_color_t number_cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(LV_100ASK_2048_NUMBER_BOX_W, LV_100ASK_2048_NUMBER_BOX_H)];

 void play_2048_event_cb(lv_obj_t *obj, lv_event_t e);
 void initBoard(lv_obj_t *parent, uint8_t board[SIZE][SIZE]);
 void initBoardNumber(uint8_t board[SIZE][SIZE]);
 void drawBoard(lv_obj_t *parent, lv_color_t *cbuf, char *number,
				  uint16_t canvas_w, uint16_t canvas_h,
				  uint16_t rect_dsc_x, uint16_t rect_dsc_y,
				  lv_color_t rgb32);
 void addRandom(uint8_t board[SIZE][SIZE]);
 lv_color_t Num2Color(uint32_t num);
 uint8_t findTarget(uint8_t array[SIZE], uint8_t x, uint8_t stop);
 bool slideArray(uint8_t array[SIZE]);
 void rotateBoard(uint8_t board[SIZE][SIZE]);
 bool moveUp(uint8_t board[SIZE][SIZE]);
 bool moveLeft(uint8_t board[SIZE][SIZE]);
 bool moveDown(uint8_t board[SIZE][SIZE]);
 bool moveRight(uint8_t board[SIZE][SIZE]);
 bool findPairDown(uint8_t board[SIZE][SIZE]);
 uint8_t countEmpty(uint8_t board[SIZE][SIZE]);
 bool gameEnded(uint8_t board[SIZE][SIZE]);
 char *Int2String(int num, char *str);

 void initBoardNumber(uint8_t board[SIZE][SIZE])
{
	uint8_t x, y;
	for (x = 0; x < SIZE; x++)
	{
		for (y = 0; y < SIZE; y++)
		{
			board[x][y] = 0;
		}
	}

	/* 初始化两个随机位置的随机数 */
	addRandom(board);
	addRandom(board);

	game_2048_current_score = 0;
}

void addRandom(uint8_t board[SIZE][SIZE])
{
	static bool initialized = false;
	uint8_t x, y;
	uint8_t r, len = 0;
	uint8_t n, list[SIZE * SIZE][2];

	if (!initialized)
	{
		srand(time(NULL));
		initialized = true;
	}

	for (x = 0; x < SIZE; x++)
	{
		for (y = 0; y < SIZE; y++)
		{
			if (board[x][y] == 0)
			{
				list[len][0] = x;
				list[len][1] = y;
				len++;
			}
		}
	}

	if (len > 0)
	{
		r = rand() % len;
		x = list[r][0];
		y = list[r][1];
		n = (rand() % 10) / 9 + 1;
		board[x][y] = n;
	}
}

 lv_color_t Num2Color(uint32_t num)
{
	switch (num)
	{
	case 2:
		return LV_100ASK_2048_NUMBER_2_COLOR;
		break;
	case 4:
		return LV_100ASK_2048_NUMBER_4_COLOR;
		break;
	case 8:
		return LV_100ASK_2048_NUMBER_8_COLOR;
		break;
	case 16:
		return LV_100ASK_2048_NUMBER_16_COLOR;
		break;
	case 32:
		return LV_100ASK_2048_NUMBER_32_COLOR;
		break;
	case 64:
		return LV_100ASK_2048_NUMBER_64_COLOR;
		break;
	case 128:
		return LV_100ASK_2048_NUMBER_128_COLOR;
		break;
	case 256:
		return LV_100ASK_2048_NUMBER_256_COLOR;
		break;
	case 512:
		return LV_100ASK_2048_NUMBER_512_COLOR;
		break;
	case 1024:
		return LV_100ASK_2048_NUMBER_1024_COLOR;
		break;
	case 2048:
		return LV_100ASK_2048_NUMBER_2048_COLOR;
		break;
	default:
		return LV_100ASK_2048_NUMBER_2048_COLOR;
		break;
	}
}

 uint8_t findTarget(uint8_t array[SIZE], uint8_t x, uint8_t stop)
{
	uint8_t t;
	// if the position is already on the first, don't evaluate
	if (x == 0)
	{
		return x;
	}
	for (t = x - 1;; t--)
	{
		if (array[t] != 0)
		{
			if (array[t] != array[x])
			{
				// merge is not possible, take next position
				return t + 1;
			}
			return t;
		}
		else
		{
			// we should not slide further, return this one
			if (t == stop)
			{
				return t;
			}
		}
	}
	// we did not find a
	return x;
}

 bool slideArray(uint8_t array[SIZE])
{
	bool success = false;
	uint8_t x, t, stop = 0;

	for (x = 0; x < SIZE; x++)
	{
		if (array[x] != 0)
		{
			t = findTarget(array, x, stop);
			// if target is not original position, then move or merge
			if (t != x)
			{
				// if target is zero, this is a move
				if (array[t] == 0)
				{
					array[t] = array[x];
				}
				else if (array[t] == array[x])
				{
					// merge (increase power of two)
					array[t]++;
					// increase score
					game_2048_current_score += (uint32_t)1 << array[t];
					// set stop to avoid double merge
					stop = t + 1;
				}
				array[x] = 0;
				success = true;
			}
		}
	}
	return success;
}

void rotateBoard(uint8_t board[SIZE][SIZE])
{
	uint8_t i, j, n = SIZE;
	uint8_t tmp;
	for (i = 0; i < n / 2; i++)
	{
		for (j = i; j < n - i - 1; j++)
		{
			tmp = board[i][j];
			board[i][j] = board[j][n - i - 1];
			board[j][n - i - 1] = board[n - i - 1][n - j - 1];
			board[n - i - 1][n - j - 1] = board[n - j - 1][i];
			board[n - j - 1][i] = tmp;
		}
	}
}

 bool moveUp(uint8_t board[SIZE][SIZE])
{
	bool success = false;
	uint8_t x;
	for (x = 0; x < SIZE; x++)
	{
		success |= slideArray(board[x]);
	}
	return success;
}

bool moveLeft(uint8_t board[SIZE][SIZE])
{
	bool success;
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	return success;
}

 bool moveDown(uint8_t board[SIZE][SIZE])
{
	bool success;
	rotateBoard(board);
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	rotateBoard(board);
	return success;
}

bool moveRight(uint8_t board[SIZE][SIZE])
{
	bool success;
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	return success;
}

bool findPairDown(uint8_t board[SIZE][SIZE])
{
	bool success = false;
	uint8_t x, y;
	for (x = 0; x < SIZE; x++)
	{
		for (y = 0; y < SIZE - 1; y++)
		{
			if (board[x][y] == board[x][y + 1])
				return true;
		}
	}
	return success;
}

uint8_t countEmpty(uint8_t board[SIZE][SIZE])
{
	uint8_t x, y;
	uint8_t count = 0;
	for (x = 0; x < SIZE; x++)
	{
		for (y = 0; y < SIZE; y++)
		{
			if (board[x][y] == 0)
			{
				count++;
			}
		}
	}
	return count;
}

bool gameEnded(uint8_t board[SIZE][SIZE])
{
	bool ended = true;
	if (countEmpty(board) > 0)
		return false;
	if (findPairDown(board))
		return false;
	rotateBoard(board);
	if (findPairDown(board))
		ended = false;
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	return ended;
}

// 10进制
char *Int2String(int num, char *str)
{
	int i = 0;	 //指示填充str
	if (num < 0) //如果num为负数，将num变正
	{
		num = -num;
		str[i++] = '-';
	}
	//转换
	do
	{
		str[i++] = num % 10 + 48; //取num最低位 字符0~9的ASCII码是48~57；简单来说数字0+48=48，ASCII码对应字符'0'
		num /= 10;				  //去掉最低位
	} while (num);				  // num不为0继续循环

	str[i] = '\0';

	//确定开始调整的位置
	int j = 0;
	if (str[0] == '-') //如果有负号，负号不用调整
	{
		j = 1; //从第二位开始调整
		++i;   //由于有负号，所以交换的对称轴也要后移1位
	}
	//对称交换
	for (; j < i / 2; j++)
	{
		//对称交换两端的值 其实就是省下中间变量交换a+b的值：a=a+b;b=a-b;a=a-b;
		str[j] = str[j] + str[i - 1 - j];
		str[i - 1 - j] = str[j] - str[i - 1 - j];
		str[j] = str[j] - str[i - 1 - j];
	}

	return str; //返回转换后的值
}

void initBoard(lv_obj_t *parent, uint8_t board[SIZE][SIZE])
{
	// static struct NUMBER_BOX s_number_cbuf[SIZE][SIZE];

	/* 创建画布 */
	// static lv_color_t best_source_cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(135, 75)];
	// lv_obj_t *best_source_canvas = lv_canvas_create(root);
	// // lv_obj_set_click(best_source_canvas, true);
	// lv_img_set_antialias(best_source_canvas, false); // 禁用抗锯齿
	// lv_canvas_set_buffer(best_source_canvas, best_source_cbuf, 135, 75, LV_IMG_CF_TRUE_COLOR);
	// lv_obj_align(best_source_canvas, LV_ALIGN_TOP_RIGHT, -70, 52);
	// // lv_canvas_fill_bg(best_source_canvas, lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);

	// /* 画矩形 */
	// lv_draw_rect_dsc_t best_source_rect_dsc;
	// lv_draw_rect_dsc_init(&best_source_rect_dsc);
	// best_source_rect_dsc.bg_color = LV_100ASK_2048_GAME_BOX_COLOR;
	// lv_canvas_draw_rect(best_source_canvas, 0, 0, 135, 75, &best_source_rect_dsc);

	// /* 最高分提示 */
	// lv_obj_t *best_source_tip_text = lv_label_create(best_source_canvas); /* 创建标签 */
	// lv_label_set_text(best_source_tip_text, "BEST");
	// lv_obj_align(best_source_tip_text, LV_ALIGN_TOP_MID, 0, 0); /* 当前画布居中 */

	// /* 最高分数 */
	// game_2048_best_score = lv_label_create(best_source_canvas); /* 创建标签 */
	// lv_label_set_text(game_2048_best_score, "4096");
	// lv_obj_align(game_2048_best_score, LV_ALIGN_BOTTOM_MID, 0, 0); /* 当前画布居中 */

	// /* 创建画布 */
	// static lv_color_t current_source_cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(135, 75)];
	// lv_obj_t *current_source_canvas = lv_canvas_create(root);
	// // lv_obj_set_click(current_source_canvas, true);
	// lv_img_set_antialias(current_source_canvas, false); // 禁用抗锯齿
	// lv_canvas_set_buffer(current_source_canvas, current_source_cbuf, 135, 75, LV_IMG_CF_TRUE_COLOR);
	// lv_obj_align(current_source_canvas, LV_ALIGN_TOP_RIGHT, -70, 70 + 75);
	// // lv_canvas_fill_bg(current_source_canvas, LV_COLOR_SILVER, LV_OPA_COVER);

	// /* 画矩形 */
	// lv_draw_rect_dsc_t current_source_rect_dsc;
	// lv_draw_rect_dsc_init(&current_source_rect_dsc);
	// current_source_rect_dsc.bg_color = LV_100ASK_2048_GAME_BOX_COLOR;
	// lv_canvas_draw_rect(current_source_canvas, 0, 0, 135, 75, &current_source_rect_dsc);

	// /* 当前分提示 */
	// lv_obj_t *current_source_tip_text = lv_label_create(current_source_canvas); /* 创建标签 */
	// lv_label_set_text(current_source_tip_text, "SORCE");
	// lv_obj_align(current_source_tip_text, LV_ALIGN_TOP_MID, 0, 0); /* 当前画布居中 */

	// /* 当前分数 */
	// char str[5] = {0};
	// game_2048_current_score_text = lv_label_create(current_source_canvas); /* 创建标签 */
	// lv_label_set_text(game_2048_current_score_text, Int2String(game_2048_current_score, str));
	// lv_obj_align(game_2048_current_score_text, LV_ALIGN_BOTTOM_MID, 0, 0); /* 当前画布居中 */

	// lv_obj_t *game_title = lv_label_create(root);
	// // lv_theme_apply(game_title, (lv_theme_style_t)LV_THEME_ARC);
	// lv_label_set_long_mode(game_title, LV_LABEL_LONG_WRAP); /*Break the long lines*/
	// lv_label_set_recolor(game_title, true);					/*Enable re-coloring by commands in the text*/
	// lv_obj_align(game_title, LV_ALIGN_TOP_LEFT, 0, 80);
	// lv_label_set_text(game_title, "#776e65 2048# ");
	// lv_obj_set_width(game_title, 150);

#if 0
	lv_obj_t *game_tutorial = lv_label_create(root);
	// lv_theme_apply(game_tutorial, (lv_theme_style_t)LV_100ASK_DEMO_THEME_CHINESE_CHARACTER);
	lv_label_set_long_mode(game_tutorial, LV_LABEL_LONG_WRAP); /*Break the long lines*/
	lv_label_set_recolor(game_tutorial, true);				   /*Enable re-coloring by commands in the text*/
	// lv_label_set_align(game_tutorial, LV_ALIGN_TOP_LEFT);		 /*Center aligned lines*/
	lv_obj_align(game_tutorial, LV_ALIGN_TOP_LEFT, 22, 120);
	lv_label_set_text(game_tutorial, "\nJoin the tiles, \nget to 2048!");
	// lv_label_set_text(game_tutorial, "合并色块，得出更大的数字！");
	lv_obj_set_width(game_tutorial, 200);
#endif

	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (board[x][y] != 0)
			{
				// sprintf(tmp_char, "%d", board[x][y]);
				char tmp_char[8];
				// s_number_cbuf[x][y].number_cbuf
				snprintf(tmp_char, 8, "%u", (uint32_t)1 << board[x][y]);
				drawBoard(parent, number_cbuf, tmp_char,
						  LV_100ASK_2048_NUMBER_BOX_W, LV_100ASK_2048_NUMBER_BOX_H,
						  (16 * (y + 1)) + (LV_100ASK_2048_NUMBER_BOX_W * (y + 1 - 1)), 
						  (16 * (x + 1)) + (LV_100ASK_2048_NUMBER_BOX_W * (x + 1 - 1)), Num2Color((uint32_t)1 << board[x][y]));
			}
			else
			{
				drawBoard(parent, number_cbuf, "",
						  LV_100ASK_2048_NUMBER_BOX_W, LV_100ASK_2048_NUMBER_BOX_H,
						  (16 * (y + 1)) + (LV_100ASK_2048_NUMBER_BOX_W * (y + 1 - 1)),
						   (16 * (x + 1)) + (LV_100ASK_2048_NUMBER_BOX_W * (x + 1 - 1)), LV_100ASK_2048_NUMBER_BOX_COLOR);
			}
		}
	}
}

void drawBoard(lv_obj_t *parent, lv_color_t *cbuf, char *number,
					  uint16_t canvas_w, uint16_t canvas_h,
					  uint16_t rect_dsc_x, uint16_t rect_dsc_y,
					  lv_color_t rgb32)
{
	static lv_style_t style_icon;

	lv_style_init(&style_icon);
	lv_style_set_text_font(&style_icon, &lv_font_montserrat_24); /*Set a larger font*/

	/* 创建画布 */
	static lv_obj_t *canvas;
	
	// if(canvas==NULL)
	canvas= lv_canvas_create(parent);

	// lv_obj_set_click(canvas, true);
	lv_img_set_antialias(canvas, false); // 禁用抗锯齿
	lv_canvas_set_buffer(canvas, cbuf, canvas_w, canvas_h, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(canvas, LV_ALIGN_TOP_LEFT, rect_dsc_x, rect_dsc_y);
	// lv_canvas_fill_bg(canvas, LV_COLOR_SILVER, LV_OPA_COVER);

	/* 画矩形 */
	static lv_draw_rect_dsc_t rect_dsc;

	lv_draw_rect_dsc_init(&rect_dsc);

	rect_dsc.bg_color = rgb32;
	lv_canvas_draw_rect(canvas, 0, 0, canvas_w, canvas_h, &rect_dsc);

	/* 数字 */
	lv_obj_t *icon = lv_label_create(canvas); /* 创建标签 */
	// lv_label_set_text(systime_task_label, "Welcome to www.100ask.net!");
	lv_label_set_text(icon, number);
	lv_obj_align(icon, LV_ALIGN_CENTER, 0, 0); /* 当前画布居中 */

	lv_obj_add_style(icon, &style_icon, 0);
	lv_obj_add_event_cb(canvas, play_2048_event_cb, LV_EVENT_CLICKED, NULL);
}

void game_2048_key_cb(lv_dir_t dir)
{
	bool success = false;

	switch (dir)
	{
	case LV_DIR_TOP:
		success = moveLeft(game_2048_board);
		break;
	case LV_DIR_BOTTOM:
		success = moveRight(game_2048_board);
		break;
	case LV_DIR_RIGHT:
		success = moveDown(game_2048_board);
		break;
	case LV_DIR_LEFT:
		success = moveUp(game_2048_board);
		break;
	default:
		success = false;
	}
	if (success)
	{
		initBoard(game_2048_canvas, game_2048_board);
		addRandom(game_2048_board);
		initBoard(game_2048_canvas, game_2048_board);
		if (gameEnded(game_2048_board))
		{
			play_game = false;
		}
	}
}

void play_2048_event_cb(lv_obj_t *obj, lv_event_t e)
{
	game_2048_key_cb(lv_indev_get_gesture_dir(lv_indev_get_act()));
}
#include "Arduino.h"

void lv_100ask_demo_2048(lv_obj_t *root)
{
	static lv_style_t style_bg;

	root = root;
	// play_2048_indev = lv_indev_get_act();

	lv_style_init(&style_bg);
	lv_style_set_bg_color(&style_bg, LV_100ASK_2048_GAME_BG_COLOR);
	lv_style_set_bg_opa(&style_bg, LV_OPA_50);

	lv_obj_add_style(root, &style_bg, 0);

	/* 创建画布 */
	// cbuf = heap_caps_malloc(
	// 	LV_CANVAS_BUF_SIZE_TRUE_COLOR(LV_100ASK_2048_GAME_BOX_W, LV_100ASK_2048_GAME_BOX_H),
	// 	MALLOC_CAP_SPIRAM
	// 	);

	// printf("spiram: %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM)/1024);
	// cbuf = lv_mem_alloc( 	LV_CANVAS_BUF_SIZE_TRUE_COLOR(LV_100ASK_2048_GAME_BOX_W, LV_100ASK_2048_GAME_BOX_H));
cbuf = lv_mem_alloc(
		LV_CANVAS_BUF_SIZE_INDEXED_1BIT(LV_100ASK_2048_GAME_BOX_W, LV_100ASK_2048_GAME_BOX_H));

	// static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(LV_100ASK_2048_GAME_BOX_W, LV_100ASK_2048_GAME_BOX_H)];
	game_2048_canvas = lv_canvas_create(root);
	// lv_obj_set_click(game_2048_canvas, true);
	lv_img_set_antialias(game_2048_canvas, false); // 禁用抗锯齿
	lv_canvas_set_buffer(game_2048_canvas, cbuf, LV_100ASK_2048_GAME_BOX_W, LV_100ASK_2048_GAME_BOX_H, LV_IMG_CF_INDEXED_1BIT);
	// lv_canvas_set_buffer(game_2048_canvas, cbuf, LV_100ASK_2048_GAME_BOX_W, LV_100ASK_2048_GAME_BOX_H, LV_IMG_CF_TRUE_COLOR);
	lv_obj_align(game_2048_canvas, LV_ALIGN_CENTER, 0, 0);
	lv_canvas_fill_bg(game_2048_canvas, lv_color_white(), LV_OPA_COVER);
	// lv_canvas_fill_bg(game_2048_canvas, LV_100ASK_2048_GAME_BOX_COLOR, LV_OPA_COVER);
	lv_obj_add_event_cb(game_2048_canvas, play_2048_event_cb, LV_EVENT_CLICKED, NULL);
	lv_obj_add_event_cb(root, play_2048_event_cb, LV_EVENT_CLICKED, NULL);

	initBoardNumber(game_2048_board);
	initBoard(game_2048_canvas, game_2048_board);
}

void lv_100ask_demo_2048_deinit()
{
	if (cbuf != NULL)
	{
		lv_mem_free(cbuf);
	}
}
// #endif /* LV_USE_100ASK_DEMO_GAME_2048 */
