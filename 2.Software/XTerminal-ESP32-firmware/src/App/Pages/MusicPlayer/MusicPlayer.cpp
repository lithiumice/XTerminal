#include "MusicPlayer.h"
#include "../MusicDetail/MusicDetail.h"
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

#include "Arduino.h"
#include "map"
#include "App/App.h"
#include "Game/GamePrivate.h"

std::map<int, std::string> map_file_list;
int map_file_list_current = 0;
Page::MusicPlayer* MusicPlayerPtr;
std::string song_name = "click to open file list";
extern Page::MusicDetail* MusicDetailPtr;
#define list_max_item 7
lv_obj_t* label_list[list_max_item];

int list_item_cur_index = 0;
int list_item_page_index = 0;
int last_list_item_page_index = 0;
int list_page_cur_index = 0;
int list_page_max_index = 0;
int list_item_max_index = 0;
int last_page_index = 0;

static lv_obj_t* currentButton = NULL;
void PrevSong();
void NextSong();
void PlaySongIndex(int index);

#ifdef ARDUINO
#else
fs::FS SD;
static const char* title_list[] = {
	"Waiting for true love.mp3",
	"Need a Better Future.wav",
	"Vibrations~~.ogg",
	"/Why now?.mp3",
	"Never Look Back",
	"It happened Yesterday",
	"Feeling so High",
	"Go Deeper",
	"Find You There",
	"Until the End",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
};
#endif

using namespace Page;

MusicPlayer::MusicPlayer()
{
	MusicPlayerPtr = this;
}

MusicPlayer::~MusicPlayer()
{
}

void MusicPlayer::onCustomAttrConfig()
{
	SetCustomCacheEnable(true);
	SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE, 500, lv_anim_path_bounce);
	// SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_bounce);
}
static void SongBtnCallback(lv_event_t* event);

void MusicPlayer::onViewLoad()
{
	lv_obj_remove_style_all(root);

	lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
	StatusBar::SetStyle(StatusBar::STYLE_TRANSP);
	lv_obj_set_style_bg_color(root, lv_color_black(), 0);

	ui.group = lv_group_create();

	lv_obj_t* label = lv_label_create(root);
	lv_label_set_text(label, "SD File List");
	lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 22);
	lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
	lv_obj_set_style_text_color(label, lv_color_white(), 0);

	int off = 22 + 15;
	lv_obj_t* list = lv_list_create(root);
	// lv_obj_set_pos(list, 0,off);
	lv_obj_set_size(list, LV_HOR_RES, LV_VER_RES - off);
	lv_obj_align(list, LV_ALIGN_TOP_MID, 0, off);
	lv_obj_set_style_radius(list, 0, 0);
	lv_obj_set_style_bg_color(list, lv_color_black(), 0);
	lv_obj_set_style_border_width(list, 0, 0);
	ui.file_list = list;

	// ListDirFiles(SD, "/", 0);

	static lv_style_t style;
	lv_style_init(&style);

	lv_style_set_radius(&style, 0);
	lv_style_set_height(&style, lv_pct(100/7));

	lv_style_set_bg_opa(&style, LV_OPA_100);
	lv_style_set_bg_color(&style, lv_color_black());
	// lv_style_set_bg_grad_color(&style, lv_palette_darken(LV_PALETTE_BLUE, 2));
	// lv_style_set_bg_grad_dir(&style, LV_GRAD_DIR_VER);

	// lv_style_set_border_opa(&style, LV_OPA_40);
	lv_style_set_border_width(&style, 2);
	lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_GREY));

	// lv_style_set_shadow_width(&style, 8);
	// lv_style_set_shadow_color(&style, lv_palette_main(LV_PALETTE_GREY));
	// lv_style_set_shadow_ofs_y(&style, 8);
	//
	// lv_style_set_outline_opa(&style, LV_OPA_COVER);
	// lv_style_set_outline_color(&style, lv_palette_main(LV_PALETTE_BLUE));

	lv_style_set_text_color(&style, lv_color_white());
	lv_style_set_pad_all(&style, 10);


	lv_obj_t* btn;
	int i;
	for (i = 0; i < list_max_item; i++)
	{
		btn = lv_btn_create(ui.file_list);
		lv_obj_set_width(btn, lv_pct(100));
		lv_obj_add_event_cb(btn, onEvent, LV_EVENT_CLICKED, NULL);
		lv_obj_add_style(btn, &style, 0);

		// lv_obj_set_user_data(btn, this);
		// lv_obj_add_event_cb(btn, SongBtnCallback, LV_EVENT_CLICKED, this);

		lv_obj_t* lab = lv_label_create(btn);
		lv_label_set_text_fmt(lab, "Item %d", i);
		label_list[i] = lab;
	}


	lv_group_add_obj(ui.group, ui.file_list);
	AttachEvent(ui.file_list);
	lv_group_focus_obj(ui.file_list);

	
	__ExecuteOnce(
		App_remove("AppList")
	);
}

