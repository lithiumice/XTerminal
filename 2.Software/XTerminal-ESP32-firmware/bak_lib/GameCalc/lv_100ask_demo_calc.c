/**
 ******************************************************************************
 * @file    lv_100ask_demo_calc.c
 * @author  百问科技
 * @version V1.1
 * @date    2021-10-17
 * @brief	计算器
 ******************************************************************************
 * Change Logs:
 * Date           Author          Notes
 * 2020-12-12     zhouyuebiao     First version
 * 2021-10-17     zhouyuebiao     V1.1
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

// #if LV_USE_100ASK_DEMO_EFF_CALC

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lv_100ask_demo_calc.h"

/*********************
 *      DEFINES
 *********************/
// Calculation expression
#define LV_100ASK_CALC_EXPR_LEN                            (128) // 允许表达式的最大长度
#define LV_100ASK_CALC_MAX_NUM_LEN                         (5)   // 允许运算数的最大长度

// padding
#define LV_100ASK_CALC_HISTORY_MAX_LINE     (128)
#define LV_100ASK_CALC_HISTORY_MAX_H        ((LV_VER_RES/4) * 1)
#define LV_100ASK_PANEL_CALC_MAX_H          ((LV_VER_RES/4) * 3)
#define LV_100ASK_COLOR_BLACK               lv_color_hex(0x000000)
#define LV_100ASK_COLOR_GREEN               lv_color_hex(0xf5fffa)

/**********************
 *      TYPEDEFS
 **********************/
// 标记符
typedef enum {
    TOKENIZER_ERROR,        // Error
    TOKENIZER_ENDOFINPUT,   // End of input
    TOKENIZER_NUMBER,       // number
    TOKENIZER_PLUS,         // +
    TOKENIZER_MINUS,        // -
    TOKENIZER_ASTR,         // *
    TOKENIZER_SLASH,        // /
    TOKENIZER_LPAREN,       // (
    TOKENIZER_RPAREN,       // )
} token_t;

//  错误代码
typedef enum {
    no_error = 0,           // no error
    syntax_error,           // syntax error
} error_t;

// 错误代码与对应的消息
typedef struct {
    error_t error_code;
    char *message;
} error_table_t;


/**********************
 *  STATIC VARIABLES
 **********************/
//static lv_obj_t * bg_calc;      	            // 背景
static lv_obj_t * g_calc_ta;    	            // 文本编辑框
static char *curr_char = NULL;     	        // 表达式中当前分析到的字符
static char *next_char = NULL;     	        // 表达式中下一个字符


static token_t current_token = TOKENIZER_ERROR;	// 默认当前token
static error_t error_code = no_error;			// 默认错误值


// 按键布局
static const char * btnm_map[] = {  "(", ")",  "C", "<-",  "\n",
									  "7", "8", "9", "/", "\n",
									  "4", "5", "6", "*",  "\n",
									  "1", "2", "3", "-",  "\n",
									  "0", ".", "=", "+",  ""};

// 错误表
static const error_table_t error_table[] = {
    {.error_code = no_error,            .message = "no error"},
    {.error_code = syntax_error,        .message = "syntax error!"}
};


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_100ask_calc_init(void);					// 界面初始化
static void lv_100ask_calc_tokenizer_init(char *expr); 	// 词法分析器初始化
static token_t lv_100ask_calc_siglechar(void);			// 获取单字符token类型
static token_t lv_100ask_calc_get_next_token(void);	    // 获取一个token
static token_t lv_100ask_calc_tokenizer_token(void);	// 得到当前token
static void lv_100ask_calc_accept(token_t token);		// 匹配token
static void lv_100ask_calc_tokenizer_next(void);		// 解析下一个token
static bool lv_100ask_calc_tokenizer_finished(void);    // token解析完成
static void lv_100ask_calc_error(error_t err);			// 错误处理
static int lv_100ask_calc_tokenizer_num(void);			// 将ASCII形式的数字转为数值
static int lv_100ask_calc_factor(void);					// 取得当前因子的值, 若当前因子(类似上式中的M)是一个表达式, 进行递归求值
static int lv_100ask_calc_term(void);					// 求第二级优先级(乘除)表达式的值
static int lv_100ask_calc_expr(void);					// 求第一级优先级(加减)表达式的值
static void event_handler_btnmatrix(lv_event_t * e);			    // 按钮矩阵事件


