#include "WeatherView.h"
#include <map>

#include "HAL/HAL.h"

#ifdef ARDUINO
#include "WString.h"
#else
#include "WString/WString.h"
#endif

using namespace Page;
extern std::map<String, int> weather_str2int;
extern String ari_level_int2str[];
extern String weather_int2name[];

// char weekDayCh[7][5] = { "周一","周二", "周一", "周一", "周一", "周一", "周一" };
// xue、lei、shachen、wu、bingbao、yun、yu、yin、qing
void WeatherView::weather_group_add(lv_obj_t* root)
{
	ui.group = lv_group_create();

	lv_group_add_obj(ui.group, root);
	lv_group_add_obj(ui.group, ui.weatherImg);
	lv_group_add_obj(ui.group, ui.cityLabel);
	lv_group_add_obj(ui.group, ui.airLabel);
	lv_group_add_obj(ui.group, ui.txtLabel);
	lv_group_add_obj(ui.group, ui.clockLabel_1);
	lv_group_add_obj(ui.group, ui.clockLabel_2);
	lv_group_add_obj(ui.group, ui.dateLabel);
	lv_group_add_obj(ui.group, ui.tempImg);
	lv_group_add_obj(ui.group, ui.tempBar);
	lv_group_add_obj(ui.group, ui.tempLabel);
	lv_group_add_obj(ui.group, ui.humiImg);
	lv_group_add_obj(ui.group, ui.humiBar);
	lv_group_add_obj(ui.group, ui.humiImg);
	lv_group_add_obj(ui.group, ui.humiLabel);
	lv_group_add_obj(ui.group, ui.spaceImg);
}

void WeatherView::weather_style_init(void)
{

	lv_style_init(&ui.style_bg);
	lv_style_set_border_color(&ui.style_bg, lv_color_white());
	// lv_style_set_border_color(&ui.style_bg, lv_palette_main(LV_PALETTE_BLUE));
	lv_style_set_border_width(&ui.style_bg, 2);
	lv_style_set_pad_all(&ui.style_bg, 4); 
	lv_style_set_radius(&ui.style_bg, 0);
	lv_style_set_anim_time(&ui.style_bg, 500);

	lv_style_init(&ui.style_indic);
	lv_style_set_bg_opa(&ui.style_indic, LV_OPA_COVER);
	lv_style_set_bg_color(&ui.style_indic, lv_palette_main(LV_PALETTE_BLUE));
	lv_style_set_radius(&ui.style_indic, 0);
}

