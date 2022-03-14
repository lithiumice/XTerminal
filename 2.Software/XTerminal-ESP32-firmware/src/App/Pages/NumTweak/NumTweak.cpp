#include "NumTweak.h"

#include <ctime>
#include "Arduino.h"
#include "HAL/HAL.h"
#include <stdio.h>
#include <stdlib.h>
using namespace Page;
uint8_t num_tweak_type = 0;
NumTweakConfig NumTweak_config;

NumTweak::NumTweak()
{
}

NumTweak::~NumTweak()
{
}

void NumTweak::onCustomAttrConfig()
{
	SetCustomCacheEnable(true);
	SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_bounce);
}

// static void set_angle(void * obj, int32_t v)
// {
//     lv_arc_set_value((lv_obj_t*)obj, v);
// }

// static void ArcBright_AnimCallback(lv_obj_t * obj, int16_t angle)
// {
//     lv_arc_set_angles(obj, angle ,180);
// }

void NumTweak::ArcValueCtrl(int step)
{
	NumTweak_config.current += step;
	__LimitValue(NumTweak_config.current, NumTweak_config.min, NumTweak_config.max);
	// int target_val = map(NumTweak_config.current,
	// 					 NumTweak_config.min,
	// 					 NumTweak_config.max,
	// 					 1, 99);
	int target_val = NumTweak_config.current;

	lv_label_set_text_fmt(ui.indicateText, "%d", target_val);
	lv_arc_set_value(ui.arc, target_val);
	// static lv_anim_t a;
	// lv_obj_add_anim(
	//     ui.arc, &a,
	//     (lv_anim_exec_xcb_t)ArcBright_AnimCallback,
	//     NumTweak_config.current,
	//     target_val,
	//     500
	// );

	if(num_tweak_type==BLACKLIGHT)
	{
		HAL::Backlight_SetValue(target_val);
	}
}

void NumTweak::GUICreate()
{

	ui.arc = lv_arc_create(root);
	lv_obj_set_size(ui.arc, 150, 150);
	// lv_arc_set_rotation(ui.arc, 135);
	// lv_arc_set_bg_angles(ui.arc, 0, 270);
	lv_arc_set_rotation(ui.arc, 270);
	lv_arc_set_bg_angles(ui.arc, 0, 360);
	lv_arc_set_value(ui.arc, NumTweak_config.current);
	lv_arc_set_range(ui.arc, NumTweak_config.min, NumTweak_config.max);
	lv_obj_remove_style(ui.arc, NULL, LV_PART_KNOB);
	lv_obj_set_style_shadow_opa(ui.arc, LV_OPA_COVER, LV_PART_INDICATOR);
	lv_obj_set_style_shadow_color(ui.arc, lv_palette_main(LV_PALETTE_BLUE), LV_PART_INDICATOR);
	lv_obj_set_style_shadow_width(ui.arc, 10, LV_PART_INDICATOR);
	lv_obj_set_style_radius(ui.arc, 0, 0);
	lv_obj_set_style_radius(ui.arc, 0, LV_PART_INDICATOR);
	lv_obj_set_style_arc_width(ui.arc, 8, LV_PART_MAIN);
	lv_obj_set_style_arc_width(ui.arc, 8, LV_PART_INDICATOR);
	lv_obj_set_style_arc_color(ui.arc, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN);
	lv_obj_set_style_arc_color(ui.arc, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR);
	// lv_arc_set_mode(ui.arc, LV_ARC_MODE_SYMMETRICAL);
	lv_obj_center(ui.arc);
	// lv_anim_t a;
	// lv_anim_init(&a);
	// lv_anim_set_var(&a, ui.arc);
	// lv_anim_set_exec_cb(&a, set_angle);
	// lv_anim_set_time(&a, 1000);
	// lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
	// lv_anim_set_repeat_delay(&a, 500);
	// lv_anim_set_values(&a, 0, 100);
	// lv_anim_start(&a);

	ui.indicateText = lv_label_create(root);
	lv_label_set_recolor(ui.indicateText, true);
	lv_obj_set_style_text_font(ui.indicateText, &lv_font_montserrat_42, 0);
	// lv_obj_set_style_text_font(ui.indicateText, Resource.GetFont("EuroStar_60"), 0);
	lv_obj_set_style_text_color(ui.indicateText, lv_color_white(), 0);
	// lv_obj_set_style_text_color(ui.indicateText, lv_palette_main(LV_PALETTE_BLUE), 0);
	lv_obj_align(ui.indicateText, LV_ALIGN_CENTER, 0, 0);
	// lv_obj_align(ui.indicateText, LV_ALIGN_CENTER,0,-10);
	lv_label_set_text(ui.indicateText, "40");
	// ui.unitText = lv_label_create(root);
	// lv_label_set_recolor(ui.unitText, true);
	// lv_obj_set_style_text_font(ui.unitText, Resource.GetFont("Morganite_36"), 0);
	// lv_obj_set_style_text_color(ui.unitText, lv_color_white(), 0);
	// lv_obj_align(ui.unitText, LV_ALIGN_CENTER,0,10);
	// lv_label_set_text(ui.unitText, "min");

}

