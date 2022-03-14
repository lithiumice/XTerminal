#include "GameList.h"
#include "App/App.h"
#include "App/Configs/Version.h"
#include "HAL/HAL.h"
using namespace Page;

GameList::GameList()
{
}

GameList::~GameList()
{
}

void GameList::onCustomAttrConfig()
{
}

void GameList::onViewLoad()
{
	View.Create(root);
	AttachEvent(root);

#define REG_GAME(index, name) \
	AttachEvent(View.ui.name.icon);

#include "../GameArduboy/_GameList.inc"

#undef REG_GAME
    lv_group_focus_obj(View.ui.GameArduboy3D.icon);
}

void GameList::onViewDidLoad()
{
}

void GameList::onViewWillAppear()
{
	lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), View.ui.group);
	StatusBar::SetStyle(StatusBar::STYLE_TRANSP);

	timer = lv_timer_create(onTimerUpdate, 100, this);
	lv_timer_ready(timer);

	View.SetScrollToY(root, -LV_VER_RES, LV_ANIM_OFF);
	lv_obj_fade_in(root, 300, 0);
}

void GameList::onViewDidAppear()
{
	View.onFocus(View.ui.group);
}

void GameList::onViewWillDisappear()
{
	lv_obj_fade_out(root, 300, 0);
}

void GameList::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void GameList::onViewDidUnload()
{
	View.Delete();
}

void GameList::AttachEvent(lv_obj_t *obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void GameList::Update()
{
}

void GameList::onTimerUpdate(lv_timer_t *timer)
{
	GameList *instance = (GameList *)timer->user_data;

	instance->Update();
}

void GameList::onEvent(lv_event_t *event)
{
	lv_obj_t *obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	auto *instance = (GameList *)lv_obj_get_user_data(obj);
	if (code == LV_EVENT_RELEASED)
	{
#define REG_GAME(index, name)                   \
	if (obj == instance->View.ui.name.icon)     \
	{                                           \
		HAL::game_select_index = index;         \
		instance->Manager->Push("Pages/GameArduboy"); \
	}

#include "../GameArduboy/_GameList.inc"

#undef REG_GAME
	}
	else if (code == LV_EVENT_LONG_PRESSED)
	{
		instance->Manager->Pop();
	}
}