void WeatherView::weather_gui_init(lv_obj_t* root)
{
	ui.weatherImg = lv_img_create(root);
	lv_img_set_src(ui.weatherImg, weaImage_map[0]);
	lv_obj_set_pos(ui.weatherImg, 15, 30);

	ui.cityLabel = lv_label_create(root);
	lv_label_set_recolor(ui.cityLabel, true);
	lv_label_set_text(ui.cityLabel, "Chongqing");
	lv_obj_set_style_text_font(ui.cityLabel, &lv_font_montserrat_20, 0);
	lv_obj_set_style_text_color(ui.cityLabel, lv_color_white(), 0);
	// lv_obj_align(ui.cityLabel, LV_ALIGN_TOP_MID, 0, 120);
	lv_obj_set_pos(ui.cityLabel, 115, 25 + 5);
	
	ui.airLabel = lv_label_create(root);
	lv_label_set_recolor(ui.airLabel, true);
	lv_label_set_text_fmt(ui.airLabel, "AirLevel: #ffa500 %s#", "Good");
	lv_obj_set_style_text_font(ui.airLabel, &lv_font_montserrat_12, 0);
	lv_obj_set_style_text_color(ui.airLabel, lv_color_white(), 0);
	lv_obj_set_pos(ui.airLabel, 115, 55);

	ui.weatherLabel = lv_label_create(root);
	lv_label_set_recolor(ui.weatherLabel, true);
	lv_label_set_text_fmt(ui.weatherLabel, "Weather: #ffa500 %s#", "Sunny");
	lv_obj_set_style_text_font(ui.weatherLabel, &lv_font_montserrat_12, 0);
	lv_obj_set_style_text_color(ui.weatherLabel, lv_color_white(), 0);
	lv_obj_set_pos(ui.weatherLabel, 115, 75);

	ui.txtLabel = lv_label_create(root);
	lv_obj_set_size(ui.txtLabel, 200, 50);
	lv_label_set_long_mode(ui.txtLabel, LV_LABEL_LONG_WRAP);
	lv_label_set_text_fmt(ui.txtLabel,
		"lowestTemp %d C, HighestTemp %d C, %s",
		15, 20, "EastNorthWind");
	lv_obj_set_style_text_font(ui.txtLabel, &lv_font_montserrat_10, 0);
	lv_obj_set_style_text_color(ui.txtLabel, lv_color_white(), 0);
	lv_obj_align(ui.txtLabel, LV_ALIGN_TOP_MID, 0, 150);
	// lv_obj_set_pos(ui.txtLabel, 100, 160);



	ui.clockLabel_1 = lv_label_create(root);
	lv_label_set_recolor(ui.clockLabel_1, true);
	lv_label_set_text_fmt(ui.clockLabel_1, "%02d : #ffa500 %02d#", 10, 52);
	lv_obj_set_style_text_font(ui.clockLabel_1, Resource.GetFont("HandGotn_26"), 0);
	// lv_obj_set_style_text_font(ui.clockLabel_1, &lv_font_montserrat_26, 0);
	lv_obj_set_style_text_color(ui.clockLabel_1, lv_color_white(), 0);
	lv_obj_align(ui.clockLabel_1, LV_ALIGN_TOP_MID, 0, 100);

	ui.clockLabel_2 = lv_label_create(root);
	lv_label_set_recolor(ui.clockLabel_2, true);
	lv_label_set_text_fmt(ui.clockLabel_2, "%02d", 00);
	lv_obj_set_style_text_font(ui.clockLabel_2, &lv_font_montserrat_12, 0);
	// lv_obj_set_style_text_font(ui.clockLabel_2, Resource.GetFont("HandGotn_26"), 0);
	lv_obj_set_style_text_color(ui.clockLabel_2, lv_color_white(), 0);
	lv_obj_align_to(ui.clockLabel_2,ui.clockLabel_1, LV_ALIGN_OUT_RIGHT_BOTTOM, 6, 0);



	ui.dateLabel = lv_label_create(root);
	lv_label_set_text_fmt(ui.dateLabel,
		"month %2d day %2d",
		11, 23);
	lv_obj_set_style_text_font(ui.dateLabel, &lv_font_montserrat_10, 0);
	lv_obj_set_style_text_color(ui.dateLabel, lv_color_white(), 0);
	lv_obj_align(ui.dateLabel, LV_ALIGN_TOP_MID, 0, 130);



	ui.tempImg = lv_img_create(root);
	lv_img_set_src(ui.tempImg, &temp);
	lv_img_set_zoom(ui.tempImg, 180);
	ui.tempBar = lv_bar_create(root);
	lv_bar_set_range(ui.tempBar, 0, 40);
	lv_bar_set_value(ui.tempBar, 10, LV_ANIM_ON);
	lv_obj_remove_style_all(ui.tempBar); 
	lv_obj_add_style(ui.tempBar, &ui.style_bg, 0);
	lv_obj_add_style(ui.tempBar, &ui.style_indic, LV_PART_INDICATOR);
	lv_obj_set_size(ui.tempBar, 60, 12);
	ui.tempLabel = lv_label_create(root);
	lv_label_set_text_fmt(ui.tempLabel, "%2d C", 18);
	lv_obj_set_style_text_font(ui.tempLabel, &lv_font_montserrat_14, 0);
	lv_obj_set_style_text_color(ui.tempLabel, lv_color_white(), 0);
	lv_obj_align(ui.tempImg, LV_ALIGN_LEFT_MID, 10, 70);
	lv_obj_align(ui.tempBar, LV_ALIGN_LEFT_MID, 35, 70);
	lv_obj_align(ui.tempLabel, LV_ALIGN_LEFT_MID, 100, 70);



	ui.humiImg = lv_img_create(root);
	lv_img_set_src(ui.humiImg, &humi);
	lv_img_set_zoom(ui.humiImg, 180);
	ui.humiBar = lv_bar_create(root);
	lv_bar_set_range(ui.humiBar, 0, 100);
	lv_bar_set_value(ui.humiBar, 49, LV_ANIM_ON);
	lv_obj_remove_style_all(ui.humiBar);
	lv_obj_add_style(ui.humiBar, &ui.style_bg, 0);
	lv_obj_add_style(ui.humiBar, &ui.style_indic, LV_PART_INDICATOR);
	lv_obj_set_size(ui.humiBar, 60, 12);
	ui.humiLabel = lv_label_create(root);
	lv_label_set_text(ui.humiLabel, "49%");
	lv_obj_set_style_text_font(ui.humiLabel, &lv_font_montserrat_14, 0);
	lv_obj_set_style_text_color(ui.humiLabel, lv_color_white(), 0);
	lv_obj_align(ui.humiImg, LV_ALIGN_LEFT_MID, 0, 100);
	lv_obj_align(ui.humiBar, LV_ALIGN_LEFT_MID, 35, 100);
	lv_obj_align(ui.humiLabel, LV_ALIGN_LEFT_MID, 100, 100);



	ui.spaceImg = lv_img_create(root);
	lv_img_set_src(ui.spaceImg, manImage_map[0]);
	lv_obj_align(ui.spaceImg, LV_ALIGN_BOTTOM_RIGHT, 0,0);
	// lv_img_set_zoom(ui.spaceImg, LV_IMG_Z);

}

