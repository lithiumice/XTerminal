#include "AppList.h"
#include "App/App.h"
#include "App/Configs/Version.h"
#include "HAL/HAL.h"
using namespace Page;
uint64_t enter_time = 0;
extern uint8_t anim_img_select;

AppList::AppList()
{
}

AppList::~AppList()
{
}

void AppList::onCustomAttrConfig()
{
}

void AppList::onViewLoad()
{
	enter_time = millis();

	View.Create(root);
	AttachEvent(root);

#define APPLIST_DEF(className) \
	AttachEvent(View.ui.className.icon);
#include "_APPLIST_DEF.inc"
#undef APPLIST_DEF
}

void AppList::onViewDidLoad()
{
// #ifdef ARDUINO
// 	HAL::SD_Init();
// #endif
}

void AppList::onViewWillAppear()
{
	lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), View.ui.group);
	StatusBar::SetStyle(StatusBar::STYLE_TRANSP);

	timer = lv_timer_create(onTimerUpdate, 100, this);
	lv_timer_ready(timer);

	View.SetScrollToY(root, -LV_VER_RES, LV_ANIM_OFF);
	lv_obj_fade_in(root, 300, 0);
}

void AppList::onViewDidAppear()
{
	View.onFocus(View.ui.group);
}

void AppList::onViewWillDisappear()
{
	lv_obj_fade_out(root, 300, 0);
}

void AppList::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void AppList::onViewDidUnload()
{
	View.Delete();
}

void AppList::AttachEvent(lv_obj_t *obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void AppList::Update()
{

	// static uint8_t auto_entered_weather_flag=0;
	// if(
	// 	// HAL::config.auto_enter_weather&&
	//     HAL::enc_btn_first_push_flag==0&&
	//     auto_entered_weather_flag==0&&
	//     millis()-enter_time>= 1000*HAL::config.auto_enter_weather_delay_sec)
	// {
	//     auto_entered_weather_flag=1;
	//     Manager->Push("Pages/Weather");
	// }
}

void AppList::onTimerUpdate(lv_timer_t *timer)
{
	AppList *instance = (AppList *)timer->user_data;

	instance->Update();
}
void AudioUpdate(void *parameter);

void AppList::onEvent(lv_event_t *event)
{
	lv_obj_t *obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	auto *instance = (AppList *)lv_obj_get_user_data(obj);
	if (code == LV_EVENT_RELEASED)
	{
		if (obj == instance->View.ui.MusicDetail.icon)
		{
			instance->Manager->Pop();
			App_keep_music();

#ifdef ARDUINO
			xTaskCreatePinnedToCore(
				AudioUpdate,
				"AudioUpdate",
				1024 * 6, // KB
				nullptr,
				0,
				nullptr,
				0);

#endif
		}

		if (obj == instance->View.ui.HeartBeat.icon)
		{

#ifdef ARDUINO
			 Wire1.begin(CONFIG_IIC2_SDA_PIN, CONFIG_IIC2_SCL_PIN);
			HAL::sensors_init();
#endif
		}

#define APPLIST_DEF(name)                        \
	if (obj == instance->View.ui.name.icon)      \
	{                                            \
		instance->Manager->Push("Pages/" #name); \
	}

#include "_APPLIST_DEF.inc"

#undef APPLIST_DEF
	}
}
