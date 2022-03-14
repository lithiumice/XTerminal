#include <HAL/HAL.h>
#include "App/App.h"
#include "lvgl_port.h"
// #include "Accounts/Account_Master.h"
// #include "Utils/AccountSystem/Account.h"

bool HAL::BluetoothConnected()
{
    return 1;
}
// Account* actEncoder;

int main()
{
    lv_init();
    // actEncoder = new Account("Encoder", AccountSystem::Broker(), sizeof(int16_t), nullptr);

    if (!lv_win32_init(
        GetModuleHandleW(NULL),
        SW_SHOW,
        280,
        240,
        LoadIconW(GetModuleHandleW(NULL),
        MAKEINTRESOURCE(IDI_LVGL))))
    {
        return -1;
    }

    lv_win32_add_all_input_devices_to_group(NULL);

    lv_win32_filesystem_driver_initialize();
    
    // lv_fs_dir_t d;
    // if (lv_fs_dir_open(&d, "/") == LV_FS_RES_OK)
    // {
    //     char b[MAX_PATH];
    //     memset(b, 0, MAX_PATH);
    //     while (lv_fs_dir_read(&d, b) == LV_FS_RES_OK)
    //     {
    //         printf("%s\n", b);
    //     }
    //
    //     lv_fs_dir_close(&d);
    // }

    // lv_demo_widgets();           // ok

    HAL::Init();
    App_Init();
    
    while (!lv_win32_quit_signal)
    {
        // lv_task_handler();
        // Sleep(1);
        // HAL::Update();
        // delay(20);

        lv_timer_handler();
        HAL::Update();
        Sleep(20);
    }

    return 0;
}
