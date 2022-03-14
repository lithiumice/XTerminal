
/**
 ******************************************************************************
 * @file    lv_100ask_demo_snake.c
 * @author  百问科技
 * @version V1.0
 * @date    2021-10-16
 * @brief	贪吃蛇游戏
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
 * @file lv_100ask_demo_snake.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
// #include "../../lv_100ask_demo.h"

// #if LV_USE_100ASK_DEMO_GAME_SNAKE

#include <stdio.h>
#include <stdlib.h>
#include "lv_100ask_demo_snake.h"

/*********************
 *      DEFINES
 *********************/
#define LV_100ASK_GAME_SNAKE_TITLE_SPACE   (50)
#define LV_100ASK_GAME_SNAKE_INIT_LINE     (3)
#define LV_100ASK_GAME_SNAKE_MAX_LINE      (256)
#define LV_100ASK_GAME_SNAKE_SIZE          (15)
//#define LV_100ASK_GAME_SNAKE_EYE_SIZE    (5)
#define LV_100ASK_GAME_SNAKE_SPEED         (15)
#define LV_100ASK_GAME_SNAKE_SPACE         (LV_100ASK_GAME_SNAKE_SIZE - LV_100ASK_GAME_SNAKE_SPEED)
#define LV_100ASK_GAME_SNAKE_HEAD_COLOR    (lv_color_hex(0xffff00))  	// 蛇头颜色
#define LV_100ASK_GAME_SNAKE_BODY_COLOR    (lv_color_hex(0x000000))  		// 蛇身颜色
#define LV_100ASK_GAME_SNAKE_RADIUS        (15)   					// 蛇身体圆角设置radius
#define LV_100ASK_GAME_FOOD_RADIUS         (50)   					// 食物圆角设置
#define LV_100ASK_GAME_FOOD_COLOR          (lv_color_hex(0x871f78)) 	    // 食物颜色
#define LV_100ASK_GAME_FOOD_SIZE           (LV_100ASK_GAME_SNAKE_SIZE)
#define LV_100ASK_GAME_FOOD_CHECK_SPACE    (10)
#define LV_100ASK_GAME_FOOD_MAX_HOR        (LV_HOR_RES - LV_100ASK_GAME_SNAKE_SIZE)
#define LV_100ASK_GAME_FOOD_MAX_VER        (LV_VER_RES - LV_100ASK_GAME_SNAKE_TITLE_SPACE)
#define LV_100ASK_GAME_SNAKE_USE_KEY       (0)  					// 使用按键控制

/**********************
 *      TYPEDEFS
 **********************/
// 游戏数据
typedef struct _lv_100ask_snake {
	lv_obj_t  * bg;				// 背景
	lv_obj_t  * obj_food;		// 食物句柄
	lv_obj_t  * label_info;		// 游戏信息
	lv_timer_t * task_handle; 	// 任务句柄
	uint8_t	sroce;				// 得分
	uint8_t len;				// 长度
	uint8_t gesture;			// 蛇头方向标志
} T_lv_100ask_snake, *PT_lv_100ask_snake;

// 蛇身数据
typedef struct Link{
	lv_obj_t *obj;            	// 蛇身
	lv_coord_t x;             	// x坐标
	lv_coord_t y;             	// y坐标
	struct Link *prior;       	// 指向直接前趋
	struct Link *next;        	// 指向直接后继针
}link_snake, p_link_snake;


/**********************
 *  STATIC VARIABLES
 **********************/