/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*
 *  函数名：   void lv_100ask_demo_calc(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用初始化入口
*/
void lv_100ask_demo_calc(void)
{
    //bg_calc = lv_obj_create(lv_scr_act());
	//lv_obj_set_size(bg_calc, LV_HOR_RES, LV_VER_RES);
	//lv_obj_set_y(bg_calc, 0);
	//lv_obj_set_style_radius(bg_calc, 0, 0);    // 设置圆角
	//lv_obj_set_style_bg_color(bg_calc, LV_100ASK_COLOR_GREEN, 0);   // 设置背景颜色

    lv_100ask_calc_init();
}



/**********************
 *   STATIC FUNCTIONS
 **********************/

/*
 *  函数名：   static void lv_100ask_calc_init(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用界面初始化
*/
static void lv_100ask_calc_init(void)
{
    /* 计算历史及计算结果 */
    g_calc_ta = lv_textarea_create(lv_scr_act());
    lv_obj_set_style_text_font(g_calc_ta, &lv_font_montserrat_22, 0);  // text font
    lv_obj_set_style_bg_color(g_calc_ta, LV_100ASK_COLOR_BLACK, 0);   // 设置背景颜色
    lv_obj_set_style_text_color(g_calc_ta, LV_100ASK_COLOR_GREEN, 0);   // 设置背景颜色
    lv_obj_set_style_radius(g_calc_ta, 0, 0);    // 设置圆角
    lv_textarea_set_max_length(g_calc_ta, LV_100ASK_CALC_HISTORY_MAX_LINE);             // 设置文本区域的最大长度
    lv_obj_set_size(g_calc_ta, LV_HOR_RES, LV_100ASK_CALC_HISTORY_MAX_H);               // 设置宽高
    //lv_textarea_set_text_align(g_calc_ta, LV_LABEL_ALIGN_RIGHT);                        // 设置文本方向
    lv_textarea_set_text(g_calc_ta, "");
    lv_textarea_set_placeholder_text(g_calc_ta, "CALC HISTORY");
    //lv_textarea_set_cursor_hidden(g_calc_ta, true);
    lv_obj_align(g_calc_ta, LV_ALIGN_TOP_MID, 0, 0);  // 摆放位置

    /* 计算器输入面板 */
    lv_obj_t * btnm = lv_btnmatrix_create(lv_scr_act());
    lv_obj_set_style_text_font(btnm, &lv_font_montserrat_26, 0);  // text font
    lv_obj_set_width(btnm, LV_HOR_RES);
    lv_obj_set_height(btnm, LV_100ASK_PANEL_CALC_MAX_H);
    lv_obj_set_style_radius(btnm, 0, 0);    // 设置圆角
    lv_btnmatrix_set_map(btnm, btnm_map);
	//lv_obj_set_style_bg_color(btnm, lv_color_hex(0xf9f9f9), 0);   // 设置背景颜色
    lv_obj_align(btnm, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_add_event_cb(btnm, event_handler_btnmatrix, LV_EVENT_VALUE_CHANGED, NULL);
}



/*
 *  函数名：   static void event_handler_btnmatrix(lv_obj_t * obj, lv_event_t event)
 *  输入参数： 触发事件的对象
 *  输入参数： 触发的事件类型
 *  返回值：   无
 *  函数作用： 按钮矩阵事件处理
*/
static void event_handler_btnmatrix(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_VALUE_CHANGED)
    {
        static char calc_exp[LV_100ASK_CALC_EXPR_LEN];   // 表达式
        static  int count = 0;  // 记录表达式位置

        lv_obj_t * obj = lv_event_get_target(e);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        const char * txt = lv_btnmatrix_get_btn_text(obj, id);

        if (strcmp(txt, "=") == 0)                   // 执行运算
        {
            char tmp_buff[32];
            int calc_results;

            lv_100ask_calc_tokenizer_init(calc_exp);  // 词法分析器

            calc_results = lv_100ask_calc_expr();  // 求第一级优先级(加减)表达式的值

            if (error_code != no_error)
            {
                // 查找错误代码并打印对应消息
                for (int i = 0; i < sizeof(error_table); i++)
                {
                    if (error_table[i].error_code == error_code)
                    {
                        lv_textarea_add_text(g_calc_ta, "\n");
                        lv_textarea_add_text(g_calc_ta, error_table[i].message);
                        lv_textarea_add_text(g_calc_ta, "\n");
                        //printf("\n%s\n", error_table[i].message);
                    }
                }
                error_code = no_error;
            }
            else
            {
                sprintf(tmp_buff, "=\n%d\n", calc_results);
                lv_textarea_add_text(g_calc_ta, tmp_buff);
                memset(calc_exp, '\0',sizeof(calc_exp));   // 清空表达式
            }

        }
        else if (strcmp(txt, "C") == 0)              // 清空
        {
            lv_textarea_set_text(g_calc_ta, "");
            memset(calc_exp, '\0',sizeof(calc_exp));   // 清空表达式
            count = 0;
        }

        else if (strcmp(txt, "<-") == 0)             // 删除
        {
            lv_textarea_del_char(g_calc_ta);
            calc_exp[count-1] = '\0';
            count--;
        }

        else                                        // 追加内容
        {
            lv_textarea_add_text(g_calc_ta, txt);
            strcat(&calc_exp[0], txt);
            count++;
        }
    }
}


/*
 *  函数名：   static token_t lv_100ask_calc_siglechar(void)
 *  输入参数： 无
 *  返回值：   token类型
 *  函数作用： 获取单字符token类型
*/
static token_t lv_100ask_calc_siglechar(void)
{
    switch (*curr_char)
    {
    case '+':
        return TOKENIZER_PLUS;
    case '-':
        return TOKENIZER_MINUS;
    case '*':
        return TOKENIZER_ASTR;
    case '/':
        return TOKENIZER_SLASH;
    case '(':
        return TOKENIZER_LPAREN;
    case ')':
        return TOKENIZER_RPAREN;
    default:
        break;
    }

    return TOKENIZER_ERROR;
}


/*
 *  函数名：   static token_t lv_100ask_calc_get_next_token(void)
 *  输入参数： 无
 *  返回值：   token类型
 *  函数作用： 获取一个token
*/
static token_t lv_100ask_calc_get_next_token(void)
{
    int i;

    // 表达式结束
    if (curr_char == '\0')
        return TOKENIZER_ENDOFINPUT;

    if (isdigit(*curr_char))
    {
        // 不可超过允许数字长度
        for (i = 0; i <= LV_100ASK_CALC_MAX_NUM_LEN; i++)
        {
            // 数字结束
            if (!isdigit(*(curr_char + i)))
            {
                next_char = curr_char + i;
                return TOKENIZER_NUMBER;
            }
        }
    }
    // 分界符
    else if (lv_100ask_calc_siglechar())
    {
        next_char++;
        return lv_100ask_calc_siglechar();
    }

    return TOKENIZER_ERROR;
}



/*
 *  函数名：   static token_t lv_100ask_calc_tokenizer_finished(void)
 *  输入参数： 无
 *  返回值：   true - 无需要解析的token， false - 有需要解析的token
 *  函数作用： 判断是否token是否到达结尾
*/
static bool lv_100ask_calc_tokenizer_finished(void)
{
    return *curr_char == '\0' || current_token == TOKENIZER_ENDOFINPUT;
}


/*
 *  函数名：   static void lv_100ask_calc_error(error_t err)
 *  输入参数： 错误类型
 *  返回值：   无
 *  函数作用： 错误处理
*/
static void lv_100ask_calc_error(error_t err)
{
    error_code = err;

    return;
}


/*
 *  函数名：   static token_t lv_100ask_calc_tokenizer_next(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 解析下一个token
*/
static void lv_100ask_calc_tokenizer_next(void)
{
    if (lv_100ask_calc_tokenizer_finished())
        return;

    curr_char = next_char;
    current_token = lv_100ask_calc_get_next_token();

    return;
}


/*
 *  函数名：   static token_t lv_100ask_calc_tokenizer_token(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 得到当前token
*/
static token_t lv_100ask_calc_tokenizer_token(void)
{
    return current_token;
}


/*
 *  函数名：   static token_t lv_100ask_calc_tokenizer_num(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 将ASCII形式的数字转为数值
*/
static int lv_100ask_calc_tokenizer_num(void)
{
    return atoi(curr_char);
}


/*
 *  函数名：   static void lv_100ask_calc_accept(token_t token)
 *  输入参数： 需要匹配的token
 *  返回值：   无
 *  函数作用： 匹配token
*/
static void lv_100ask_calc_accept(token_t token)
{
    if (token != lv_100ask_calc_tokenizer_token())
        lv_100ask_calc_error(syntax_error);

    lv_100ask_calc_tokenizer_next();
}



/*
 *  函数名：   static int lv_100ask_calc_factor(void)
 *  输入参数： 无
 *  返回值：   因子的值
 *  函数作用： 取得当前因子的值, 若当前因子(类似上式中的M)是一个表达式, 进行递归求值
*/
static int lv_100ask_calc_factor(void)
{
    int r;

    // 当前token的类型
    switch (lv_100ask_calc_tokenizer_token())
    {
    // 数字(终结符)
    case TOKENIZER_NUMBER:
        // 将其由ASCII转为数字值
        r = lv_100ask_calc_tokenizer_num();
        // 根据语法规则匹配当前token
        lv_100ask_calc_accept(TOKENIZER_NUMBER);
        break;
    // 左括号
    case TOKENIZER_LPAREN:
        lv_100ask_calc_accept(TOKENIZER_LPAREN);
        // 将括号里的值当作一个新的表达式, 递归计算(递归是从函数expr()开始的)
        r = lv_100ask_calc_expr();
        // 当括号里的表达式处理完毕后下一个token一定是右括号
        lv_100ask_calc_accept(TOKENIZER_RPAREN);
        break;
        // 除左括号和数字之外的其它token已经被上一级处理掉了
        // 若有其token, 一定是表达式语法错误
    default:
        lv_100ask_calc_error(syntax_error);
    }

    // 返回因子的值
    return r;
}


/*
 *  函数名：   static int lv_100ask_calc_term(void)
 *  输入参数： 无
 *  返回值：   计算结果
 *  函数作用： 求第二级优先级(乘除)表达式的值
*/
static int lv_100ask_calc_term(void)
{
    int f1, f2;
    token_t op;

    // 获取左操作数(因子)
    f1 = lv_100ask_calc_factor();
    // 获取操作符
    op = lv_100ask_calc_tokenizer_token();

    // 操作符只能是乘或者除(同一优先级)
    while (op == TOKENIZER_ASTR || op == TOKENIZER_SLASH)
    {
        // 下一个token
        lv_100ask_calc_tokenizer_next();
        // 获取右操作数(因子)
        f2 = lv_100ask_calc_factor();
        switch ((int)op)
        {
        case TOKENIZER_ASTR:
            f1 = f1 * f2;
            break;
        case TOKENIZER_SLASH:
            f1 = f1 / f2;
            break;
        }
        // 上面计算完毕的这个值将做为左操作数
        op = lv_100ask_calc_tokenizer_token();
    }

    return f1;
}


/*
 *  函数名：   static int lv_100ask_calc_expr(void)
 *  输入参数： 无
 *  返回值：   计算结果
 *  函数作用： 求第一级优先级(加减)表达式的值
*/
static int lv_100ask_calc_expr(void)
{
    int t1, t2 = 0;
    token_t op;

    // 第一个操作数
    t1 = lv_100ask_calc_term();
    // 获取运算符
    op = lv_100ask_calc_tokenizer_token();

    // 操作符只能是加或者减(同一优先级)
    while (op == TOKENIZER_PLUS || op == TOKENIZER_MINUS)
    {
        // 下一个token
        lv_100ask_calc_tokenizer_next();
        // 第二个操作数
        t2 = lv_100ask_calc_term();
        switch ((int)op)
        {
        case TOKENIZER_PLUS:
            t1 = t1 + t2;
            break;
        case TOKENIZER_MINUS:
            t1 = t1 - t2;
            break;
        }
        op = lv_100ask_calc_tokenizer_token();
    }

    return t1;
}


/*
 *  函数名：   static int lv_100ask_calc_expr(void)
 *  输入参数： 输入的表达式字符串
 *  返回值：   无
 *  函数作用： 词法分析器初始化
*/
static void lv_100ask_calc_tokenizer_init(char *expr)
{
    curr_char = next_char = expr;
    current_token = lv_100ask_calc_get_next_token();

    return;
}



// #endif /* LV_USE_100ASK_DEMO_EFF_CALC */