void MusicPlayer::onViewDidLoad()
{
	// for(int i=0;i<8;i++)
	// // for(int i=0;i<map_file_list.size();i++)
	// {
	// 	lv_obj_t* list_file_btn = lv_list_add_btn(ui.file_list, nullptr, map_file_list[i].c_str());
	// 	lv_group_add_obj(ui.group, list_file_btn);
	// 	lv_obj_set_style_text_font(list_file_btn, &lv_font_montserrat_14, 0);
	// 	lv_obj_set_style_text_color(list_file_btn, lv_color_white(), 0);
	// 	lv_obj_set_style_bg_color(list_file_btn, lv_color_black(), 0);
	//
	// 	lv_obj_set_user_data(list_file_btn, this);
	// 	lv_obj_add_event_cb(list_file_btn, onEvent, LV_EVENT_ALL, this);
	//
	// }

	// for(int i=0; i < list_max_item;i++)
	// {
	// 	lv_obj_t* list_file_btn = lv_list_add_btn(ui.file_list, LV_SYMBOL_AUDIO, NULL);
	// 	// lv_group_add_obj(ui.group, list_file_btn);
	// 	lv_obj_set_style_text_font(list_file_btn, &lv_font_montserrat_14, 0);
	// 	lv_obj_set_style_text_color(list_file_btn, lv_color_white(), 0);
	// 	lv_obj_set_style_bg_color(list_file_btn, lv_color_black(), 0);
	//
	// 	lv_obj_t* label = lv_label_create(list_file_btn);
	// 	lv_label_set_text(label, "test");
	// 	lv_obj_center(label);
	// 	label_list[i] = label;
	//
	// 	lv_obj_set_user_data(list_file_btn, this);
	// 	lv_obj_add_event_cb(list_file_btn, onEvent, LV_EVENT_ALL, this);
	// 	}

	
}

void MusicPlayer::onViewWillAppear()
{
	lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), ui.group);
	StatusBar::SetStyle(StatusBar::STYLE_TRANSP);

	lv_obj_set_style_bg_color(root, lv_color_white(), LV_PART_MAIN);

	timer = lv_timer_create(onTimerUpdate, 500, this);
	lv_timer_ready(timer);

	lv_obj_fade_in(root, 300, 0);

}

void update_list()
{
	list_page_cur_index = list_item_cur_index / list_max_item;
	list_item_page_index = list_item_cur_index - (list_page_cur_index * list_max_item);
}
void MusicPlayer::onViewDidAppear()
{

	list_item_max_index = map_file_list.size();
	list_page_max_index = map_file_list.size() / list_max_item;


	for (int i = 0; i < list_max_item; i++)
	{
		int index = list_page_cur_index * list_max_item + i;

		if(index>=list_item_max_index)
		{
			const char* name = map_file_list.at(0).c_str();
			lv_label_set_text(label_list[i], name);

		}else
		{
			const char* name = map_file_list.at(index).c_str();
			lv_label_set_text(label_list[i], name);

		}
	
	
	}

	update_list();
	currentButton = lv_obj_get_child(ui.file_list, list_item_page_index);
	lv_obj_add_state(currentButton, LV_STATE_CHECKED);

}


