// #include "MusicPlayerView.h"

// using namespace Page;


// void MusicPlayerView::Create(lv_obj_t *root)
// {
// 	// lv_obj_remove_style_all(root);
// 	// lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
// 	// lv_obj_set_style_bg_color(root, lv_color_black(), 0);
// 	// lv_obj_set_style_bg_opa(root, LV_OPA_COVER, 0);

// 	lv_obj_remove_style_all(root);

// 	lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
// 	StatusBar::SetStyle(StatusBar::STYLE_BLACK);
// 	lv_obj_set_style_bg_color(root, lv_color_black(), 0);

// 	// Style_Init();
// 	Group_Init();


// 	lv_obj_t* list= lv_list_create(root);
// 	lv_obj_set_size(list, LV_HOR_RES, LV_VER_RES - 22);
// 	lv_obj_align(list, LV_ALIGN_CENTER, 0, 22);
// 	lv_obj_set_style_radius(list, 0, 0);
// 	lv_obj_set_style_bg_color(list, lv_color_black(), 0);
// 	lv_obj_set_style_border_width(list, 0, 0);
// 	ui.file_list = list;

// }

// void MusicPlayerView::Group_Init()
// {
// 	ui.group = lv_group_create();
// 	lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), ui.group);
// }
// //
// // void MusicPlayerView::Delete()
// // {
// // 	lv_group_del(ui.group);
// // 	Style_Reset();
// // }

// // void MusicPlayerView::Style_Init()
// // {
// // 	lv_style_init(&style.icon);
// // 	lv_style_set_width(&style.icon, 220);
// // 	lv_style_set_bg_color(&style.icon, lv_color_black());
// // 	lv_style_set_bg_opa(&style.icon, LV_OPA_COVER);
// // 	lv_style_set_text_font(&style.icon, Resource.GetFont("bahnschrift_17"));
// // 	lv_style_set_text_color(&style.icon, lv_color_white());
// //
// // 	lv_style_init(&style.focus);
// // 	lv_style_set_width(&style.focus, 105);
// // 	lv_style_set_border_side(&style.focus, LV_BORDER_SIDE_RIGHT);
// // 	lv_style_set_border_width(&style.focus, 2);
// // 	lv_style_set_border_color(&style.focus, lv_color_hex(0xff0000));
// //
// // 	static const lv_style_prop_t style_prop[] =
// // 		{
// // 			LV_STYLE_WIDTH,
// // 			LV_STYLE_PROP_INV};
// //
// // 	static lv_style_transition_dsc_t trans;
// // 	lv_style_transition_dsc_init(
// // 		&trans,
// // 		style_prop,
// // 		lv_anim_path_overshoot,
// // 		200,
// // 		0,
// // 		nullptr);
// // 	lv_style_set_transition(&style.focus, &trans);
// // 	lv_style_set_transition(&style.icon, &trans);
// //
// // 	lv_style_init(&style.info);
// // 	lv_style_set_text_font(&style.info, Resource.GetFont("bahnschrift_13"));
// // 	lv_style_set_text_color(&style.info, lv_color_hex(0x999999));
// //
// // 	lv_style_init(&style.data);
// // 	lv_style_set_text_font(&style.data, Resource.GetFont("bahnschrift_13"));
// // 	lv_style_set_text_color(&style.data, lv_color_white());
// // }
// //
// // void MusicPlayerView::Style_Reset()
// // {
// // 	lv_style_reset(&style.icon);
// // 	lv_style_reset(&style.info);
// // 	lv_style_reset(&style.data);
// // 	lv_style_reset(&style.focus);
// // }
