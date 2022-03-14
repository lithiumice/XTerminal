#pragma once

#define ListAddItem(icon, name)                                         \
	{                                                                   \
		ui.name = lv_list_add_btn(ui.list1, icon, #name);               \
		lv_obj_set_style_text_font(ui.name, &lv_font_montserrat_14, 0); \
		lv_obj_set_style_text_color(ui.name, lv_color_white(), 0);      \
		lv_group_add_obj(ui.group, ui.name);                            \
		lv_obj_set_style_bg_color(ui.name, lv_color_black(), 0);        \
	}
#define ListAddText(name)                                            \
	{                                                                \
		lv_obj_t *name = lv_list_add_text(ui.list1, #name);          \
		lv_obj_set_style_text_font(name, &lv_font_montserrat_12, 0); \
		lv_obj_set_style_text_color(name, lv_color_white(), 0);      \
		lv_obj_set_style_bg_color(name, lv_color_black(), 0);        \
	}
#define ListAddOption(icon, name)                                                                    \
	{                                                                                                \
		ListAddItem(icon, name);                                                                     \
		ui.name##_sw = lv_switch_create(ui.name);                                                          \
       lv_group_remove_obj(ui.name);\
		lv_group_add_obj(ui.group, ui.name##_sw);                                                    \
		lv_obj_set_height(ui.name##_sw, lv_pct(90));                                                 \
		lv_obj_align(ui.name##_sw, LV_ALIGN_RIGHT_MID, 0, 0);                                        \
		lv_obj_set_style_bg_color(ui.name##_sw, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR); \
		lv_obj_set_style_bg_color(ui.name##_sw, lv_palette_main(LV_PALETTE_GREY), 0);                \
		lv_obj_add_state(ui.name##_sw, LV_STATE_CHECKED);                                            \
	}