void MusicPlayer::onViewWillDisappear()
{
	lv_obj_fade_out(root, 300, 0);
}

void MusicPlayer::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void MusicPlayer::onViewDidUnload()
{
	lv_group_del(ui.group);
}

void MusicPlayer::AttachEvent(lv_obj_t* obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void MusicPlayer::Update()
{
	// int ui_index = 0;
	// int start_pos = UI_LIST_MAX_LEN * ui_option.current_title_page;
	// int end_pos = (UI_TITLE_LEN - start_pos) > UI_LIST_MAX_LEN ? UI_LIST_MAX_LEN : (UI_TITLE_LEN - start_pos);
	//
	// for (int i = start_pos; i < start_pos + end_pos; i++)
	// {
	// 	ui_title_x x_1 = ui_title_y[i];
	// 	std::string ui_str = "   " + (std::string)x_1.title;
	//
	// 	if (ui_index == (ui_option.cursor_level0 % UI_LIST_MAX_LEN))
	// 	{
	// 		ui_str[1] = '>';
	// 	}
	// 	else
	// 	{
	// 		ui_str[1] = ' ';
	// 	}
	// 	MyOLED_P6x8Str(0, ui_index, (uint8*)ui_str.data());
	// 	ui_index++;
	// }
}

void MusicPlayer::onTimerUpdate(lv_timer_t* timer)
{
	MusicPlayer* instance = (MusicPlayer*)timer->user_data;
	instance->Update();
}

void MusicPlayer::onEvent(lv_event_t* event)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	auto* instance = (MusicPlayer*)lv_obj_get_user_data(obj);

	if (obj == instance->ui.file_list)
	{
		if (code == LV_EVENT_KEY)
		{
			uint32_t key = (*(uint32_t*)event->param);
			last_page_index = list_page_cur_index;
			last_list_item_page_index = list_item_page_index;

			if (key == LV_KEY_LEFT)
			{
				__ValuePlus(list_item_cur_index, -1, 0, list_item_max_index - 1);
								
				update_list();

			}
			else if (key == LV_KEY_RIGHT)
			{
				__ValuePlus(list_item_cur_index, 1, 0, list_item_max_index - 1);
				update_list();

				
			}

			if (list_page_cur_index != last_page_index)
			{
				MusicPlayerPtr->onViewDidAppear();
			}

			currentButton = lv_obj_get_child(instance->ui.file_list, list_item_page_index);
			lv_obj_add_state(currentButton, LV_STATE_CHECKED);

			currentButton = lv_obj_get_child(instance->ui.file_list, last_list_item_page_index);
			lv_obj_clear_state(currentButton, LV_STATE_CHECKED);
		}else if(code==LV_EVENT_CLICKED)
		{
			PlaySongIndex(list_item_cur_index);
			MusicPlayerPtr->Manager->Pop();
		}
	}

	if (code == LV_EVENT_LONG_PRESSED)
	{
		MusicPlayerPtr->Manager->Pop();
	}
}

// static void SongBtnCallback(lv_event_t* event)
// {
// 	lv_obj_t* obj = lv_event_get_target(event);
// 	lv_event_code_t code = lv_event_get_code(event);
// 	// auto* instance = (MusicPlayer*)lv_obj_get_user_data(obj);
//
//
// 	if (code == LV_EVENT_PRESSED ||
// 		code == LV_EVENT_CLICKED)
// 	{
// 		const char* name = lv_list_get_btn_text(MusicPlayerPtr->ui.file_list, obj);
// 		map_file_list_current = 0;
// 		std::map<int, std::string>::reverse_iterator iter;
// 		for (iter = map_file_list.rbegin(); iter != map_file_list.rend(); iter++)
// 		{
// 			if (iter->second == std::string(name))
// 			{
// 				map_file_list_current = iter->first;
// 				break;
// 			}
// 		}
// 		PlaySongIndex(map_file_list_current);
// 		MusicPlayerPtr->Manager->Pop();
// 	}
// }

