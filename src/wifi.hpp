#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *WIFI_SSID = "Threedognight_Mk_4";
const char *WIFI_PASSWORD = "Refuel26";
bool wifi_connected = false;

bool WIFI_Start()
{
    if (wifi_connected)
        return true;

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    long timeout = millis();
    while (WiFi.status() == WL_DISCONNECTED)
    {
        if (millis() - timeout > 10 * 1000) // таймаут 10 секунд
        {
            return false;
        }
        delay(10);
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("ERROR\nНе получается подключиться к локальной WiFi сети, \nпроверьте пароль, логин и вообще включен ли маршрутизатор\n");
        Serial.print("Код ошибки: ");
        Serial.println(WiFi.status());
        return false;
    }
    wifi_connected = true;

    return wifi_connected;
}