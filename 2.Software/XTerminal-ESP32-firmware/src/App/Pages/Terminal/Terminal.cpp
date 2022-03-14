#include "Terminal.h"
#include "stdio.h"
#include "HAL/HAL.h"
using namespace Page;

Terminal::Terminal()
{
}

Terminal::~Terminal()
{

}

void Terminal::onCustomAttrConfig()
{
	// SetCustomCacheEnable(true);
	// SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_bounce);
}

void Terminal::onViewLoad()
{
	View.Create(root);
	// AttachEvent(root);
	AttachEvent(View.ui.termTextLabel);
}

void Terminal::onViewDidLoad()
{

}

void Terminal::onViewWillAppear()
{
	lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), View.ui.group);
	StatusBar::SetStyle(StatusBar::STYLE_TRANSP);
	
	lv_obj_set_style_bg_color(root, lv_color_white(), LV_PART_MAIN);

	timer = lv_timer_create(onTimerUpdate, 300, this);
	lv_timer_ready(timer);

	lv_obj_fade_in(root, 300, 0);
}

void Terminal::onViewDidAppear()
{
	lv_group_focus_obj(View.ui.termTextLabel);
}

void Terminal::onViewWillDisappear()
{
	lv_obj_fade_out(root, 300, 0);
}

void Terminal::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void Terminal::onViewDidUnload()
{
	// View.Delete();
	// Model.DeInit();
}

void Terminal::AttachEvent(lv_obj_t* obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Terminal::Update()
{
	if(HAL::term_text_update_flag)
	{
		View.SetTermText(HAL::globalTermText);

	}
}

void Terminal::onTimerUpdate(lv_timer_t* timer)
{
	Terminal* instance = (Terminal*)timer->user_data;
	instance->Update();
}

void Terminal::onEvent(lv_event_t* event)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	auto* instance = (Terminal*)lv_obj_get_user_data(obj);

	if (code == LV_EVENT_RELEASED)
	{
        HAL::TerminalPrintln("Terminal LV_EVENT_PRESSED");
		instance->Manager->Pop();
	}
	else if (code == LV_EVENT_LONG_PRESSED)
	{
		HAL::TerminalPrintln("Terminal LV_EVENT_LONG_PRESSED");
		instance->Manager->Pop();
	}

}
