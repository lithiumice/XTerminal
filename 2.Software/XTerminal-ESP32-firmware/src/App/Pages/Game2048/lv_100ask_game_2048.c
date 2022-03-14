// /**
//  ******************************************************************************
//  * @file    lv_100ask_game_2048.c
//  * @author  百问科技
//  * @version V1.2
//  * @date    2020-12-12
//  * @brief	2048游戏
//  ******************************************************************************
//  * Change Logs:
//  * Date           Author          Notes
//  * 2020-12-12     zhouyuebiao     First version
//  * 2021-01-25     zhouyuebiao     V1.2 
//  ******************************************************************************
//  * @attention
//  *
//  * Copyright (C) 2008-2021 深圳百问网科技有限公司<https://www.100ask.net/>
//  * All rights reserved
//  *
//  ******************************************************************************
//  */
//
// /*********************
//  *      INCLUDES
//  *********************/
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include "lv_100ask_game_2048.h"
//
//
// /**********************
//  *  STATIC VARIABLES
//  **********************/
// static PT_lv_100ask_2048_game g_pt_lv_100ask_2048_game;  // 数据结构体
//
//
// /**********************
//  *  STATIC PROTOTYPES
//  **********************/
// static void lv_100ask_game_2048_init(void);													// 界面初始化
// static void lv_100ask_game_2048_init_board(lv_obj_t * parent, uint8_t board[SIZE][SIZE]);  	// 初始化画板，展示主界面效果
// static void lv_100ask_game_2048_init_board_number(uint8_t board[SIZE][SIZE]);				// 初始化小方块数据
// static void lv_100ask_game_2048_draw_board(lv_obj_t * parent, char * number, \
// 							 uint16_t canvas_w, uint16_t canvas_h, \
// 							 uint16_t rect_dsc_x, uint16_t rect_dsc_y, \
// 							 lv_color_t rgb32);												// 填充绘制小方块
// static void lv_100ask_game_2048_add_random(uint8_t board[SIZE][SIZE]);						// 为二维数组初始化随机位置的随机数
// static void lv_100ask_game_2048_rotate_board(uint8_t board[SIZE][SIZE]);					// 旋转矩阵
// static bool lv_100ask_game_2048_slide_array(uint8_t array[SIZE]);							// 检查数组是否还有空间
// static bool lv_100ask_game_2048_move_up(uint8_t board[SIZE][SIZE]);							// 检查是否可以上滑动(触摸屏控制)
// static bool lv_100ask_game_2048_move_left(uint8_t board[SIZE][SIZE]);						// 检查是否可以左滑动(触摸屏控制)
// static bool lv_100ask_game_2048_move_down(uint8_t board[SIZE][SIZE]);						// 检查是否可以下滑动(触摸屏控制)
// static bool lv_100ask_game_2048_move_right(uint8_t board[SIZE][SIZE]);						// 检查是否可以右滑动(触摸屏控制)
// static bool lv_100ask_game_2048_find_pair_down(uint8_t board[SIZE][SIZE]);					// 检查是否可以右滑动
// static bool lv_100ask_game_2048_game_ended(uint8_t board[SIZE][SIZE]);						// 判断游戏是否应该结束
// static char* lv_100ask_game_2048_int_to_string(int num, char *str);							// 整型数值转为字符串
// static lv_color_t lv_100ask_game_2048_num_to_color(uint32_t num);							// 为数字设置对应的颜色
// static uint8_t lv_100ask_game_2048_find_target(uint8_t array[SIZE],uint8_t x,uint8_t stop);	// 检查是否应该停止滑动以避免双重合并
// static uint8_t lv_100ask_game_2048_count_empty(uint8_t board[SIZE][SIZE]);					// 查找当前二维数组是否有可以合并的数值(数值一样即可合并)
// 				
// // 任务				
// // static void lv_task_100ask_game_2048_key(lv_task_t * task);  								// 按键游戏任务
// static void lv_100ask_game_2048_game_key_up(void);											// 按键控制上移(按键控制)
// static void lv_100ask_game_2048_game_key_down(void);										// 按键控制下移(按键控制)
// static void lv_100ask_game_2048_game_key_left(void);										// 按键控制左移(按键控制)
// static void lv_100ask_game_2048_game_key_right(void);										// 按键控制右移(按键控制)
// 				
// // 触摸屏检测事件				
// static void event_handler_play_2048(lv_obj_t * obj, lv_event_t event); 						// 触摸屏检测事件处理函数(上、下、左、右滑动
// static void event_handler_back_to_home(lv_obj_t * obj, lv_event_t event);					// 返回桌面事件处理函数
//
//
//
//
// /*
//  *  函数名：   void lv_100ask_stm32_tool_widget_test(void)
//  *  输入参数： 无
//  *  返回值：   无
//  *  函数作用： 应用入口
// */
// void lv_100ask_game_2048(void)
// {
// 	/* 申请内存 */
// 	g_pt_lv_100ask_2048_game = (T_lv_100ask_2048_game *)malloc(sizeof(T_lv_100ask_2048_game));
// 	
// 	/* 初始化桌面背景 */
// 	g_pt_lv_100ask_2048_game->bg = lv_obj_create(lv_scr_act());
// 	lv_obj_set_size(g_pt_lv_100ask_2048_game->bg, LV_HOR_RES, LV_VER_RES);
// 	lv_obj_set_y(g_pt_lv_100ask_2048_game->bg, 0);
//
// 	/* 初始化游戏舞台 */
// 	g_pt_lv_100ask_2048_game->canvas_stage = lv_obj_create(g_pt_lv_100ask_2048_game->bg);
//     lv_obj_set_style_radius(g_pt_lv_100ask_2048_game->canvas_stage, 0, 0); // 设置圆角
//     lv_obj_set_style_bg_color(g_pt_lv_100ask_2048_game->canvas_stage, LV_100ASK_2048_GAME_BOX_COLOR,0); //设置颜色
// 	lv_obj_set_size(g_pt_lv_100ask_2048_game->canvas_stage, LV_100ASK_2048_GAME_BOX_W, LV_100ASK_2048_GAME_BOX_H);
// 	lv_obj_align(g_pt_lv_100ask_2048_game->canvas_stage, LV_ALIGN_TOP_MID, 0, LV_100ASK_2048_NUMBER_BOX_H);
// 	
// 	/* 初始化主界面 */
// 	g_pt_lv_100ask_2048_game->play_game = true;
// 	g_pt_lv_100ask_2048_game->current_score_value = 0;
// 	lv_100ask_game_2048_init();
// 	
// 	/* 创建任务检测按键输入 */
// 	// g_pt_lv_100ask_2048_game->task_handle = lv_task_create(lv_task_100ask_game_2048_key, 100, _LV_TASK_PRIO_NUM, NULL);
// 	
// 	/* 分配屏幕触摸事件处理 */
// 	// lv_obj_set_click(lv_layer_top(), true);
// 	// lv_obj_set_event_cb(lv_layer_top(), event_handler_play_2048);  
// 	//
// 	// /* 创建app标题 */
// 	// add_title(g_pt_lv_100ask_2048_game->bg, "2048 GAME");
// 	//
// 	// /* 创建返回桌面按钮 */
// 	// add_back(lv_layer_top(), event_handler_back_to_home);
// }
//
//
// /*
//  *  函数名：   static void lv_100ask_stm32_tool_music_player_init(void)
//  *  输入参数： 无
//  *  返回值：   无
//  *  函数作用： 应用界面初始化
// */
// static void lv_100ask_game_2048_init(void)
// {
// 	// /* 游戏说明 */
// 	// lv_obj_t * game_title = lv_label_create(g_pt_lv_100ask_2048_game->bg);
// 	// lv_obj_set_style_text_font(game_title,&lv_font_montserrat_32,0);             // 设置文字大小
// 	// lv_label_set_recolor(game_title, true); 					 /*Enable re-coloring by commands in the text*/
// 	// lv_label_set_align(game_title, LV_ALIGN_IN_LEFT_MID);		 /*Center aligned lines*/
// 	// lv_obj_align(game_title, g_pt_lv_100ask_2048_game->canvas_stage, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
// 	// lv_label_set_text(game_title, "#776e65 2048# ");
//  //
// 	// lv_obj_t * game_tutorial = lv_label_create(g_pt_lv_100ask_2048_game->bg, NULL);
// 	// lv_label_set_align(game_tutorial, LV_ALIGN_OUT_TOP_LEFT);		 /*Center aligned lines*/
// 	// lv_obj_align(game_tutorial, game_title, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
// 	// lv_label_set_text(game_tutorial, "Join the tiles, \nget to 2048!\n");
// 	// //lv_label_set_text(game_tutorial, "合并色块，得出更大的数字！");
// 	// lv_obj_set_width(game_tutorial, 200);
//  //
// 	// /* LOGO */
//  //    LV_IMG_DECLARE(img_lv_100ask_demo_logo);
//  //    lv_obj_t * logo = lv_img_create(g_pt_lv_100ask_2048_game->bg, NULL);
//  //    lv_img_set_src(logo, &img_lv_100ask_demo_logo);
// 	// lv_obj_align(logo, game_tutorial,  LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);  //(lv_obj_get_width(logo)/4)
//
// 	// /* 公司信息 */
//  //    lv_obj_t * label_logo = lv_label_create(g_pt_lv_100ask_2048_game->bg, NULL);
// 	// lv_obj_set_style_local_text_font(label_logo, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_10);             // 设置文字大小
//  //    lv_label_set_text(label_logo,  "www.100ask.net\nwww.lvgl.100ask.net");
//  //    lv_obj_align(label_logo, logo, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
//
// 	/* 最高记录显示区域 */
// 	lv_obj_t * obj_best_source = lv_obj_create(g_pt_lv_100ask_2048_game->bg, NULL);
// 	lv_obj_set_size(obj_best_source, 65, 35);
// 	lv_obj_align(obj_best_source, g_pt_lv_100ask_2048_game->canvas_stage, LV_ALIGN_OUT_BOTTOM_RIGHT,0, 0);
//
// 	/* 最高记录标题 */
// 	lv_obj_t * best_source_tip_text  = lv_label_create(obj_best_source, NULL); /* 创建标签 */
// 	lv_label_set_text(best_source_tip_text, "BEST");
// 	lv_obj_align(best_source_tip_text, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);  /* 居中 */
//
// 	/* 最高记录分数 */
// 	g_pt_lv_100ask_2048_game->label_best_score = lv_label_create(obj_best_source, NULL); /* 创建标签 */
// 	lv_label_set_text(g_pt_lv_100ask_2048_game->label_best_score, "4096");
// 	lv_obj_align(g_pt_lv_100ask_2048_game->label_best_score, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);  /* 居中 */
//
// 	/* 当前分数显示区域 */
// 	lv_obj_t * obj_current_source = lv_obj_create(g_pt_lv_100ask_2048_game->bg, NULL);
// 	lv_obj_set_size(obj_current_source, 65, 35);
// 	lv_obj_align(obj_current_source, obj_best_source, LV_ALIGN_OUT_BOTTOM_MID, 0, (lv_obj_get_height(obj_best_source)/2));
//
// 	/* 当前分提示 */
// 	lv_obj_t *  current_source_tip_text  = lv_label_create(obj_current_source, NULL); /* 创建标签 */
// 	lv_label_set_text(current_source_tip_text, "SORCE");
// 	lv_obj_align(current_source_tip_text, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);           /* 居中 */
//
// 	/* 当前分数 */
// 	g_pt_lv_100ask_2048_game->label_current_score = lv_label_create(obj_current_source, NULL);         /* 创建标签 */
// 	lv_label_set_text(g_pt_lv_100ask_2048_game->label_current_score, "0");
// 	lv_obj_align(g_pt_lv_100ask_2048_game->label_current_score, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);   /* 当前画布居中 */
// 	
// 	/* 初始化游戏数字 */
// 	lv_100ask_game_2048_init_board_number(g_pt_lv_100ask_2048_game->game_board);
//
// 	/* 初始化游戏舞台中的每个方格块 */
// 	lv_100ask_game_2048_init_board(g_pt_lv_100ask_2048_game->canvas_stage, g_pt_lv_100ask_2048_game->game_board);
// }
//
//
//
// /*
//  *  函数名：   static void lv_100ask_game_2048_init_board(lv_obj_t * parent, uint8_t board[SIZE][SIZE])
//  *  输入参数： 父对象
//  *  返回值：   需要操作的数组
//  *  函数作用： 初始化画板，展示主界面效果
// */
// static void lv_100ask_game_2048_init_board(lv_obj_t * parent, uint8_t board[SIZE][SIZE])
// {
// 	/* 清除之前所有的子对象 */
//     lv_obj_clean(parent);  
//
// 	/* 当前分数 */
// 	char str_current_score[8] = {0};
// 	lv_label_set_text(g_pt_lv_100ask_2048_game->label_current_score, lv_100ask_game_2048_int_to_string(g_pt_lv_100ask_2048_game->current_score_value, str_current_score));
// 	
// 	for(int y = 0; y < SIZE; y++)
// 	{
// 		for(int x = 0; x < SIZE; x++)
// 		{
// 			if (board[x][y]!=0) {
// 				//sprintf(tmp_char, "%d", board[x][y]);
// 				char tmp_char[8];
// 				snprintf(tmp_char, 8, "%u", (uint32_t)1<<board[x][y]);
// 				lv_100ask_game_2048_draw_board(parent, tmp_char,\
// 						  LV_100ASK_2048_NUMBER_BOX_W, LV_100ASK_2048_NUMBER_BOX_H, \
// 						  (8*(y+1))+(LV_100ASK_2048_NUMBER_BOX_W*(y+1-1)), (8*(x+1))+(LV_100ASK_2048_NUMBER_BOX_W*(x+1-1)), lv_100ask_game_2048_num_to_color((uint32_t)1<<board[x][y]));
// 			}
// 			else {
// 				lv_100ask_game_2048_draw_board(parent, "",\
// 						  LV_100ASK_2048_NUMBER_BOX_W, LV_100ASK_2048_NUMBER_BOX_H, \
// 						  (8*(y+1))+(LV_100ASK_2048_NUMBER_BOX_W*(y+1-1)), (8*(x+1))+(LV_100ASK_2048_NUMBER_BOX_W*(x+1-1)), LV_100ASK_2048_NUMBER_BOX_COLOR);
// 			}
// 		}
// 	}
// }
//
//
// /*
//  *  函数名：   static void lv_100ask_game_2048_draw_board(lv_obj_t * parent, char * number, \
// 														 uint16_t canvas_w, uint16_t canvas_h, \
// 														 uint16_t rect_dsc_x, uint16_t rect_dsc_y, \
// 														 lv_color_t rgb32)
//  *  输入参数： 绘制所依托的父对象
//  *  输入参数： 展示的数值
//  *  输入参数： 宽度
//  *  输入参数： 高度
//  *  输入参数： x轴上的偏移值
//  *  输入参数： y轴上的偏移值
//  *  输入参数： 方块背景颜色
//  *  返回值：   无
//  *  函数作用： 填充绘制小方块
// */
// static void lv_100ask_game_2048_draw_board(lv_obj_t * parent, char * number, \
// 							 uint16_t canvas_w, uint16_t canvas_h, \
// 							 uint16_t rect_dsc_x, uint16_t rect_dsc_y, \
// 							 lv_color_t rgb32)
// {
//
//     /* 创建方格块 */
//     lv_obj_t * obj = lv_obj_create(parent, NULL);
//     lv_obj_set_size(obj, canvas_w, canvas_h);
//     lv_obj_set_style_local_bg_color(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, rgb32);
//     //lv_obj_set_style_local_bg_opa(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
//     lv_obj_set_style_local_radius(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0); // 设置圆角
//     lv_obj_set_style_local_border_opa(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_0); // 边框透明度
// 	lv_obj_set_style_local_text_font(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_22); // 字体大小
// 	
// 	lv_obj_align(obj, NULL, LV_ALIGN_IN_TOP_LEFT, rect_dsc_x, rect_dsc_y);
//
// 	/* 数字 */
// 	lv_obj_t * icon  = lv_label_create(obj, NULL); /* 创建标签 */
// 	lv_label_set_text(icon, number);
// 	lv_obj_align(icon, NULL, LV_ALIGN_CENTER, 0, 0);  /* 当前画布居中 */
//
// }
//
//
//
// /*
//  *  函数名：   static char* lv_100ask_game_2048_int_to_string(int num, char *str)
//  *  输入参数： 需要转换的整型数值
//  *  返回值：   转换后的字符串
//  *  函数作用： 整型数值转为字符串
// */
// static char* lv_100ask_game_2048_int_to_string(int num, char *str)
// {
// 	int i = 0;//指示填充str
// 	if(num<0)//如果num为负数，将num变正
// 	{
// 		num = -num;
// 		str[i++] = '-';
// 	}
// 	//转换
// 	do
// 	{
// 		str[i++] = num%10+48;//取num最低位 字符0~9的ASCII码是48~57；简单来说数字0+48=48，ASCII码对应字符'0'
// 		num /= 10;//去掉最低位
// 	}while(num);//num不为0继续循环
//
// 	str[i] = '\0';
//
// 	//确定开始调整的位置
// 	int j = 0;
// 	if(str[0]=='-')//如果有负号，负号不用调整
// 	{
// 		j = 1;//从第二位开始调整
// 		++i;//由于有负号，所以交换的对称轴也要后移1位
// 	}
// 	//对称交换
// 	for(;j<i/2;j++)
// 	{
// 		//对称交换两端的值 其实就是省下中间变量交换a+b的值：a=a+b;b=a-b;a=a-b;
// 		str[j] = str[j] + str[i-1-j];
// 		str[i-1-j] = str[j] - str[i-1-j];
// 		str[j] = str[j] - str[i-1-j];
// 	}
//
// 	return str;//返回转换后的值
// }
//
//
// /*
//  *  函数名：   static void lv_100ask_game_2048_init_board_number(uint8_t board[SIZE][SIZE])
//  *  输入参数： 需要进行初始化的数组
//  *  返回值：   无
//  *  函数作用： 为二维数组初始化数值(全写0)
// */
// static void lv_100ask_game_2048_init_board_number(uint8_t board[SIZE][SIZE]) {
// 	uint8_t x,y;
// 	for (x=0;x<SIZE;x++) {
// 		for (y=0;y<SIZE;y++) {
// 			board[x][y]=0;
// 		}
// 	}
//
// 	/* 初始化两个随机位置的随机数 */
// 	lv_100ask_game_2048_add_random(board);
// 	lv_100ask_game_2048_add_random(board);
//
// 	g_pt_lv_100ask_2048_game->current_score_value = 0;
// }
//
// //__use_no_semihosting was requested, but _ttywrch was
// time(int ch)
// {
// ch = ch;
// }
//
// /*
//  *  函数名：   static void lv_100ask_game_2048_add_random(uint8_t board[SIZE][SIZE])
//  *  输入参数： 需要初始化随机位置的随机数的数组
//  *  返回值：   无
//  *  函数作用： 为二维数组初始化随机位置的随机数
// */
// static void lv_100ask_game_2048_add_random(uint8_t board[SIZE][SIZE])
// {
// 	static bool initialized = false;
// 	uint8_t x,y;
// 	uint8_t r,len=0;
// 	uint8_t n,list[SIZE*SIZE][2];
//
// 	if (!initialized) {
// 		srand(time(NULL));
// 		initialized = true;
// 	}
//
// 	for (x=0;x<SIZE;x++) {
// 		for (y=0;y<SIZE;y++) {
// 			if (board[x][y]==0) {
// 				list[len][0]=x;
// 				list[len][1]=y;
// 				len++;
// 			}
// 		}
// 	}
//
// 	if (len>0) {
// 		r = rand()%len;
// 		x = list[r][0];
// 		y = list[r][1];
// 		n = (rand()%10)/9+1;
// 		board[x][y]=n;
// 	}
// }
//
//
// /*
//  *  函数名：   static lv_color_t lv_100ask_game_2048_num_to_color(uint32_t num)
//  *  输入参数： 需要设置颜色的数值
//  *  返回值：   颜色值
//  *  函数作用： 为数字设置对应的颜色
// */
// static lv_color_t lv_100ask_game_2048_num_to_color(uint32_t num)
// {
// 	switch (num)
// 	{
// 		case 2:		return LV_100ASK_2048_NUMBER_2_COLOR;	
// 		case 4:		return LV_100ASK_2048_NUMBER_4_COLOR;	
// 		case 8:		return LV_100ASK_2048_NUMBER_8_COLOR;	
// 		case 16:	return LV_100ASK_2048_NUMBER_16_COLOR;	
// 		case 32:	return LV_100ASK_2048_NUMBER_32_COLOR;	
// 		case 64:	return LV_100ASK_2048_NUMBER_64_COLOR;	
// 		case 128:	return LV_100ASK_2048_NUMBER_128_COLOR;	
// 		case 256:	return LV_100ASK_2048_NUMBER_256_COLOR;	
// 		case 512:	return LV_100ASK_2048_NUMBER_512_COLOR;	
// 		case 1024:	return LV_100ASK_2048_NUMBER_1024_COLOR;
// 		case 2048:	return LV_100ASK_2048_NUMBER_2048_COLOR;
// 		default:	return LV_100ASK_2048_NUMBER_2048_COLOR;
// 	}
//
// }
//
//
// /*
//  *  函数名：   static uint8_t lv_100ask_game_2048_find_target(uint8_t array[SIZE],uint8_t x,uint8_t stop) 
//  *  输入参数： 需要检查的二维数组
//  *  返回值：   目标位置
//  *  函数作用： 检查是否应该停止滑动以避免双重合并
// */
// static uint8_t lv_100ask_game_2048_find_target(uint8_t array[SIZE],uint8_t x,uint8_t stop) 
// {
// 	uint8_t t;
// 	// if the position is already on the first, don't evaluate
// 	if (x == 0) {
// 		return x;
// 	}
// 	for(t = (x - 1) ;; t--) {
// 		if (array[t]!=0) {
// 			if (array[t] != array[x]) {
// 				// merge is not possible, take next position
// 				return (t + 1);
// 			}
// 			return t;
// 		} else {
// 			// we should not slide further, return this one
// 			if (t == stop) {
// 				return t;
// 			}
// 		}
// 	}
// 	// we did not find a
// 	return x;
// }
//
//
// /*
//  *  函数名：   static bool lv_100ask_game_2048_slide_array(uint8_t array[SIZE]) 
//  *  输入参数： 需要检查的数组
//  *  返回值：   true - 尚有空间； false - 无多余空间
//  *  函数作用： 检查数组是否还有空间
// */
// static bool lv_100ask_game_2048_slide_array(uint8_t array[SIZE]) 
// {
// 	bool success = false;
// 	uint8_t x, t, stop = 0;
//
// 	for (x = 0; x < SIZE; x++) {
// 		if (array[x] != 0) {
// 			t = lv_100ask_game_2048_find_target(array, x, stop);
// 			// if target is not original position, then move or merge
// 			if (t != x) {
// 				// if target is zero, this is a move
// 				if (array[t]==0) {
// 					array[t]=array[x];
// 				} else if (array[t]==array[x]) {
// 					// merge (increase power of two)
// 					array[t]++;
// 					// increase score
// 					g_pt_lv_100ask_2048_game->current_score_value+=(uint32_t)1<<array[t];
// 					// set stop to avoid double merge
// 					stop = t+1;
// 				}
// 				array[x]=0;
// 				success = true;
// 			}
// 		}
// 	}
// 	return success;
// }
//
//
//
// /*
//  *  函数名：   static bool lv_100ask_game_2048_rotate_board(uint8_t board[SIZE][SIZE]) 
//  *  输入参数： 需要旋转的矩阵
//  *  返回值：   无
//  *  函数作用： 旋转矩阵
// */
// static void lv_100ask_game_2048_rotate_board(uint8_t board[SIZE][SIZE]) 
// {
// 	uint8_t i,j,n=SIZE;
// 	uint8_t tmp;
// 	for (i=0; i<n/2; i++) {
// 		for (j=i; j<n-i-1; j++) {
// 			tmp = board[i][j];
// 			board[i][j] = board[j][n-i-1];
// 			board[j][n-i-1] = board[n-i-1][n-j-1];
// 			board[n-i-1][n-j-1] = board[n-j-1][i];
// 			board[n-j-1][i] = tmp;
// 		}
// 	}
// }
//
//
//
// /*
//  *  函数名：   static bool lv_100ask_game_2048_move_up(uint8_t board[SIZE][SIZE]) 
//  *  输入参数： 需要检查的二维数组
//  *  返回值：   true - 可以滑动； false - 不可以滑动
//  *  函数作用： 检查是否可以上滑动
// */
// static bool lv_100ask_game_2048_move_up(uint8_t board[SIZE][SIZE])
// {
// 	bool success = false;
// 	uint8_t x;
// 	for (x=0;x<SIZE;x++) {
// 		success |= lv_100ask_game_2048_slide_array(board[x]);
// 	}
// 	return success;
// }
//
//
//
// /*
//  *  函数名：   static bool lv_100ask_game_2048_move_left(uint8_t board[SIZE][SIZE]) 
//  *  输入参数： 需要检查的二维数组
//  *  返回值：   true - 可以滑动； false - 不可以滑动
//  *  函数作用： 检查是否可以上滑动
// */
// static bool lv_100ask_game_2048_move_left(uint8_t board[SIZE][SIZE])
// {
// 	bool success;
// 	lv_100ask_game_2048_rotate_board(board);
// 	success = lv_100ask_game_2048_move_up(board);
// 	lv_100ask_game_2048_rotate_board(board);
// 	lv_100ask_game_2048_rotate_board(board);
// 	lv_100ask_game_2048_rotate_board(board);
// 	return success;
// }
//
//
// /*
//  *  函数名：   static bool lv_100ask_game_2048_move_down(uint8_t board[SIZE][SIZE]) 
//  *  输入参数： 需要检查的二维数组
//  *  返回值：   true - 可以滑动； false - 不可以滑动
//  *  函数作用： 检查是否可以下滑动
// */
// static bool lv_100ask_game_2048_move_down(uint8_t board[SIZE][SIZE])
// {
// 	bool success;
// 	lv_100ask_game_2048_rotate_board(board);
// 	lv_100ask_game_2048_rotate_board(board);
// 	success = lv_100ask_game_2048_move_up(board);
// 	lv_100ask_game_2048_rotate_board(board);
// 	lv_100ask_game_2048_rotate_board(board);
// 	return success;
// }
//
//
// /*
//  *  函数名：   static bool lv_100ask_game_2048_move_right(uint8_t board[SIZE][SIZE]) 
//  *  输入参数： 需要检查的二维数组
//  *  返回值：   true - 可以滑动； false - 不可以滑动
//  *  函数作用： 检查是否可以右滑动
// */
// static bool lv_100ask_game_2048_move_right(uint8_t board[SIZE][SIZE]) 
// {
// 	bool success = false;
// 	lv_100ask_game_2048_rotate_board(board);
// 	lv_100ask_game_2048_rotate_board(board);
// 	lv_100ask_game_2048_rotate_board(board);
// 	success = lv_100ask_game_2048_move_up(board);
// 	lv_100ask_game_2048_rotate_board(board);
// 	return success;
// }
//
//
//
// /*
//  *  函数名：   static uint8_t lv_100ask_game_2048_count_empty(uint8_t board[SIZE][SIZE]) 
//  *  输入参数： 需要查找的二维数组
//  *  返回值：   true - 有可以合并的数值； false - 没有可以合并的数值
//  *  函数作用： 查找当前二维数组是否有可以合并的数值(数值一样即可合并)
// */
// static bool lv_100ask_game_2048_find_pair_down(uint8_t board[SIZE][SIZE])
// {
// 	bool success = false;
// 	uint8_t x,y;
// 	for (x=0;x<SIZE;x++) {
// 		for (y=0;y<SIZE-1;y++) {
// 			if (board[x][y]==board[x][y+1]) 
// 				return true;
// 		}
// 	}
// 	return success;
// }
//
//
//
// /*
//  *  函数名：   static uint8_t lv_100ask_game_2048_count_empty(uint8_t board[SIZE][SIZE]) 
//  *  输入参数： 需要统计的二维数组
//  *  返回值：   空闲的方格个数
//  *  函数作用： 统计空闲的方格个数
// */
// static uint8_t lv_100ask_game_2048_count_empty(uint8_t board[SIZE][SIZE]) 
// {
// 	uint8_t x,y;
// 	uint8_t count=0;
// 	for (x=0;x<SIZE;x++) {
// 		for (y=0;y<SIZE;y++) {
// 			if (board[x][y]==0) {
// 				count++;
// 			}
// 		}
// 	}
// 	return count;
// }
//
//
//
// // 游戏结束
//
// /*
//  *  函数名：   static bool lv_100ask_game_2048_game_ended(uint8_t board[SIZE][SIZE])
//  *  输入参数： 无
//  *  返回值：   true - 游戏结束， false - 可继续游戏
//  *  函数作用： 判断游戏是否应该结束
// */
// static bool lv_100ask_game_2048_game_ended(uint8_t board[SIZE][SIZE])
// {
// 	bool ended = true;
// 	if (lv_100ask_game_2048_count_empty(board)>0) return false;
// 	if (lv_100ask_game_2048_find_pair_down(board)) return false;
// 	lv_100ask_game_2048_rotate_board(board);
// 	if (lv_100ask_game_2048_find_pair_down(board)) ended = false;
// 	lv_100ask_game_2048_rotate_board(board);
// 	lv_100ask_game_2048_rotate_board(board);
// 	lv_100ask_game_2048_rotate_board(board);
// 	return ended;
// }
//
//
// /*
//  *  函数名：   static void lv_task_100ask_game_2048_key(lv_task_t * task)
//  *  输入参数： 任务描述符
//  *  返回值：   无
//  *  函数作用： 物理按键检测(上、下、左、右)
// */
// static void lv_task_100ask_game_2048_key(lv_task_t * task)
// {
// 	uint8_t *key = (uint8_t*)&key_value.up_value;
// 	if(key[0] == 1)
// 	{
// 		lv_100ask_game_2048_game_key_left();  // UP
// 		key[0] = 0;
// 	}
// 	else if(key[1] == 1)
// 	{
// 		lv_100ask_game_2048_game_key_right(); // DOWN		
// 		key[1] = 0;
// 	}
// 	else if(key[2] == 1)
// 	{
// 		lv_100ask_game_2048_game_key_up();	 //	LEFT
// 		key[2] = 0;
// 	}
// 	else if(key[3] == 1)
// 	{
// 		lv_100ask_game_2048_game_key_down();  // RIGHT
// 		key[3] = 0;
// 	}
// }
//
//
// /*
//  *  函数名：   static void event_handler_play_2048(lv_obj_t * obj, lv_event_t event)
//  *  输入参数： 触发事件的对象
//  *  输入参数： 触发的事件类型
//  *  返回值：   无
//  *  函数作用： 触摸屏检测事件处理函数(上、下、左、右滑动)
// */
// static void event_handler_play_2048(lv_obj_t * obj, lv_event_t event)
// {
// 	if (event == LV_EVENT_GESTURE)
// 	{
// 		bool success = false;
// 		printf("		 GAME BEGIN!			\n\r");
// 		switch(lv_indev_get_gesture_dir(lv_indev_get_act()))
// 		{
// 			case LV_GESTURE_DIR_TOP:
// 				//printf("LV_GESTURE_DIR_TOP.\n\r");
// 				success = lv_100ask_game_2048_move_left(g_pt_lv_100ask_2048_game->game_board); 
// 				break;
// 			case LV_GESTURE_DIR_BOTTOM:
// 				//printf("LV_GESTURE_DIR_BOTTOM.\n\r");
// 				success = lv_100ask_game_2048_move_right(g_pt_lv_100ask_2048_game->game_board); 
// 				break;
// 			case LV_GESTURE_DIR_RIGHT:
// 				//printf("LV_GESTURE_DIR_RIGHT.\n\r");
// 				success = lv_100ask_game_2048_move_down(g_pt_lv_100ask_2048_game->game_board); 
// 				break;
// 			case LV_GESTURE_DIR_LEFT:
// 				//printf("LV_GESTURE_DIR_LEFT.\n\r");
// 				success = lv_100ask_game_2048_move_up(g_pt_lv_100ask_2048_game->game_board); 
// 				break;
// 			default: success = false;
// 		}
// 		if (success)
// 		{
// 			lv_100ask_game_2048_init_board(g_pt_lv_100ask_2048_game->canvas_stage, g_pt_lv_100ask_2048_game->game_board);
// 			lv_100ask_game_2048_add_random(g_pt_lv_100ask_2048_game->game_board);
// 			lv_100ask_game_2048_init_board(g_pt_lv_100ask_2048_game->canvas_stage, g_pt_lv_100ask_2048_game->game_board);
// 			if (lv_100ask_game_2048_game_ended(g_pt_lv_100ask_2048_game->game_board))
// 			{
// 				printf("		 GAME OVER			\n");
// 				g_pt_lv_100ask_2048_game->play_game = false;
// 			}
// 		}
// 	}
// }
//
//
// /*
//  *  函数名：   static void lv_100ask_game_2048_game_key_right(void)
//  *  输入参数： 无
//  *  输入参数： 无
//  *  返回值：   无
//  *  函数作用： 按键控制上移
// */
// static void lv_100ask_game_2048_game_key_up(void)
// {
// 	if (lv_100ask_game_2048_move_up(g_pt_lv_100ask_2048_game->game_board))
// 	{
// 		lv_100ask_game_2048_init_board(g_pt_lv_100ask_2048_game->canvas_stage, g_pt_lv_100ask_2048_game->game_board);
// 		lv_100ask_game_2048_add_random(g_pt_lv_100ask_2048_game->game_board);
// 		lv_100ask_game_2048_init_board(g_pt_lv_100ask_2048_game->canvas_stage, g_pt_lv_100ask_2048_game->game_board);
// 		if (lv_100ask_game_2048_game_ended(g_pt_lv_100ask_2048_game->game_board)) {
// 			printf("         GAME OVER          \n");
// 		}
// 	}
//
// }
//
//
// /*
//  *  函数名：   static void lv_100ask_game_2048_game_key_right(void)
//  *  输入参数： 无
//  *  输入参数： 无
//  *  返回值：   无
//  *  函数作用： 按键控制下移
// */
// static void lv_100ask_game_2048_game_key_down(void)
// {
// 	if (lv_100ask_game_2048_move_down(g_pt_lv_100ask_2048_game->game_board))
// 	{
// 		lv_100ask_game_2048_init_board(g_pt_lv_100ask_2048_game->canvas_stage, g_pt_lv_100ask_2048_game->game_board);
// 		lv_100ask_game_2048_add_random(g_pt_lv_100ask_2048_game->game_board);
// 		lv_100ask_game_2048_init_board(g_pt_lv_100ask_2048_game->canvas_stage, g_pt_lv_100ask_2048_game->game_board);
// 		if (lv_100ask_game_2048_game_ended(g_pt_lv_100ask_2048_game->game_board)) {
// 			printf("         GAME OVER          \n");
// 		}
// 	}
// }
//
//
// /*
//  *  函数名：   static void lv_100ask_game_2048_game_key_right(void)
//  *  输入参数： 无
//  *  输入参数： 无
//  *  返回值：   无
//  *  函数作用： 按键控制左移
// */
// static void lv_100ask_game_2048_game_key_left(void)
// {
// 	if (lv_100ask_game_2048_move_left(g_pt_lv_100ask_2048_game->game_board))
// 	{
// 		lv_100ask_game_2048_init_board(g_pt_lv_100ask_2048_game->canvas_stage, g_pt_lv_100ask_2048_game->game_board);
// 		lv_100ask_game_2048_add_random(g_pt_lv_100ask_2048_game->game_board);
// 		lv_100ask_game_2048_init_board(g_pt_lv_100ask_2048_game->canvas_stage, g_pt_lv_100ask_2048_game->game_board);
// 		if (lv_100ask_game_2048_game_ended(g_pt_lv_100ask_2048_game->game_board)) {
// 			printf("         GAME OVER          \n");
// 		}
// 	}
// }
//
//
// /*
//  *  函数名：   static void lv_100ask_game_2048_game_key_right(void)
//  *  输入参数： 无
//  *  输入参数： 无
//  *  返回值：   无
//  *  函数作用： 按键控制右移
// */
// static void lv_100ask_game_2048_game_key_right(void)
// {
// 	if (lv_100ask_game_2048_move_right(g_pt_lv_100ask_2048_game->game_board))
// 	{
// 		lv_100ask_game_2048_init_board(g_pt_lv_100ask_2048_game->canvas_stage, g_pt_lv_100ask_2048_game->game_board);
// 		lv_100ask_game_2048_add_random(g_pt_lv_100ask_2048_game->game_board);
// 		lv_100ask_game_2048_init_board(g_pt_lv_100ask_2048_game->canvas_stage, g_pt_lv_100ask_2048_game->game_board);
// 		if (lv_100ask_game_2048_game_ended(g_pt_lv_100ask_2048_game->game_board)) {
// 			printf("         GAME OVER          \n");
// 		}
// 	}
// }
//
//
// /*
//  *  函数名：   static void event_handler_back_to_home(lv_obj_t * obj, lv_event_t event)
//  *  输入参数： 触发事件的对象
//  *  输入参数： 触发的事件类型
//  *  返回值：   无
//  *  函数作用： 返回桌面事件处理函数
// */
// static void event_handler_back_to_home(lv_obj_t * obj, lv_event_t event)
// {
//     if(event == LV_EVENT_CLICKED)
//     {
// 		if (g_pt_lv_100ask_2048_game->task_handle != NULL)			lv_task_del(g_pt_lv_100ask_2048_game->task_handle);  		/* 删除任务 */
// 		if (g_pt_lv_100ask_2048_game->canvas_stage != NULL)			lv_obj_del(g_pt_lv_100ask_2048_game->canvas_stage);			/* 删除游戏舞台 */
// 		if (g_pt_lv_100ask_2048_game->label_best_score != NULL)		lv_obj_del(g_pt_lv_100ask_2048_game->label_best_score);		/* 删除最高分数对象 */
// 		if (g_pt_lv_100ask_2048_game->label_current_score != NULL)	lv_obj_del(g_pt_lv_100ask_2048_game->label_current_score);	/* 删除当前分数对象 */
// 		if (g_pt_lv_100ask_2048_game->bg != NULL)					lv_obj_del(g_pt_lv_100ask_2048_game->bg);					/* 删除背景 */
// 		
// 		/* 释放内存 */
// 		free(g_pt_lv_100ask_2048_game);
// 		
// 		/* 清除lv_layer_top */
// 		lv_obj_set_click(lv_layer_top(), false);
// 		lv_obj_clean(lv_layer_top());
// 		lv_obj_set_event_cb(lv_layer_top(), NULL);   /* 分配事件处理 */
// 		
// 		/* 清空屏幕并返回桌面 */
//         lv_100ask_stm32_anim_out_all(lv_scr_act(), 0);
//         lv_100ask_stm32_demo_home(0);
//     }
// }
//
//
//
//
