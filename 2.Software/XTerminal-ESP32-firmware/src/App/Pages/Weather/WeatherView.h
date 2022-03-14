#ifndef __Weather_VIEW_H
#define __Weather_VIEW_H

#include "../Page.h"

extern "C"
{
	extern lv_img_dsc_t love_0;
extern lv_img_dsc_t love_1;
extern lv_img_dsc_t love_2;
extern lv_img_dsc_t love_3;
extern lv_img_dsc_t love_4;
extern lv_img_dsc_t love_5;
extern lv_img_dsc_t love_6;
extern lv_img_dsc_t love_7;
extern lv_img_dsc_t love_8;
extern lv_img_dsc_t love_9;
extern lv_img_dsc_t love_10;
extern lv_img_dsc_t love_11;
extern lv_img_dsc_t love_12;
extern lv_img_dsc_t love_13;
extern lv_img_dsc_t love_14;
extern lv_img_dsc_t love_15;
extern lv_img_dsc_t love_16;
extern lv_img_dsc_t love_17;
extern lv_img_dsc_t love_18;
extern lv_img_dsc_t love_19;
extern lv_img_dsc_t love_20;
extern lv_img_dsc_t love_21;
extern lv_img_dsc_t love_22;
extern lv_img_dsc_t love_23;
extern lv_img_dsc_t love_24;
extern lv_img_dsc_t love_25;
extern lv_img_dsc_t love_26;
extern lv_img_dsc_t love_27;
extern lv_img_dsc_t love_28;
extern lv_img_dsc_t love_29;
extern lv_img_dsc_t love_30;

	extern lv_img_dsc_t plus_0;
	extern lv_img_dsc_t plus_1;
	extern lv_img_dsc_t plus_2;
	extern lv_img_dsc_t plus_3;
	extern lv_img_dsc_t plus_4;
	extern lv_img_dsc_t plus_5;
	extern lv_img_dsc_t plus_6;
	extern lv_img_dsc_t plus_7;
	extern lv_img_dsc_t plus_8;
	extern lv_img_dsc_t plus_9;
	extern lv_img_dsc_t plus_10;
	extern lv_img_dsc_t plus_11;
	extern lv_img_dsc_t plus_12;
	extern lv_img_dsc_t plus_13;
	extern lv_img_dsc_t plus_14;
	extern lv_img_dsc_t plus_15;
	extern lv_img_dsc_t plus_16;
	extern lv_img_dsc_t plus_17;
	extern lv_img_dsc_t plus_18;
	extern lv_img_dsc_t plus_19;
	extern lv_img_dsc_t plus_20;
	extern lv_img_dsc_t plus_21;
	extern lv_img_dsc_t plus_22;
	extern lv_img_dsc_t plus_23;
	extern lv_img_dsc_t plus_24;
	extern lv_img_dsc_t plus_25;
	extern lv_img_dsc_t plus_26;
	extern lv_img_dsc_t plus_27;
	extern lv_img_dsc_t plus_28;
	extern lv_img_dsc_t plus_29;
	extern lv_img_dsc_t plus_30;


	extern lv_img_dsc_t tree_0;
extern lv_img_dsc_t tree_1;
extern lv_img_dsc_t tree_2;
extern lv_img_dsc_t tree_3;
extern lv_img_dsc_t tree_4;
extern lv_img_dsc_t tree_5;
extern lv_img_dsc_t tree_6;
extern lv_img_dsc_t tree_7;
extern lv_img_dsc_t tree_8;
extern lv_img_dsc_t tree_9;
extern lv_img_dsc_t tree_10;
extern lv_img_dsc_t tree_11;
extern lv_img_dsc_t tree_12;
extern lv_img_dsc_t tree_13;
extern lv_img_dsc_t tree_14;
extern lv_img_dsc_t tree_15;
extern lv_img_dsc_t tree_16;
extern lv_img_dsc_t tree_17;
extern lv_img_dsc_t tree_18;
extern lv_img_dsc_t tree_19;
extern lv_img_dsc_t tree_20;
extern lv_img_dsc_t tree_21;
extern lv_img_dsc_t tree_22;
extern lv_img_dsc_t tree_23;
extern lv_img_dsc_t tree_24;
extern lv_img_dsc_t tree_25;
extern lv_img_dsc_t tree_26;
extern lv_img_dsc_t tree_27;
extern lv_img_dsc_t tree_28;
extern lv_img_dsc_t tree_29;
extern lv_img_dsc_t tree_30;

	extern lv_img_dsc_t weather_0;
	extern lv_img_dsc_t weather_9;
	extern lv_img_dsc_t weather_14;
	extern lv_img_dsc_t weather_5;
	extern lv_img_dsc_t weather_25;
	extern lv_img_dsc_t weather_30;
	extern lv_img_dsc_t weather_26;
	extern lv_img_dsc_t weather_11;
	extern lv_img_dsc_t weather_23;


	extern lv_img_dsc_t man_0;
	extern lv_img_dsc_t man_1;
	extern lv_img_dsc_t man_2;
	extern lv_img_dsc_t man_3;
	extern lv_img_dsc_t man_4;
	extern lv_img_dsc_t man_5;
	extern lv_img_dsc_t man_6;
	extern lv_img_dsc_t man_7;
	extern lv_img_dsc_t man_8;
	extern lv_img_dsc_t man_9;
	extern lv_img_dsc_t temp;
	extern lv_img_dsc_t humi;
}

