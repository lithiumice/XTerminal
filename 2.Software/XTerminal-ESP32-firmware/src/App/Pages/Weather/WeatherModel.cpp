#include "WeatherModel.h"

#include "Weather.h"
#include "App/Accounts/Account_Master.h"
using namespace Page;

//static int onEvent(Account* account, Account::EventParam_t* param)
//{
//    auto instance = (WeatherModel*)(account->UserData);
//
//    if(param->event==Account::EVENT_PUB_PUBLISH)
//    {
//        instance->data_reved_flag = 1;
//        memcpy(&instance->info, param->data_p, sizeof(HAL::Weather_Info_t));
//    }
//    return 0;
//}

void WeatherModel::Init()
{
    account = new Account(
        "WeatherModel",
        AccountSystem::Broker(), 
        0, 
        this
    );
//    account->SetEventCallback(onEvent);
    account->Subscribe("Weather");

    GetWeatherInfo();
}

void WeatherModel::DeInit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}

void Page::WeatherModel::GetWeatherInfo()
{
    account->Pull("Weather", &info, sizeof(HAL::Weather_Info_t));
    data_reved_flag = 1;
}

void Page::WeatherModel::GetWeatherInfo(HAL::Weather_Info_t* info)
{
    account->Pull("Weather", info, sizeof(HAL::Weather_Info_t));
    data_reved_flag = 1;
}
