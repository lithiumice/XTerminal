#include "MusicDetail.h"
#include "HAL/HAL_Audio.h"
#include <ctime>
#include "HAL/HAL.h"
#include <stdio.h>
#include <stdlib.h>
#include "../NumTweak/NumTweak.h"
#include "HAL/HAL_Audio.h"
#include "HAL/HAL_SdCard.h"
#include "../../Lvgl_Wrapper.h"
#include "App/Utils/lv_lib_gif/lv_gif.h"
#include <vector>
#include <string>
#include "map"
#include "App/App.h"
#include "App/Pages/MusicPlayer/MusicPlayer.h"
extern std::string song_name;
Page::MusicDetail *MusicDetailPtr;
extern Page::MusicPlayer *MusicPlayerPtr;
int cur_play_time;
int total_play_time;

void PrevSong();
void NextSong();
void PlaySongIndex(int index);
using namespace Page;

MusicDetail::MusicDetail()
{
	MusicDetailPtr = this;
}

MusicDetail::~MusicDetail()
{
}

void MusicDetail::onCustomAttrConfig()
{
	SetCustomCacheEnable(true);
	SetCustomLoadAnimType(PageManager::LOAD_ANIM_MOVE_LEFT, 500, lv_anim_path_bounce);
}

static void set_angle(void *img, int32_t v)
{
	lv_img_set_angle((lv_obj_t *)img, v);
}

