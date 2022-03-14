#include "StartupView.h"

using namespace Page;

#define COLOR_ORANGE lv_color_hex(0xff931e)
#define COLOR_RED lv_color_hex(0xff0000)

void StartupView::Create(lv_obj_t *root)
{
    lv_obj_remove_style_all(root);
    lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);

    lv_obj_t *cont = lv_obj_create(root);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 150, 40);
    lv_obj_set_style_border_color(cont, COLOR_RED, 0);
    lv_obj_set_style_border_side(cont, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_border_width(cont, 3, 0);
    lv_obj_set_style_border_post(cont, true, 0);
    lv_obj_center(cont);
    ui.cont = cont;

    lv_obj_t *label = lv_label_create(cont);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_label_set_text(label, "LithiumStudio");
    lv_obj_center(label);
    ui.labelLogo = label;

    label = lv_label_create(root);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_12, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_label_set_text(label, "Lithiumice 2022\nEdition for HLX");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 40);
    // lv_obj_align_to(label, cont, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    ui.labelLogo2 = label;

    ui.anim_timeline = lv_anim_timeline_create();

#define ANIM_DEF(start_time, obj, attr, start, end) \
    {start_time, obj, LV_ANIM_EXEC(attr), start, end, 500, lv_anim_path_ease_out, true}

    lv_anim_timeline_wrapper_t wrapper[] =
        {
            ANIM_DEF(0, ui.cont, width, 0, lv_obj_get_style_width(ui.cont, 0)),
            ANIM_DEF(500, ui.labelLogo, y, lv_obj_get_style_height(ui.cont, 0), lv_obj_get_y(ui.labelLogo)),
            // ANIM_DEF(600, ui.labelLogo2, width, 0, lv_obj_get_style_width(ui.cont, 0)),
            // ANIM_DEF(600, ui.labelLogo2, y, lv_obj_get_style_height(ui.cont, 0), lv_obj_get_y(ui.labelLogo2)),
            LV_ANIM_TIMELINE_WRAPPER_END};

    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);
}

void StartupView::Delete()
{
    // lv_group_set_focus_cb(lv_group_get_default(), nullptr);

    if (ui.anim_timeline)
    {
        lv_anim_timeline_del(ui.anim_timeline);
        ui.anim_timeline = nullptr;
    }
}
