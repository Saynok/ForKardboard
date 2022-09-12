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

    wifi_connected = false;

    if (!wifi_connected)
    {
        Serial.println("ERROR\nНе получается подключиться к локальной WiFi сети, \nпроверьте пароль, логин и вообще включен ли маршрутизатор\n");
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
        Serial.println("\nERROR\nНет подключения к локальной WiFi сети\n");
        return false;
    }

    /*

    TODO:  Код подключения к серверу времени

    */

    time_server_connected = false;

    if (!time_server_connected)
    {
        Serial.println("\nERROR\nНевозможно подключиться к серверу, проверьте роутер или киньте денег провайдеру\n");
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
