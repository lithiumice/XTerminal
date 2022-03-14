#include "Game2048.h"
#include <ctime>
#include "HAL/HAL.h"
#include <stdio.h>
#include <stdlib.h>
#include "lv_100ask_game_2048.h"

lv_dir_t Get_Btn();

#define GAME_EN 0
using namespace Page;

/***********Page*************/
Game2048::Game2048()
{
}

Game2048::~Game2048()
{
}

void Game2048::onCustomAttrConfig()
{
	SetCustomCacheEnable(true);
	SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_bounce);
}

void Game2048::onViewLoad()
{
	lv_obj_remove_style_all(root);
	lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
	StatusBar::SetStyle(StatusBar::STYLE_BLACK);

	ui.group = lv_group_create();
}

void Game2048::onViewDidLoad()
{
	lv_indev_set_cursor(lv_get_indev(LV_INDEV_TYPE_ENCODER), canvas);
}

void Game2048::onViewWillAppear()
{
#if GAME_EN
	lv_100ask_demo_2048(root);
#endif

	lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), ui.group);
	StatusBar::SetStyle(StatusBar::STYLE_TRANSP);

	lv_obj_set_style_bg_color(root, lv_color_white(), LV_PART_MAIN);

	timer = lv_timer_create(onTimerUpdate, 30, this);
	lv_timer_ready(timer);

	lv_obj_fade_in(root, 300, 0);
}

void Game2048::onViewDidAppear()
{
	// lv_group_focus_obj(View.ui.canvas);
}

void Game2048::onViewWillDisappear()
{
	lv_obj_fade_out(root, 300, 0);

#if GAME_EN
	lv_100ask_demo_2048_deinit();
#endif
}

void Game2048::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void Game2048::onViewDidUnload()
{
}

void Game2048::AttachEvent(lv_obj_t *obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}
void Game2048::Update()
{
#if GAME_EN
	lv_dir_t dir = Get_Btn();
	if (dir != LV_DIR_NONE)
		game_2048_key_cb(dir);
#endif

	if (gflag.enc_long_push_flag == 1)
	{
		gflag.enc_long_push_flag = 0;
		Manager->Pop();
	}
}

void Game2048::onTimerUpdate(lv_timer_t *timer)
{
	Game2048 *instance = (Game2048 *)timer->user_data;
	instance->Update();
}

void Game2048::onEvent(lv_event_t *event)
{
	lv_obj_t *obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	auto *instance = (Game2048 *)lv_obj_get_user_data(obj);
}
