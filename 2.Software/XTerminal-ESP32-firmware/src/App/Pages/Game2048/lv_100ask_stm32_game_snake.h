// #ifndef LV_100ASK_STM32_GAME_SANKE_H
// #define LV_100ASK_STM32_GAME_SANKE_H
//
// #ifdef __cplusplus
// extern "C" {
// #endif
//
//
// /*********************
//  *      INCLUDES
//  *********************/
// #include "lvgl/lvgl.h"
//
//
//
// /*********************
//  *      DEFINES
//  *********************/
// #define LV_100ASK_GAME_SNAKE_TITLE_SPACE   (50)
// #define LV_100ASK_GAME_SNAKE_INIT_LINE     (3)
// #define LV_100ASK_GAME_SNAKE_MAX_LINE      (256)
// #define LV_100ASK_GAME_SNAKE_SIZE          (15)
// //#define LV_100ASK_GAME_SNAKE_EYE_SIZE    (5)
// #define LV_100ASK_GAME_SNAKE_SPEED         (15)
// #define LV_100ASK_GAME_SNAKE_SPACE         (LV_100ASK_GAME_SNAKE_SIZE - LV_100ASK_GAME_SNAKE_SPEED)
// #define LV_100ASK_GAME_SNAKE_HEAD_COLOR    (LV_COLOR_YELLOW)  		// 蛇头颜色
// #define LV_100ASK_GAME_SNAKE_BODY_COLOR    (LV_COLOR_BLACK)  		// 蛇身颜色
// #define LV_100ASK_GAME_SNAKE_RADIUS        (15)   					// 蛇身体圆角设置radius
// #define LV_100ASK_GAME_FOOD_RADIUS         (50)   					// 食物圆角设置
// #define LV_100ASK_GAME_FOOD_COLOR          (LV_COLOR_PURPLE) 	    // 食物颜色
// #define LV_100ASK_GAME_FOOD_SIZE           (LV_100ASK_GAME_SNAKE_SIZE)
// #define LV_100ASK_GAME_FOOD_CHECK_SPACE    (10)
// #define LV_100ASK_GAME_FOOD_MAX_HOR        (LV_HOR_RES - LV_100ASK_GAME_SNAKE_SIZE)
// #define LV_100ASK_GAME_FOOD_MAX_VER        (LV_VER_RES - LV_100ASK_GAME_SNAKE_TITLE_SPACE)
// #define LV_100ASK_GAME_SNAKE_USE_KEY       (1)  					// 使用按键控制
//
//
// /**********************
//  *      TYPEDEFS
//  **********************/
// // 游戏数据
// typedef struct _lv_100ask_snake {
// 	lv_obj_t  * bg;				// 背景
// 	lv_obj_t  * obj_food;		// 食物句柄
// 	lv_obj_t  * label_info;		// 游戏信息
// 	lv_task_t * task_handle; 	// 任务句柄
// 	uint8_t	sroce;				// 得分
// 	uint8_t len;				// 长度
// 	uint8_t gesture;			// 蛇头方向标志
// } T_lv_100ask_snake, *PT_lv_100ask_snake;
//
// // 蛇身数据
// typedef struct Link{
// 	lv_obj_t *obj;            	// 蛇身
// 	lv_coord_t x;             	// x坐标
// 	lv_coord_t y;             	// y坐标
// 	struct Link *prior;       	// 指向直接前趋
// 	struct Link *next;        	// 指向直接后继针
// }link_snake, p_link_snake;
//
// /**********************
//  * GLOBAL PROTOTYPES
//  **********************/
// void lv_100ask_stm32_game_snake(void);
//
//
//
//
//
// /**********************
//  *      MACROS
//  **********************/
//
// #ifdef __cplusplus
// } /* extern "C" */
// #endif
//
// #endif /* LV_100ASK_STM32_GAME_SANKE_H */
//
//
//
//
//