void MusicDetail::onViewLoad()
{

#ifndef ARDUINO
	extern fs::FS SD;
#endif
	MusicPlayerPtr->ListDirFiles(SD, "/", 0);

	audio_vol_plus();

	lv_obj_remove_style_all(root);

	lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
	StatusBar::SetStyle(StatusBar::STYLE_BLACK);
	lv_obj_set_style_bg_color(root, lv_color_black(), 0);

	ui.group = lv_group_create();

	// lv_obj_t *obj = lv_obj_create(root);
	// lv_obj_set_size(obj, LV_HOR_RES, LV_VER_RES);
	// lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
	// ui.play_disp = obj;

	// lv_obj_t* obj;

	lv_obj_t *label;
	lv_obj_t *obj = lv_img_create(root);
	lv_img_set_src(obj, Resource.GetImage("album"));
	lv_obj_align(obj, LV_ALIGN_CENTER, 0, -40);
	lv_img_set_zoom(obj, 160);
	ui.album = obj;

	lv_anim_t a;
	lv_anim_init(&a);
	lv_anim_set_var(&a, ui.album);
	lv_anim_set_exec_cb(&a, set_angle);
	lv_anim_set_values(&a, 0, 3600);
	lv_anim_set_time(&a, 3 * 5000);
	lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
	lv_anim_start(&a);

	int interval = 280 / 7;

	// next
	obj = lv_btn_create(root);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, nullptr);
	lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, -interval / 2, -20);
	// lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, 0, -20);
	lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
	ui.btn_next = obj;

	label = lv_label_create(obj);
	lv_label_set_text(label, LV_SYMBOL_NEXT);
	lv_obj_center(label);

	// pause
	obj = lv_btn_create(root);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, nullptr);
	lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, -interval * (3.0 / 2), -20);
	// lv_obj_align_to(obj, ui.btn_next, LV_ALIGN_OUT_LEFT_BOTTOM, -interval, 0);
	lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
	ui.btn_pause = obj;

	label = lv_label_create(obj);
	lv_label_set_text(label, LV_SYMBOL_PAUSE);
	lv_obj_center(label);
	ui.btn_pause_label = label;

	// prev
	obj = lv_btn_create(root);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, nullptr);
	lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, -interval * (5.0 / 2), -20);
	// lv_obj_align_to(obj, ui.btn_pause, LV_ALIGN_OUT_LEFT_BOTTOM, -interval, 0);
	lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
	ui.btn_prev = obj;

	label = lv_label_create(obj);
	lv_label_set_text(label, LV_SYMBOL_PREV);
	lv_obj_center(label);

	// duration
	lv_style_init(&ui.style_bg);
	lv_style_set_border_color(&ui.style_bg, lv_color_white());
	lv_style_set_border_width(&ui.style_bg, 2);
	lv_style_set_pad_all(&ui.style_bg, 4);
	lv_style_set_radius(&ui.style_bg, 0);
	lv_style_set_anim_time(&ui.style_bg, 500);

	lv_style_init(&ui.style_indic);
	lv_style_set_bg_opa(&ui.style_indic, LV_OPA_COVER);
	lv_style_set_bg_color(&ui.style_indic, lv_palette_main(LV_PALETTE_BLUE));
	lv_style_set_radius(&ui.style_indic, 0);

	obj = lv_bar_create(root);
	lv_bar_set_range(obj, 0, 100);
	lv_bar_set_value(obj, 0, LV_ANIM_ON);
	lv_obj_remove_style_all(obj);
	lv_obj_add_style(obj, &ui.style_bg, 0);
	lv_obj_add_style(obj, &ui.style_indic, LV_PART_INDICATOR);
	lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, -25, -60);
	lv_obj_set_size(obj, 170, 15);
	ui.duration_bar = obj;

	label = lv_label_create(root);
	lv_label_set_text(label, "00:00");
	lv_obj_align_to(label, ui.duration_bar, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, -5);
	lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
	lv_obj_set_style_text_color(label, lv_color_white(), 0);
	ui.duration_label = label;

	// list
	obj = lv_btn_create(root);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, nullptr);
	lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, interval * (1.0 / 2), -20);
	lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
	ui.btn_list = obj;

	label = lv_label_create(obj);
	lv_label_set_text(label, LV_SYMBOL_DRIVE);
	lv_obj_center(label);
	lv_obj_set_style_text_font(label, &lv_font_montserrat_12, 0);
	lv_obj_set_style_text_color(label, lv_color_white(), 0);

	// vol-
	obj = lv_btn_create(root);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, nullptr);
	lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, interval * (3.0 / 2), -20);
	lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
	ui.btn_vol_minus = obj;
	label = lv_label_create(obj);
	lv_label_set_text(label, LV_SYMBOL_VOLUME_MID);
	lv_obj_center(label);

	// vol+
	obj = lv_btn_create(root);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, nullptr);
	lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, interval * (5.0 / 2), -20);
	lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
	ui.btn_vol_plus = obj;
	label = lv_label_create(obj);
	lv_label_set_text(label, LV_SYMBOL_VOLUME_MAX);
	lv_obj_center(label);

	// name
	label = lv_label_create(root);
	lv_label_set_text(label, "song name.mp3");
	// lv_obj_align_to(label, ui.duration_bar, LV_ALIGN_OUT_TOP_MID, 0, -10);
	lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -80);
	lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
	lv_obj_set_style_text_color(label, lv_color_white(), 0);
	// lv_obj_set_size(label, LV_HOR_RES-15, 15);
	ui.song_name = label;

	// AttachEvent(root);
	AttachEvent(ui.btn_prev);
	AttachEvent(ui.btn_pause);
	AttachEvent(ui.btn_next);
	AttachEvent(ui.btn_list);
	AttachEvent(ui.btn_vol_minus);
	AttachEvent(ui.btn_vol_plus);

	// lv_group_add_obj(ui.group, root);
	lv_group_add_obj(ui.group, ui.btn_prev);
	lv_group_add_obj(ui.group, ui.btn_pause);
	lv_group_add_obj(ui.group, ui.btn_next);
	lv_group_add_obj(ui.group, ui.btn_list);
	lv_group_add_obj(ui.group, ui.btn_vol_minus);
	lv_group_add_obj(ui.group, ui.btn_vol_plus);

	lv_group_focus_obj(ui.btn_list);
}

void MusicDetail::onViewDidLoad()
{
	audio_init();

}