static PT_lv_100ask_snake g_pt_lv_100ask_snake;  	// 数据结构体
static link_snake *spriteSnake;              		// 链表头(蛇头)

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_100ask_stm32_game_snake_init(void);							// 初始化界面
static link_snake *lv_100ask_stm32_game_snake_initLink(void);				// 初始化链表
static void lv_100ask_stm32_game_snake_clear_list(link_snake* ppHeadNode);	// 清空链表，释放结点内存，将链表重置为空表
static void lv_100ask_stm32_game_snake_linkAddNode(void);					// 在链表尾部插入新节点(增长小蛇身体)
static void lv_task_100ask_game_snake(lv_timer_t * task);					// 游戏任务
static void lv_100ask_stm32_game_snake_update_snake_data(void); 			// 更新小蛇数据结构
static void event_handler_snake_gesture_cb(lv_event_t *e);	// 触摸屏检测处理事件(触摸屏控制游戏)

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*
 *  函数名：   void lv_100ask_demo_snake(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用初始化入口
*/
void lv_100ask_demo_snake(void)
{
	g_pt_lv_100ask_snake = (T_lv_100ask_snake *)malloc(sizeof(T_lv_100ask_snake));   // 申请内存
	g_pt_lv_100ask_snake->gesture = 0;

	g_pt_lv_100ask_snake->bg = lv_obj_create(lv_scr_act());
	lv_obj_set_style_radius(g_pt_lv_100ask_snake->bg, 0 ,0);
	lv_obj_set_size(g_pt_lv_100ask_snake->bg, LV_HOR_RES, LV_VER_RES);
	lv_obj_set_y(g_pt_lv_100ask_snake->bg, 0);

    lv_100ask_stm32_game_snake_init();

    /* 创建任务检测按键输入与游戏动画 */
	g_pt_lv_100ask_snake->task_handle = lv_timer_create(lv_task_100ask_game_snake, 500, NULL); // 150

    lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(lv_layer_top(), event_handler_snake_gesture_cb, LV_EVENT_CLICKED, NULL);   	// 分配事件处理
}



/**********************
 *   STATIC FUNCTIONS
 **********************/

/*
 *  函数名：   static void lv_100ask_stm32_game_snake_init(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用界面初始化
*/
static void lv_100ask_stm32_game_snake_init(void)
{
    spriteSnake = lv_100ask_stm32_game_snake_initLink();

    link_snake* head = NULL;
    head = spriteSnake;         //将temp指针重新指向头结点
    int i = 0;
    lv_coord_t init_x = (rand()%(LV_HOR_RES));
    lv_coord_t init_y = (rand()%(LV_VER_RES));
    while (head->next)
    {
        head = head->next;
        head->obj = lv_obj_create(g_pt_lv_100ask_snake->bg);
        if (i == 0)
        {
            lv_obj_set_style_bg_color(head->obj, LV_100ASK_GAME_SNAKE_HEAD_COLOR, 0); //设置颜色
        }
        else
            lv_obj_set_style_bg_color(head->obj, LV_100ASK_GAME_SNAKE_BODY_COLOR, 0); //设置颜色
        lv_obj_set_style_radius(head->obj, LV_100ASK_GAME_SNAKE_RADIUS, 0);  		 // 设置圆角
        lv_obj_set_size(head->obj, LV_100ASK_GAME_SNAKE_SIZE, LV_100ASK_GAME_SNAKE_SIZE);
        lv_obj_set_pos(head->obj, init_x+(i * LV_100ASK_GAME_SNAKE_SIZE), init_y);
        head->x = lv_obj_get_x(head->obj);
        head->y = lv_obj_get_y(head->obj);
        i++;
    }

    // 初始化食物
    g_pt_lv_100ask_snake->obj_food = lv_obj_create(g_pt_lv_100ask_snake->bg);
    lv_obj_set_size(g_pt_lv_100ask_snake->obj_food, LV_100ASK_GAME_FOOD_SIZE, LV_100ASK_GAME_FOOD_SIZE);
    lv_obj_set_style_bg_color(g_pt_lv_100ask_snake->obj_food, LV_100ASK_GAME_FOOD_COLOR, 0); //设置颜色
    lv_obj_set_style_radius(g_pt_lv_100ask_snake->obj_food, LV_100ASK_GAME_FOOD_RADIUS, 0);	// 设置圆角
    lv_obj_set_pos(g_pt_lv_100ask_snake->obj_food, (rand()%(LV_100ASK_GAME_FOOD_MAX_HOR)), (rand()%(LV_100ASK_GAME_FOOD_MAX_VER)));

	g_pt_lv_100ask_snake->sroce = 3;
    g_pt_lv_100ask_snake->len = 3;
    g_pt_lv_100ask_snake->label_info = lv_label_create(g_pt_lv_100ask_snake->bg);
	lv_obj_set_style_text_font(g_pt_lv_100ask_snake->label_info, &lv_font_montserrat_14, 0);  		// 设置字体格式
	lv_label_set_text_fmt(g_pt_lv_100ask_snake->label_info, "LEN: %d\nSROCE: %d", g_pt_lv_100ask_snake->len, g_pt_lv_100ask_snake->sroce);  // 展示游戏信息
	lv_obj_align(g_pt_lv_100ask_snake->label_info, LV_ALIGN_TOP_LEFT, 0, LV_100ASK_GAME_SNAKE_TITLE_SPACE);

}

//
/*
 *  函数名：   static link_snake* lv_100ask_stm32_game_snake_initLink(void)
 *  输入参数： 无
 *  返回值：   初始化后的链表
 *  函数作用： 初始化链表(蛇)
*/
static link_snake* lv_100ask_stm32_game_snake_initLink(void)
{
    link_snake* head = (link_snake*)malloc(sizeof(link_snake));		// 创建链表第一个结点（首元结点）
    head->prior = NULL;
    head->next = NULL;
    head->obj = NULL;
    head->x = 0;
    head->y = 0;
    link_snake * list = head;   //声明一个指针指向头结点，方便后期向链表中添加新创建的节点

    // 生成链表(初始化蛇身)
    for (int i = 0; i < LV_100ASK_GAME_SNAKE_INIT_LINE; i++) {
        link_snake *body = (link_snake*)malloc(sizeof(link_snake));
        body->prior = NULL;
        body->next = NULL;
        body->obj = NULL;
        body->x = i;
        body->y = i;

        //新节点与链表最后一个节点建立关系
        list->next = body;
        body->prior = list;
        //list永远指向链表中最后一个节点
        list = list->next;
    }
    return head;
}



/*
 *  函数名：   static void lv_100ask_stm32_game_snake_linkAddNode(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 在链表尾部插入新节点(增长蛇身)
*/
static void lv_100ask_stm32_game_snake_linkAddNode(void)
{
    link_snake *temp_list;

    // 初始化新节点
    link_snake *list_new = (link_snake*)malloc(sizeof(link_snake));
    list_new->prior = NULL;
    list_new->next = NULL;
    list_new->x = 0;
    list_new->y = 0;
    list_new->obj = lv_obj_create(g_pt_lv_100ask_snake->bg);
    lv_obj_set_style_bg_color(list_new->obj, LV_100ASK_GAME_SNAKE_BODY_COLOR, 0); //设置颜色
    lv_obj_set_style_radius(list_new->obj, LV_100ASK_GAME_SNAKE_RADIUS, 0);  // 设置圆角
    lv_obj_set_size(list_new->obj, LV_100ASK_GAME_SNAKE_SIZE, LV_100ASK_GAME_SNAKE_SIZE);

    // 检查头节点
    if(spriteSnake == NULL)
    {
        spriteSnake = list_new;
    }
    else
    {
        temp_list = spriteSnake;
        while(temp_list->next)  // 定位到链表尾部
        {
            temp_list = temp_list->next;
        }
        temp_list->next = list_new;
        list_new->prior = temp_list;
    }
}


/*
 *  函数名：   static void lv_100ask_stm32_game_snake_clear_list(link_snake* ppHeadNode)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 清空链表，释放结点内存，将链表重置为空表
*/
static void lv_100ask_stm32_game_snake_clear_list(link_snake* ppHeadNode)
{
    link_snake* pListNodeTmp = NULL;
    if((ppHeadNode) == NULL)
    {
        printf("The list is empty, no need to clear.\n");
        return;
    }

    //bool is_head = true;
    // 循环释放链表中的结点所占内存，
    while((ppHeadNode)->next != NULL)
    {
        pListNodeTmp = (ppHeadNode)->next;
		if (ppHeadNode->obj != NULL)	lv_obj_clean(ppHeadNode->obj);  // 删除蛇身节点
        free((ppHeadNode));
        (ppHeadNode) = pListNodeTmp;
    }

    // 清除最后一个结点
    if((ppHeadNode) != NULL)
    {
		if (ppHeadNode->obj != NULL)	lv_obj_clean(ppHeadNode->obj);  // 删除蛇身节点
        free((ppHeadNode));
        (ppHeadNode) = NULL;
    }

    printf("The list is cleared.\n");
}


/*
 *  函数名：   static void lv_task_100ask_game_snake(lv_timer_t * task)
 *  输入参数： 任务描述符
 *  返回值：   无
 *  函数作用： 物理按键检测控制游戏、不断地移动小蛇
*/
static void lv_task_100ask_game_snake(lv_timer_t * task)
{
#if LV_100ASK_GAME_SNAKE_USE_KEY
	uint8_t *key = (uint8_t*)&key_value.up_value;
	if(key[0] == 1)
	{
		printf("UP\n\r");
		g_pt_lv_100ask_snake->gesture |= 1;
		key[0] = 0;
	}
	else if(key[1] == 1)
	{
		printf("DOWN\n\r");
		g_pt_lv_100ask_snake->gesture |= 2;
		key[1] = 0;
	}
	else if(key[2] == 1)
	{
		printf("LEFT\n\r");
		g_pt_lv_100ask_snake->gesture |= 8;
		key[2] = 0;
	}
	else if(key[3] == 1)
	{
		printf("RIGHT\n\r");
		g_pt_lv_100ask_snake->gesture |= 4;
		key[3] = 0;
	}
#endif // LV_100ASK_GAME_SNAKE_USE_KEY

    lv_coord_t x = spriteSnake->next->x - lv_obj_get_x(g_pt_lv_100ask_snake->obj_food);   // 获取 x 轴的差异
    lv_coord_t y = spriteSnake->next->y - lv_obj_get_y(g_pt_lv_100ask_snake->obj_food);   // 获取 y 轴的差异
    if(((x >= -LV_100ASK_GAME_FOOD_CHECK_SPACE)&&(x <= LV_100ASK_GAME_FOOD_CHECK_SPACE)) && ((y >= -LV_100ASK_GAME_FOOD_CHECK_SPACE)&&(y <= LV_100ASK_GAME_FOOD_CHECK_SPACE)))
    {
        lv_100ask_stm32_game_snake_linkAddNode();
        g_pt_lv_100ask_snake->len += 1;
        g_pt_lv_100ask_snake->sroce += 1;

        lv_obj_set_pos(g_pt_lv_100ask_snake->obj_food, rand()%(LV_100ASK_GAME_FOOD_MAX_HOR), rand()%(LV_100ASK_GAME_FOOD_MAX_VER));
		lv_label_set_text_fmt(g_pt_lv_100ask_snake->label_info, "LEN: %u\nSROCE: %u", g_pt_lv_100ask_snake->len, g_pt_lv_100ask_snake->sroce);  // 展示游戏信息
    }
    lv_100ask_stm32_game_snake_update_snake_data();
}



/*
 *  函数名：   static void event_handler_snake_gesture_cb(lv_event_t *e)
 *  输入参数： 触发地事件类型
 *  返回值：   无
 *  函数作用： 触摸屏检测事件处理，控制小蛇移动
*/
static void event_handler_snake_gesture_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

	//if ((code == LV_EVENT_GESTURE) || (code == LV_EVENT_CLICKED))
	//{
		switch(lv_indev_get_gesture_dir(lv_indev_get_act()))
		{
			case LV_DIR_TOP:
			    g_pt_lv_100ask_snake->gesture |= 1;
                break;
			case LV_DIR_BOTTOM:
				g_pt_lv_100ask_snake->gesture |= 2;
				break;
			case LV_DIR_RIGHT:
				g_pt_lv_100ask_snake->gesture |= 4;
				break;
			case LV_DIR_LEFT:
				g_pt_lv_100ask_snake->gesture |= 8;
				break;
			default: break;
		}
		lv_100ask_stm32_game_snake_update_snake_data();
	//}
	//else if (code == LV_EVENT_LONG_PRESSED)   // 当长按时加速前进
    //{
    //    lv_100ask_stm32_game_snake_update_snake_data();
    //}
}