static void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

void PlaySongIndex(int index)
{
	gflag.audio_en_flag = 0;

#ifdef ARDUINO
	audio->stopSong();
#endif

	delay(100);
	const char* name = map_file_list[index].c_str();
	audio_play(name);

	std::string tmp = std::string(name);
	std::vector<std::string> v;
	std::string c = std::string("/");
	SplitString(tmp, v, c);
	std::string after_fix = *v.rbegin();
	song_name = after_fix;
	lv_label_set_text(MusicDetailPtr->ui.song_name, song_name.c_str());

	gflag.audio_en_flag = 1;
}

void NextSong()
{
	__ValuePlus(list_item_cur_index, 1, 0, list_item_max_index - 1);

	PlaySongIndex(list_item_cur_index);
	update_list();
}

void PrevSong()
{
	__ValuePlus(list_item_cur_index, -1, 0, list_item_max_index - 1);

	PlaySongIndex(list_item_cur_index);
	update_list();
}

void MusicPlayer::ListDirFiles(fs::FS& fs, const char* dirname, uint8_t levels)
{
#ifdef ARDUINO
	Serial.printf("Listing directory: %s\n", dirname);

	File root = fs.open(dirname);
	if (!root)
	{
		Serial.println("Failed to open directory");
		return;
	}
	if (!root.isDirectory())
	{
		Serial.println("Not a directory");
		return;
	}

	File file = root.openNextFile();
	int file_index = 0;

	while (file)
	{
		// if (file.isDirectory())
		// {
		// 	Serial.print("  DIR : ");
		// 	Serial.println(file.name());
		// 	if (levels)
		// 	{
		// 	    ListDirFiles(fs, file.name(), levels - 1);
		// 	}
		// }
		// else
		std::string tmp = std::string(file.name());
		std::vector<std::string> v;
		std::string c = std::string(".");
		SplitString(tmp, v, c);
		std::string after_fix = *v.rbegin();

		if (!file.isDirectory() &&
			(after_fix == "mp3" ||
			 after_fix == "aac" ||
			 after_fix == "m4a" ||
			 after_fix == "flac" ||
			 after_fix == "wav"))
		{
			Serial.print("  FILE: ");
			Serial.print(file.name());
			Serial.print("  SIZE: ");
			Serial.println(file.size());

			// lv_obj_t *list_file_btn = lv_list_add_btn(ui.file_list, nullptr, file.name());
			// lv_group_add_obj(ui.group, list_file_btn);
			// lv_obj_set_style_text_font(list_file_btn, &lv_font_montserrat_14, 0);
			// lv_obj_set_style_text_color(list_file_btn, lv_color_white(), 0);
			// lv_obj_set_style_bg_color(list_file_btn, lv_color_black(), 0);
			//
			// lv_obj_set_user_data(list_file_btn, this);
			// lv_obj_add_event_cb(list_file_btn, onEvent, LV_EVENT_ALL, this);

			map_file_list.insert(std::map<int, std::string>::value_type(file_index, file.name()));
			file_index++;
		}
		file = root.openNextFile();
	}

#else
	int file_index = 0;
	map_file_list.clear();

	for (int i = 0; i < sizeof(title_list) / sizeof(title_list[0]); i++)
	{
		std::string tmp = std::string(title_list[i]);
		std::vector<std::string> v;
		std::string c = std::string(".");
		SplitString(tmp, v, c);
		std::string after_fix = *v.rbegin();

		// if (after_fix == "mp3" ||
		// 	after_fix == "aac" ||
		// 	after_fix == "m4a" ||
		// 	after_fix == "flac" ||
		// 	after_fix == "wav")
		// {
		//

		map_file_list.insert(std::map<int, std::string>::value_type(file_index, title_list[i]));
		file_index++;
		// }
	}

#endif
}
