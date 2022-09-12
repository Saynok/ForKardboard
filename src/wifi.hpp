#pragma once
#include <Arduino.h>

const char *WIFI_SSID = "Threedognight_Mk_4";
const char *WIFI_PASSWORD = "Refuel26";
const char *TIME_SERVER = "";
const int TIMEZONE = 3; // +3, Москва

bool wifi_connected = false;
bool time_server_connected = false;
bool time_server_updated = false;

bool WIFI_Setup()
{
    if (wifi_connected)
        return true;

    /*

    TODO: Код подключения к WIFI

    */

    wifi_connected = true;

    if (!wifi_connected)
    {
        Serial.println("Не получается подключиться к локальной WiFi сети, \nпроверьте пароль, логин и вообще включен ли маршрутизатор");
    }
    return wifi_connected;
}

bool WIFI_Start_time_from_server()
{
    if (time_server_connected)
    {
        return true;
    }

    if (!wifi_connected)
    {
        Serial.println("ERROR, Нет подключения к локальной WiFi сети");
        return false;
    }

    /*

    TODO:  Код подключения к серверу времени

    */

    time_server_connected = true;

    if (!time_server_connected)
    {
        Serial.println("Невозможно подключиться к серверу, проверьте роутер или киньте денег провайдеру");
        return false;
    }

    return time_server_connected;
}

void WIFI_Time_Quant()
{
    if (!wifi_connected || !time_server_connected)
    {
        return;
    }

    /*

    TODO: здесь будет крутиться автомат получения с сервера данных времени

    */
}

bool WIFI_Time_Updated()
{
    return time_server_updated;
}

void WIFI_Print_current_time()
{
    /*

    TODO: Код вывода времени

    */
}