/*
 *  函数名：   static void lv_100ask_stm32_game_snake_update_snake_data(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 更新小蛇数据结构
*/
static void lv_100ask_stm32_game_snake_update_snake_data(void)
{
    static lv_coord_t x = LV_100ASK_GAME_SNAKE_SPEED, y = 0;  // 默认往右边走
    volatile lv_coord_t obj_size_x = LV_100ASK_GAME_SNAKE_SPACE, obj_size_y = 0;  // 间距补偿
    if (((g_pt_lv_100ask_snake->gesture) & 1) == 1)         // 上
    {
        y = -LV_100ASK_GAME_SNAKE_SPEED;
        x = 0;
        obj_size_y = -LV_100ASK_GAME_SNAKE_SPACE;
        obj_size_x = 0;
    }
    else if (((g_pt_lv_100ask_snake->gesture) & 2) == 2)   // 下
    {
        y = LV_100ASK_GAME_SNAKE_SPEED;
        x = 0;
        obj_size_y = LV_100ASK_GAME_SNAKE_SPACE;
        obj_size_x = 0;
    }
    else if (((g_pt_lv_100ask_snake->gesture) & 4) == 4)   // 左
    {
        y = 0;
        x = LV_100ASK_GAME_SNAKE_SPEED;
        obj_size_y = 0;
        obj_size_x = LV_100ASK_GAME_SNAKE_SPACE;
    }
    else if (((g_pt_lv_100ask_snake->gesture) & 8) == 8)   // 右
    {
        y = 0;
        x = -LV_100ASK_GAME_SNAKE_SPEED;
        obj_size_y = 0;
        obj_size_x = -LV_100ASK_GAME_SNAKE_SPACE;
    }
    g_pt_lv_100ask_snake->gesture = 0;  // 清空标志位

    link_snake* temp_list = NULL;
    temp_list = spriteSnake;    // 将 temp_list 指针重新指向头结点
    while (temp_list->next)     // 定位到链表尾部
    {
        temp_list = temp_list->next;
    }
    while (temp_list->prior->prior)  // 首节点不加入
    {
        // 从后往前迭代更新坐标数据
        temp_list->x = temp_list->prior->x;
        temp_list->y = temp_list->prior->y;
        lv_obj_set_pos(temp_list->obj, temp_list->x, temp_list->y);
        temp_list = temp_list->prior;
    }
    // 处理首节点
    temp_list->x = lv_obj_get_x(temp_list->obj) + x;
    temp_list->y = lv_obj_get_y(temp_list->obj) + y;
    lv_obj_set_pos(temp_list->obj, temp_list->x, temp_list->y);
}

/**********************
 * GLOBAL PROTOTYPES
 **********************/



// #endif /* LV_USE_100ASK_DEMO_GAME_SNAKE */
