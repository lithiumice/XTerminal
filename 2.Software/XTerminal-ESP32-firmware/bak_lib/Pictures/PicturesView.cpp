#include "PicturesView.h"

using namespace Page;

void PicturesView::GuiInit(lv_obj_t* root)
{
}

// void PicturesView::ListAddItem(
//     lv_obj_t* list,
//     const char* icon,
//     const char* name
// )
// {
//     lv_obj_t* btn;
//     btn = lv_list_add_btn(list, icon, name);
//     lv_obj_set_style_text_font(btn, &lv_font_montserrat_18, 0);
//     lv_obj_set_style_text_color(btn, lv_color_white(), 0);
//     lv_group_add_obj(ui.group, btn);
// }
#define ListAddItem(icon,name) \
{\
    ui.name = lv_list_add_btn(ui.list1, icon, #name);\
    lv_obj_set_style_text_font(ui.name, &lv_font_montserrat_14, 0);\
    lv_obj_set_style_text_color(ui.name, lv_color_white(), 0);\
    lv_group_add_obj(ui.group, ui.name);\
    lv_obj_set_style_bg_color(ui.name, lv_color_black(), 0);\
}

// void PicturesView::ListAddText(
//     lv_obj_t* list,
//     const char* name
// )
// {
//     lv_obj_t* txt;
//     txt = lv_list_add_text(list, name);
//     lv_obj_set_style_text_font(txt, &lv_font_montserrat_14, 0);
//     lv_obj_set_style_text_color(txt, lv_color_white(), 0);
// }
#define ListAddText(name)\
{\
    lv_obj_t* name = lv_list_add_text(ui.list1, #name);\
    lv_obj_set_style_text_font(name, &lv_font_montserrat_12, 0);\
    lv_obj_set_style_text_color(name, lv_color_white(), 0);\
    lv_obj_set_style_bg_color(name, lv_color_black(), 0);\
}



void PicturesView::Create(lv_obj_t* root)
{
    lv_obj_remove_style_all(root);
    lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
    StatusBar::SetStyle(StatusBar::STYLE_BLACK);
    lv_obj_set_style_bg_color(root, lv_color_black(), 0);

    ui.group = lv_group_create();
    ui.list1 = lv_list_create(root);
    lv_obj_set_size(ui.list1, LV_HOR_RES, LV_VER_RES-22);
    lv_obj_align(ui.list1, LV_ALIGN_CENTER,0,22);
    lv_obj_set_style_radius(ui.list1, 0, 0);
    lv_obj_set_style_bg_color(ui.list1, lv_color_black(), 0);
    lv_obj_set_style_border_width(ui.list1, 0,0); 
    
#define SET_DEF(icon,className)\
		ListAddItem(icon, className);

#define SET_DEF2(className)\
		ListAddText(className);

#include "_Setting_DEF.inc"

#undef SET_DEF2
#undef SET_DEF
    // ListAddItem(LV_SYMBOL_FILE, New);
    // ListAddItem(LV_SYMBOL_SAVE, Save);
    // ListAddItem(LV_SYMBOL_EDIT, Edit);
    // ListAddItem(LV_SYMBOL_BLUETOOTH, Bluetooth);
    // ListAddItem(LV_SYMBOL_GPS, Navigation);
    // ui.btn = lv_list_add_btn(ui.list1, LV_SYMBOL_SAVE, "UpdateInter");
    // lv_obj_set_style_text_font(ui.btn, &lv_font_montserrat_16, 0);
    // lv_obj_set_style_text_color(ui.btn, lv_color_white(), 0);
    // lv_group_add_obj(ui.group, ui.btn);
    //
    // ui.spinbox = lv_spinbox_create(ui.btn);
    // lv_spinbox_set_range(ui.spinbox, 1, 10);
    // lv_spinbox_set_digit_format(ui.spinbox, 3, 1);
    // lv_spinbox_step_prev(ui.spinbox);
    // lv_obj_set_size(ui.spinbox, 50, 15);
    // lv_obj_set_width(ui.spinbox, 100);
    // lv_obj_align(ui.spinbox, LV_ALIGN_RIGHT_MID, 0, 0);
    // lv_group_add_obj(ui.group, ui.spinbox); \

    
    // lv_group_add_obj(ui.group, root);
    // lv_group_add_obj(ui.group, ui.list1);
}

void PicturesView::Delete()
{
	
}