void NumTweak::onViewLoad()
{
	if (num_tweak_type == BLACKLIGHT)
	{
		NumTweak_config.min = 50;
		NumTweak_config.max = 950;
		NumTweak_config.step = 10;
		NumTweak_config.current = HAL::Backlight_GetValue();
	}

	lv_obj_remove_style_all(root);
	lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
	StatusBar::SetStyle(StatusBar::STYLE_BLACK);
	ui.group = lv_group_create();

	GUICreate();
	lv_group_add_obj(ui.group, ui.arc);
	ArcValueCtrl(0);
	AttachEvent(ui.arc);

	
}

void NumTweak::onViewDidLoad()
{
}

void NumTweak::onViewWillAppear()
{
	lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), ui.group);
	StatusBar::SetStyle(StatusBar::STYLE_TRANSP);

	lv_obj_set_style_bg_color(root, lv_color_white(), LV_PART_MAIN);

	timer = lv_timer_create(onTimerUpdate, 500, this);
	lv_timer_ready(timer);

	lv_obj_fade_in(root, 300, 0);
}

void NumTweak::onViewDidAppear()
{
	lv_group_focus_obj(ui.arc);
}

void NumTweak::onViewWillDisappear()
{
	lv_obj_fade_out(root, 300, 0);
}

void NumTweak::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void NumTweak::onViewDidUnload()
{
	// View.Delete();
	// Model.DeInit();
}

void NumTweak::AttachEvent(lv_obj_t *obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void NumTweak::Update()
{
}

void NumTweak::onTimerUpdate(lv_timer_t *timer)
{
	NumTweak *instance = (NumTweak *)timer->user_data;
	instance->Update();
}

void NumTweak::onEvent(lv_event_t *event)
{
	lv_obj_t *obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	auto *instance = (NumTweak *)lv_obj_get_user_data(obj);

	if (code == LV_EVENT_RELEASED)
	{
		HAL::TerminalPrintln("NumTweak LV_EVENT_PRESSED");
		instance->Manager->Pop();
	}
	else if (code == LV_EVENT_LONG_PRESSED)
	{

		HAL::TerminalPrintln("NumTweak LV_EVENT_LONG_PRESSED");
		instance->Manager->Pop();
	}
	// else if (code == LV_EVENT_VALUE_CHANGED &&
	// 		 obj == instance->ui.arc)
	else if (code == LV_EVENT_KEY)
	{
		uint32_t key = (*(uint32_t *)event->param);
		if (key == LV_KEY_LEFT)
		{
			instance->ArcValueCtrl(NumTweak_config.step);
		}
		else if (key == LV_KEY_RIGHT)
		{
			instance->ArcValueCtrl(-NumTweak_config.step);
		}
		// else if (key == LV_KEY_ENTER)
		// {
		// 	KEY_V = KEY_TURN;
		// }

		// LV_LOG_USER("State: %s\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
	}
}