namespace Page
{

	class WeatherView
	{
	public:
		void Create(lv_obj_t* root);
		void Delete();

	public:
		struct
		{
			lv_group_t* group;

			lv_style_t style_bg;
			lv_style_t style_indic;
			lv_style_t default_style;
			lv_style_t chFont_style;
			lv_style_t numberSmall_style;
			lv_style_t numberBig_style;
			lv_style_t btn_style;
			lv_style_t bar_style;

			lv_obj_t* weatherImg;
			lv_obj_t* cityLabel;
			lv_obj_t* btn;
			lv_obj_t* airLabel;
			lv_obj_t* weatherLabel;
			lv_obj_t* txtLabel;

			lv_obj_t* clockLabel_1;
			lv_obj_t* clockLabel_2;
			lv_obj_t* dateLabel;

			lv_obj_t* tempImg;
			lv_obj_t* tempBar;
			lv_obj_t* tempLabel;

			lv_obj_t* humiImg;
			lv_obj_t* humiBar;
			lv_obj_t* humiLabel;

			lv_obj_t* spaceImg;
			// lv_chart_series_t* ser1, * ser2;
			// lv_obj_t* chart, * titleLabel;

		} ui;

		void SetDailyWeather(
			const char* cityName,
			const int weatherLevel,
			const int airLevel,
			const int temperatue,
			const int huminature,
			const int minTemp,
			const int maxTemp,
			const int windDir,
			const int windLevel);

		void SetCityName();
		void SetAirLevel();
		void SetClockTime();
		void SetHumiTemp();

		void weather_obj_del(void);
		void weather_gui_del(void);
		void weather_group_add(lv_obj_t* root);
		void weather_style_init(void);
		void weather_gui_init(lv_obj_t* root);

		void SetCityName(const char* cityName);

		void SetWeather(const char* weather_pinyin);

		void SetWeather(const int weatherCode);
		void SetAirLevel(const int airLevel);

		void SetTemperatue(const int temperatue);

		void SetHuminature(const int huminature);

		void SetTextInfo(const int minTemp, const int maxTemp, const char* windDir, const int windLevel);

		void SetClockDay(const int month, const int day);

		void SetClockHour(const int hour, const int min);

		void SetClockSec(const int sec);

		void* weaImage_map[9] = {
			&weather_0, &weather_9, &weather_14, &weather_5, &weather_25,
			&weather_30, &weather_26, &weather_11, &weather_23 };
		void* manImage_map[10] = {
			&man_0, &man_1, &man_2, &man_3, &man_4,
			&man_5, &man_6, &man_7, &man_8, &man_9 };

lv_img_dsc_t* loveImage_map[31] = {
&love_0,
&love_1,
&love_2,
&love_3,
&love_4,
&love_5,
&love_6,
&love_7,
&love_8,
&love_9,
&love_10,
&love_11,
&love_12,
&love_13,
&love_14,
&love_15,
&love_16,
&love_17,
&love_18,
&love_19,
&love_20,
&love_21,
&love_22,
&love_23,
&love_24,
&love_25,
&love_26,
&love_27,
&love_28,
&love_29,
&love_30,
};

		lv_img_dsc_t* plusImage_map[31] = {
			&plus_0,
			&plus_1,
			&plus_2,
			&plus_3,
			&plus_4,
			&plus_5,
			&plus_6,
			&plus_7,
			&plus_8,
			&plus_9,
			&plus_10,
			&plus_11,
			&plus_12,
			&plus_13,
			&plus_14,
			&plus_15,
			&plus_16,
			&plus_17,
			&plus_18,
			&plus_19,
			&plus_20,
			&plus_21,
			&plus_22,
			&plus_23,
			&plus_24,
			&plus_25,
			&plus_26,
			&plus_27,
			&plus_28,
			&plus_29,
			&plus_30,
		};

		lv_img_dsc_t* treeImage_map[31] = {
			&tree_0,
			&tree_1,
			&tree_2,
			&tree_3,
			&tree_4,
			&tree_5,
			&tree_6,
			&tree_7,
			&tree_8,
			&tree_9,
			&tree_10,
			&tree_11,
			&tree_12,
			&tree_13,
			&tree_14,
			&tree_15,
			&tree_16,
			&tree_17,
			&tree_18,
			&tree_19,
			&tree_20,
			&tree_21,
			&tree_22,
			&tree_23,
			&tree_24,
			&tree_25,
			&tree_26,
			&tree_27,
			&tree_28,
			&tree_29,
			&tree_30,
		};
	};
}
#endif // !__VIEW_H
