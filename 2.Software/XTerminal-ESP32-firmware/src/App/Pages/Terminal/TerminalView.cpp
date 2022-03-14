#include "TerminalView.h"
#include "HAL/HAL.h"

using namespace Page;

void TerminalView::SetTermText(std::string termText)
{
	lv_label_set_text(
		ui.termTextLabel,
		termText.c_str()
	);
}

void TerminalView::Create(lv_obj_t* root)
{

	lv_obj_remove_style_all(root);
	lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);

	// lv_style_t* style2;
	// lv_style_init(style2);
	// lv_style_t style2;
	// lv_style_set_text_font(&style2, &lv_font_simsun_16_cjk);
	
#if 1
	ui.termTextLabel = lv_label_create(root);
	 lv_obj_set_size(ui.termTextLabel, LV_HOR_RES, LV_VER_RES);
	 lv_label_set_long_mode(ui.termTextLabel, LV_LABEL_LONG_WRAP);
	 // lv_label_set_recolor(ui.termTextLabel, true);
	 // lv_obj_add_style(ui.termTextLabel, &style2, 0);
	 lv_obj_set_style_text_font(ui.termTextLabel, &lv_font_montserrat_10, 0);
	 // lv_label_set_text_static(ui.termTextLabel, HAL::globalTermText.c_str());
	 // lv_obj_set_style_text_font(ui.termTextLabel, Resource.GetFont("msDengL_10"), 0);
	 // lv_obj_set_style_text_font(ui.termTextLabel, &lv_font_simsun_16_cjk, 0);

	 lv_obj_set_style_text_color(ui.termTextLabel, lv_color_white(), 0);
	 // lv_label_set_text(ui.termTextLabel, "一二三");
	 // lv_label_ins_text(ui.termTextLabel,LV_LABEL_POS_LAST, "2一二三");
	 
	 // lv_obj_align(ui.termTextLabel, LV_ALIGN_TOP_MID, 0, 120);
	 // lv_obj_set_pos(ui.termTextLabel, 5, 15);

#else
	 ui.termTextLabel = lv_label_create(root);
	 lv_obj_t* ltr_label = lv_label_create(root);
	 lv_label_set_text(ltr_label, "In modern terminology, a microcontroller is similar to a system on a chip (SoC).");
	 lv_obj_set_style_text_font(ltr_label, &lv_font_montserrat_16, 0);
	 lv_obj_set_width(ltr_label, 310);
	 lv_obj_align(ltr_label, LV_ALIGN_TOP_LEFT, 5, 5);

	 lv_obj_t* rtl_label = lv_label_create(root);
	 lv_label_set_text(rtl_label, "מעבד, או בשמו המלא יחידת עיבוד מרכזית (באנגלית: CPU - Central Processing Unit).");
	 lv_obj_set_style_base_dir(rtl_label, LV_BASE_DIR_RTL, 0);
	 lv_obj_set_style_text_font(rtl_label, &lv_font_dejavu_16_persian_hebrew, 0);
	 lv_obj_set_width(rtl_label, 310);
	 lv_obj_align(rtl_label, LV_ALIGN_LEFT_MID, 5, 0);

	 lv_obj_t* cz_label = lv_label_create(root);
	 lv_label_set_text(cz_label, "嵌入式系统（Embedded System），\n是一种嵌入机械或电气系统内部、具有专一功能和实时计算性能的计算机系统。");
	 lv_obj_set_style_text_font(cz_label, &lv_font_simsun_16_cjk, 0);
	 lv_obj_set_width(cz_label, 310);
	 lv_obj_align(cz_label, LV_ALIGN_BOTTOM_LEFT, 5, -5);
#endif

	ui.group = lv_group_create();
	// lv_group_add_obj(ui.group, root);
	lv_group_add_obj(ui.group, ui.termTextLabel);
}