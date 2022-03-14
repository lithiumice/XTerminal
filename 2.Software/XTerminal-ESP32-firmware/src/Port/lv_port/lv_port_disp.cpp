#include "Port/Display.h"
#include "App/Configs/Config.h"
#define USE_STATIC_DISP_BUF 0

#if USE_STATIC_DISP_BUF
static lv_color_t lv_full_disp_buf[DISP_BUF_SIZE];
#else
lv_color_t *lv_disp_buf_p;
#endif

static lv_disp_draw_buf_t disp_buf;
static lv_disp_drv_t disp_drv;

void lhl_print(const char *buf)
{
  Serial.println(buf);
}

/**
 * @brief  屏幕刷新回调函数
 * @param  disp:屏幕驱动地址
 * @param  area:刷新区域
 * @param  color_p:刷新缓冲区地址
 * @retval 无
 */
static void disp_flush_cb(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  SCREEN_CLASS *screen = (SCREEN_CLASS *)disp->user_data;
  // area->y1 += 40;
  // area->y2 += 40;

  int32_t w = (area->x2 - area->x1 + 1);
  int32_t h = (area->y2 - area->y1 + 1);

  screen->startWrite();

#ifdef DEVICE0
#if DISP_ROTATE == 0
  screen->setAddrWindow(area->x1, area->y1 + 20, w, h);
#elif DISP_ROTATE == 1
  screen->setAddrWindow(area->x1 + 20, area->y1, w, h);
#endif
#else
  screen->setAddrWindow(area->x1, area->y1, w, h);
#endif

  screen->pushColors((uint16_t *)(&color_p->full), w * h, true);
  screen->endWrite();

  lv_disp_flush_ready(disp);
}

static void disp_wait_cb(lv_disp_drv_t *disp_drv)
{
  //    __wfi();
}

/**
 * @brief  屏幕初始化
 * @param  无
 * @retval 无
 */
void lv_port_disp_init(SCREEN_CLASS *scr)
{
  lv_log_register_print_cb(lhl_print);
  // lv_log_register_print_cb(//        reinterpret_cast<lv_log_print_g_cb_t>(my_print));

#if USE_STATIC_DISP_BUF
  lv_disp_draw_buf_init(&disp_buf, lv_full_disp_buf, nullptr, DISP_BUF_SIZE);
#else
  lv_disp_draw_buf_init(&disp_buf, lv_disp_buf_p, nullptr, DISP_BUF_SIZE);
#endif

  /*Initialize the display*/
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = DISP_HOR_RES;
  disp_drv.ver_res = DISP_VER_RES;
  disp_drv.flush_cb = disp_flush_cb;
  disp_drv.wait_cb = disp_wait_cb;
  disp_drv.draw_buf = &disp_buf;

  disp_drv.user_data = scr;
  lv_disp_drv_register(&disp_drv);
}
