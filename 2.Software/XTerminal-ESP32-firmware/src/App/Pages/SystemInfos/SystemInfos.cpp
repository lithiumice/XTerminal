#include "SystemInfos.h"
#include "App/Configs/Version.h"
#include "HAL/HAL.h"

using namespace Page;

SystemInfos::SystemInfos()
{
}

SystemInfos::~SystemInfos()
{

}

void SystemInfos::onCustomAttrConfig()
{

}

void SystemInfos::onViewLoad()
{
	Model.Init();
	View.Create(root);
	AttachEvent(root);
	AttachEvent(View.ui.wifi.icon);
	AttachEvent(View.ui.system.icon);
	// AttachEvent(View.ui.imu.icon);
	AttachEvent(View.ui.battery.icon);
	AttachEvent(View.ui.storage.icon);
}

void SystemInfos::onViewDidLoad()
{

}

void SystemInfos::onViewWillAppear()
{
	lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), View.ui.group);
	StatusBar::SetStyle(StatusBar::STYLE_TRANSP);

	timer = lv_timer_create(onTimerUpdate, 100, this);
	lv_timer_ready(timer);

	View.SetScrollToY(root, -LV_VER_RES, LV_ANIM_OFF);
	lv_obj_fade_in(root, 300, 0);

	lv_group_focus_obj(View.ui.system.icon);
}

void SystemInfos::onViewDidAppear()
{
	View.onFocus(View.ui.group);
}

void SystemInfos::onViewWillDisappear()
{
	lv_obj_fade_out(root, 300, 0);
}

void SystemInfos::onViewDidDisappear()
{
	lv_timer_del(timer);
}

void SystemInfos::onViewDidUnload()
{
	View.Delete();
	Model.Deinit();
}

void SystemInfos::AttachEvent(lv_obj_t* obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void SystemInfos::Update()
{
	char buf[128];
	/* WIFI */
	View.SetWifiInfo(
		HAL::config.host_name.c_str(),
        HAL::config.wifi_name.c_str(),
        HAL::config.wifi_pwd.c_str(),
		HAL::wifi_isconnected()
	);

	/* IMU */
	// Model.GetIMUInfo(buf, sizeof(buf));
	// snprintf(
    //     buf,
    //     sizeof(buf),
    //     "%.3f\n%.3f\n%.3f\n%.3f\n%.3f\n%.3f\n%.3f\n%.3f\n%.3f",
    //     imuInfo.ax,
    //     imuInfo.ay,
    //     imuInfo.az,
    //     imuInfo.gx,
    //     imuInfo.gy,
    //     imuInfo.gz,
    //     imuInfo.pitch,
    //     imuInfo.roll,
    //     imuInfo.yaw
    // );
	// View.SetIMU(buf);

	/* Power */
	int usage;
	float voltage;
	Model.GetBatteryInfo(&usage, &voltage, buf, sizeof(buf));
	View.SetBattery(usage, voltage, buf);

	/* Storage */
	bool detect;
	int used_heap;
	int total_heap;
	int used_heap_percent;
	int used_spiram;
#ifdef ARDUINO
	used_heap=ESP.getFreeHeap();
	total_heap=ESP.getHeapSize();
    // total_heap=320*1024;
	used_heap_percent = (total_heap-used_heap) * 100 / total_heap;
	used_spiram=heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
#else
	used_heap = 0;
	total_heap = 0;
	used_heap_percent = 0;
	used_spiram = 0;
#endif
	Model.GetStorageInfo(&detect, buf, sizeof(buf));
	View.SetStorage(
		detect ? "YES" : "NO",
		buf,
		VERSION_FILESYSTEM,
		used_heap,
		used_heap_percent
	);

	/* System */
	View.SetSystem(
		VERSION_FIRMWARE_NAME " " VERSION_SOFTWARE,
		VERSION_AUTHOR_NAME,
		VERSION_LVGL,
		VERSION_SOFTWARE,
		VERSION_COMPILER,
		VERSION_BUILD_TIME
	);
}

void SystemInfos::onTimerUpdate(lv_timer_t* timer)
{
	SystemInfos* instance = (SystemInfos*)timer->user_data;

	instance->Update();
}

void SystemInfos::onEvent(lv_event_t* event)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	auto* instance = (SystemInfos*)lv_obj_get_user_data(obj);

	if (code == LV_EVENT_RELEASED)
	{
		instance->Manager->Pop();
	}
	else if (code == LV_EVENT_LONG_PRESSED)
	{
		instance->Manager->Pop();
	}
}
