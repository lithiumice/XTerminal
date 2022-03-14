#include "WifiText.h"
#include "HAL/HAL.h"
using namespace Page;

WifiText::WifiText()
{
}

WifiText::~WifiText()
{
}

void WifiText::onCustomAttrConfig()
{
	SetCustomCacheEnable(true);
	SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_bounce);
}

void WifiText::onViewLoad()
{
	// View.Create(root);
	lv_obj_remove_style_all(root);
	lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
	StatusBar::SetStyle(StatusBar::STYLE_BLACK);
	ui.group = lv_group_create();

	/*Create the password box*/
	ui.pwd_textarea = lv_textarea_create(root);
	lv_textarea_set_text(ui.pwd_textarea, "");
#ifdef ARDUINO
	lv_textarea_set_text(ui.pwd_textarea, HAL::config.wifi_pwd.c_str());
#endif
	lv_textarea_set_password_mode(ui.pwd_textarea, false);
	lv_textarea_set_one_line(ui.pwd_textarea, true);
	lv_obj_set_width(ui.pwd_textarea, lv_pct(80));
	lv_obj_set_style_radius(ui.pwd_textarea, 0, 0);
	// lv_obj_add_event_cb(ui.pwd_textarea, ta_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(ui.pwd_textarea, LV_OBJ_FLAG_HIDDEN);
	// if (LV_HOR_RES == 240)
	// {
	// lv_obj_set_height(ui.pwd_textarea, 25);
	lv_obj_align(ui.pwd_textarea, LV_ALIGN_TOP_MID, 0, 22 + 30);
	// }

	ui.pwd_label = lv_label_create(root);
	lv_label_set_text(ui.pwd_label, "wifi passwd:");
	lv_obj_set_style_text_color(ui.pwd_label, lv_color_white(), 0);
	lv_obj_set_style_text_font(ui.pwd_label, &lv_font_montserrat_14, 0);
	lv_obj_align_to(ui.pwd_label, ui.pwd_textarea, LV_ALIGN_OUT_TOP_LEFT, 0, -2);
	lv_obj_add_flag(ui.pwd_label, LV_OBJ_FLAG_HIDDEN);

	/*Create the one-line mode text area*/
	ui.name_textarea = lv_textarea_create(root);
	lv_textarea_set_text(ui.name_textarea, "");
#ifdef ARDUINO
	lv_textarea_set_text(ui.name_textarea, HAL::config.wifi_name.c_str());
#endif
	lv_textarea_set_one_line(ui.name_textarea, true);
	lv_textarea_set_password_mode(ui.name_textarea, false);
	lv_obj_set_width(ui.name_textarea, lv_pct(80));
	lv_obj_set_style_radius(ui.name_textarea, 0, 0);
	// lv_obj_add_event_cb(ui.name_textarea, ta_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(ui.name_textarea, LV_OBJ_FLAG_HIDDEN);
	// if (LV_HOR_RES == 240)
	// {
	// lv_obj_set_height(ui.name_textarea, 25);
	lv_obj_align(ui.name_textarea, LV_ALIGN_TOP_MID, 0, 22 + 30);
	// }

	ui.name_label = lv_label_create(root);
	lv_label_set_text(ui.name_label, "wifi name:");
	lv_obj_set_style_text_color(ui.name_label, lv_color_white(), 0);
	lv_obj_set_style_text_font(ui.name_label, &lv_font_montserrat_14, 0);
	lv_obj_align_to(ui.name_label, ui.name_textarea, LV_ALIGN_OUT_TOP_LEFT, 0, -2);
	lv_obj_add_flag(ui.name_label, LV_OBJ_FLAG_HIDDEN);

	/*Create a keyboard*/
	kb = lv_keyboard_create(root);
	lv_group_add_obj(ui.group, kb);
	lv_group_focus_obj(kb);

	// if (LV_HOR_RES == 240)
	// {
	lv_obj_set_size(kb, LV_HOR_RES, LV_VER_RES / 2);
	// }

	AttachEvent(root);
	AttachEvent(ui.name_textarea);
	AttachEvent(ui.pwd_textarea);
}

void WifiText::onViewDidLoad()
{
}

void WifiText::onViewWillAppear()
{
	lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), ui.group);
	StatusBar::SetStyle(StatusBar::STYLE_TRANSP);

	lv_obj_set_style_bg_color(root, lv_color_white(), LV_PART_MAIN);

	timer = lv_timer_create(onTimerUpdate, 500, this);
	lv_timer_ready(timer);

	lv_obj_fade_in(root, 300, 0);

	if (HAL::wifi_name_passswd == WIFI_SET_PWD)
	{
		lv_obj_add_flag(ui.name_textarea, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(ui.name_label, LV_OBJ_FLAG_HIDDEN);

		lv_obj_clear_flag(ui.pwd_textarea, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(ui.pwd_label, LV_OBJ_FLAG_HIDDEN);
		lv_keyboard_set_textarea(kb, ui.pwd_textarea);
	}
	else if (HAL::wifi_name_passswd == WIFI_SET_NAME)
	{
		lv_obj_add_flag(ui.pwd_textarea, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(ui.pwd_label, LV_OBJ_FLAG_HIDDEN);

		lv_obj_clear_flag(ui.name_textarea, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(ui.name_label, LV_OBJ_FLAG_HIDDEN);
		lv_keyboard_set_textarea(kb, ui.name_textarea);
	}
}

void WifiText::onViewDidAppear()
{
	// lv_group_focus_obj(View.ui.canvas);
}

void WifiText::onViewWillDisappear()
{
	lv_obj_fade_out(root, 300, 0);
}

void WifiText::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void WifiText::onViewDidUnload()
{
	// View.Delete();
	// Model.DeInit();
}

void WifiText::AttachEvent(lv_obj_t *obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void WifiText::Update()
{
}

void WifiText::onTimerUpdate(lv_timer_t *timer)
{
	WifiText *instance = (WifiText *)timer->user_data;
	instance->Update();
}

void WifiText::onEvent(lv_event_t *event)
{
	lv_obj_t *obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	auto *instance = (WifiText *)lv_obj_get_user_data(obj);

	if (code == LV_EVENT_RELEASED)
	{
		HAL::TerminalPrintln("WifiText LV_EVENT_PRESSED");
		instance->Manager->Pop();
	}
	else if (
		code == LV_EVENT_READY ||
		code == LV_EVENT_LONG_PRESSED ||
		code == LV_EVENT_CLICKED ||
		code == LV_EVENT_FOCUSED)
	{

		String text = lv_textarea_get_text(obj);
		LV_LOG_USER("Ready, current text: %s", text.c_str());

#ifdef ARDUINO
		if (obj == instance->ui.name_textarea)
		{
			HAL::config.wifi_name = text;
		}
		else
		{
			HAL::config.wifi_pwd = text;
		}
		HAL::config.host_name = "LithiumPeak";
		HAL::config_wifi_save();
#endif

		instance->Manager->Pop();
	}
}