void MusicDetail::onViewWillAppear()
{
	lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), ui.group);
	StatusBar::SetStyle(StatusBar::STYLE_TRANSP);

	lv_obj_set_style_bg_color(root, lv_color_white(), LV_PART_MAIN);

	timer = lv_timer_create(onTimerUpdate, 1000, this);
	lv_timer_ready(timer);

	lv_obj_fade_in(root, 300, 0);

	lv_label_set_text(ui.song_name, song_name.c_str());
}

void MusicDetail::onViewDidAppear()
{
	gflag.audio_en_flag = 1;

	__ExecuteOnce(
		// PlaySongIndex(0)
		audio_play("0.mp3")
		);
}

void MusicDetail::onViewWillDisappear()
{
	lv_obj_fade_out(root, 300, 0);
	// gflag.audio_en_flag = 0;
}

void MusicDetail::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void MusicDetail::onViewDidUnload()
{
	lv_group_del(ui.group);
	audio_delete();
}

void MusicDetail::AttachEvent(lv_obj_t *obj)
{
	// if (obj != nullptr)
	// {
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
	// }
}

void MusicDetail::Update()
{

	
#ifdef ARDUINO
	cur_play_time = audio->getTotalPlayingTime() / 1000;
	total_play_time = audio->getAudioFileDuration();

	// printf("pos: %d -- ", cur_play_time);
	// printf("%d\n", total_play_time);
#endif

	lv_label_set_text_fmt(ui.duration_label, "%2d:%2d", cur_play_time, total_play_time);

	if (total_play_time > 0)
	{

		lv_bar_set_range(ui.duration_bar, 0, total_play_time);
		lv_bar_set_value(ui.duration_bar, cur_play_time, LV_ANIM_OFF);
	}
	else
	{

		lv_bar_set_range(ui.duration_bar, 0, 10);
		lv_bar_set_value(ui.duration_bar, 0, LV_ANIM_OFF);
	}
}

void MusicDetail::onTimerUpdate(lv_timer_t *timer)
{
	MusicDetail *instance = (MusicDetail *)timer->user_data;
	instance->Update();
}

void audio_eof_mp3(const char *info)
{

	NextSong();

	printf("eof_mp3     ");
	printf(info);
}

void MusicDetail::onEvent(lv_event_t *event)
{
	lv_obj_t *obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	auto *instance = (MusicDetail *)lv_obj_get_user_data(obj);

	if (code == LV_EVENT_CLICKED)
	{
		static uint64_t last_btn_pressed_time = 0;

		if (millis() - last_btn_pressed_time < 300)
		{
			last_btn_pressed_time = millis();

			return;
		}
		else
		{
			last_btn_pressed_time = millis();
		}

		if (obj == instance->ui.btn_prev)
		{
			PrevSong();
		}
		else if (obj == instance->ui.btn_pause)
		{
			static int is_pause = 0;
			if (is_pause)
			{
				is_pause = 0;
				lv_label_set_text(instance->ui.btn_pause_label, LV_SYMBOL_PAUSE);
				audio_resume();
			}
			else
			{
				is_pause = 1;
				lv_label_set_text(instance->ui.btn_pause_label, LV_SYMBOL_PLAY);
				audio_pause();
			}
			// char* txt=lv_label_get_text(instance->ui.btn_pause_label);
			// if(strcmp(txt,LV_SYMBOL_PLAY)==0)
			// {
			// lv_label_set_text(instance->ui.btn_pause_label, LV_SYMBOL_PAUSE);
			// audio_resume();
			//
			// }else{
			// lv_label_set_text(instance->ui.btn_pause_label, LV_SYMBOL_PLAY);
			// audio_pause();
			//
			// }
		}
		else if (obj == instance->ui.btn_next)
		{
			NextSong();
		}
		else if (obj == instance->ui.btn_list)
		{
			MusicDetailPtr->Manager->Push("Pages/MusicPlayer");
		}
		else if (obj == instance->ui.btn_vol_minus)
		{
			audio_vol_minus();
		}
		else if (obj == instance->ui.btn_vol_plus)
		{
			audio_vol_plus();
		}
	}

	// else if (code == LV_EVENT_LONG_PRESSED)
	// {
	// 	MusicDetailPtr->Manager->BackHome();
	// }
}