//data
void WeatherView::SetCityName(const char* cityName)
{
	lv_label_set_text(
		ui.cityLabel,
		cityName
	);
}

void WeatherView::SetWeather(const char* weather_pinyin)
{
	int code = weather_str2int[weather_pinyin];
	const char* name = weather_int2name[code].c_str();
	lv_img_set_src(
		ui.weatherImg,
		weaImage_map[code]
	);
	lv_label_set_text_fmt(
		ui.weatherLabel,
		"Weather: #ffa500 %s#",
		name
	);
}

void WeatherView::SetAirLevel(const int airLevel)
{
	if (airLevel < 0 || airLevel>5)
	{
		HAL::TerminalPrintln("error air level");
		return;
	}
	const char* name = ari_level_int2str[airLevel].c_str();
	lv_label_set_text_fmt(
		ui.airLabel,
		"AirLevel: #ffa500 %s#",
		name
	);
}

void WeatherView::SetTemperatue(const int temperatue)
{
	lv_bar_set_value(
		ui.tempBar,
		temperatue,
		LV_ANIM_ON
	);

	lv_label_set_text_fmt(
		ui.tempLabel,
		"%2dC",
		temperatue
	);

}

void WeatherView::SetHuminature(const int huminature)
{

	lv_bar_set_value(
		ui.humiBar,
		huminature,
		LV_ANIM_ON
	);

	lv_label_set_text_fmt(
		ui.humiLabel,
		"%2d%%",
		huminature
	);

}

//info
void WeatherView::SetTextInfo(const int minTemp, const int maxTemp, const char* windDir, const int windLevel)
{
	lv_label_set_text_fmt(
		ui.txtLabel,
		"minTemp:%dC, maxTemp:%dC, windDir:%s, winlevel:%d",
		minTemp,
		maxTemp,
		windDir,
		windLevel
	);
}

//time 
void WeatherView::SetClockDay(const int month, const int day)
{

	lv_label_set_text_fmt(
		ui.dateLabel,
		"month %2d day %2d",
		month,
		day
	);
}

void WeatherView::SetClockHour(const int hour, const int min)
{
	lv_label_set_text_fmt(
		ui.clockLabel_1,
		"%02d : #ffa500 %02d#",
		hour,
		min
	);
}

void WeatherView::SetClockSec(const int sec)
{

	lv_label_set_text_fmt(
		ui.clockLabel_2,
		"%02d",
		// "%02d sec",
		// "%02d\nseconds",
		sec
	);
}

//model
void WeatherView::Create(lv_obj_t* root)
{
	lv_obj_remove_style_all(root);
	lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);

	weather_style_init();
	weather_gui_init(root);
	// weather_group_add(root);
	ui.group = lv_group_create();
	lv_group_add_obj(ui.group, root);
}


void WeatherView::Delete()
{
	lv_group_del(ui.group);
}
