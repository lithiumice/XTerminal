#include "Arduino.h"
#include "HAL.h"

void HAL::wifi_init()
{
    WiFi.enableSTA(false);
    WiFi.enableAP(false);
    //    WiFi.setSleep(true);
    WiFi.setAutoReconnect(true);
}

bool HAL::wifi_isconnected()
{
    return WL_CONNECTED == WiFi.status();
}

void HAL::wifi_smartConfig()
{
    WiFi.mode(WIFI_MODE_STA);
    Serial.println("wifi_smartConfig:");
    WiFi.beginSmartConfig();
    while (1)
    {
        Serial.print(".");
        delay(500);
        if (WiFi.smartConfigDone())
        {
            Serial.println("配网成功");
            //   HAL::TerminalPrintln("SSID:%s"+WiFi.SSID().c_str());
            //   HAL::TerminalPrintln("PSW:%s"+ WiFi.psk().c_str());
            HAL::TerminalPrintln(WiFi.SSID().c_str());
            HAL::TerminalPrintln(WiFi.psk().c_str());
            break;
        }
    }
}

void HAL::wifi_search()
{
    Serial.println("scan start");
    int wifi_num = WiFi.scanNetworks();
    Serial.println("scan done");
    if (0 == wifi_num)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(wifi_num);
        Serial.println(" networks found");
        for (int cnt = 0; cnt < wifi_num; ++cnt)
        {
            Serial.print(cnt + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(cnt));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(cnt));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(cnt) == WIFI_AUTH_OPEN) ? " " : "*");
        }
    }
}

bool HAL::wifi_connect()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println(F("\nWiFi is OK.\n"));
        return false;
    }

    HAL::TerminalPrintln("Connecting: " + config.wifi_name + " @" + config.wifi_pwd);
    //设置为STA模式并连接WIFI
    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.enableSTA(true);
    WiFi.enableAP(true);
    WiFi.setHostname(config.host_name.c_str());
    WiFi.begin(config.wifi_name.c_str(), config.wifi_pwd.c_str());

    // Serial.println(F("\nWiFi connected"));
    // Serial.print(F("IP address: "));
    // Serial.println(WiFi.localIP());

    // if (!WiFi.config(local_ip, gateway, subnet, dns))
    // { //WiFi.config(ip, gateway, subnet, dns1, dns2);
    // 	Serial.println("WiFi STATION Failed to configure Correctly");
    // }
    // wifiMulti.addAP(AP_SSID, AP_PASS); // add Wi-Fi networks you want to connect to, it connects strongest to weakest
    // wifiMulti.addAP(AP_SSID1, AP_PASS1); // Adjust the values in the Network tab

    // Serial.println("Connecting ...");
    // while (wifiMulti.run() != WL_CONNECTED)
    // { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    // 	delay(250);
    // 	Serial.print('.');
    // }
    // Serial.println("\nConnected to " + WiFi.SSID() + " Use IP address: " + WiFi.localIP().toString()); // Report which SSID and IP is in use
    // // The logical name http://fileserver.local will also access the device if you have 'Bonjour' running or your system supports multicast dns
    // if (!MDNS.begin(SERVER_NAME))
    // { // Set your preferred server name, if you use "myserver" the address would be http://myserver.local/
    // 	Serial.println(F("Error setting up MDNS responder!"));
    // 	ESP.restart();
    // }

    return true;
}

bool HAL::wifi_close()
{
    WiFi.disconnect();
    WiFi.enableSTA(false);
    WiFi.enableAP(false);
    WiFi.mode(WIFI_MODE_NULL);
    // esp_wifi_set_inactive_time(ESP_IF_ETH, 10); //设置暂时休眠时间
    // esp_wifi_get_ant(wifi_ant_config_t * config);                   //获取暂时休眠时间
    // WiFi.setSleep(WIFI_PS_MIN_MODEM);
    // WiFi.onEvent();
    Serial.println(F("WiFi disconnect"));
    return true;
}

// bool HAL::wifi_open_ap()
//{
//     const char *ap_ssid=AP_SSID.c_str();
//     const char *ap_password=AP_PASS.c_str();
//
//     IPAddress local_ip(192, 168, 4, 2); // Set your server's fixed IP address here
// IPAddress gateway(192, 168, 4, 1);  // Set your network Gateway usually your Router base address
// IPAddress subnet(255, 255, 255, 0); // Set your network sub-network mask here
// IPAddress dns(192, 168, 4, 1);      // Set your network DNS usually your Router base address
//
//     WiFi.enableAP(true); //配置为AP模式
//     WiFi.setHostname(HOST_NAME.c_str());
//     // WiFi.begin();
//     bool result = WiFi.softAP(ap_ssid, ap_password); //开启WIFI热点
//     if (result)
//     {
//         WiFi.softAPConfig(local_ip, gateway, subnet);
//         IPAddress myIP = WiFi.softAPIP();
//
//         //打印相关信息
//         Serial.print(F("\nSoft-AP IP address = "));
//         Serial.println(myIP);
//         Serial.println(String("MAC address = ") + WiFi.softAPmacAddress().c_str());
//         Serial.println(F("waiting ..."));
////        ap_timeout = 300; // 开始计时
//        // xTimer_ap = xTimerCreate("ap time out", 1000 / portTICK_PERIOD_MS, pdTRUE, (void *)0, restCallback);
//        // xTimerStart(xTimer_ap, 0); //开启定时器
//    }
//    else
//    {
//        //开启热点失败
//        Serial.println(F("WiFiAP Failed"));
//        return false;
//        delay(1000);
//        ESP.restart(); //复位esp32
//    }
//    // 设置域名
//    if (MDNS.begin(HOST_NAME.c_str()))
//    {
//        Serial.println(F("MDNS responder started"));
//    }
//    return true;
//
//    //        WiFi.softAPdisconnect(true);
////        // ESP.restart();
//}
