#pragma once
#include <Arduino.h>

enum Buttons_Setting
{
    BUTTONS_USER = 0,                         /* GPIO используется для загрузки, но после прохождения начального кода
                                                 бутлоадера может быть назначена под свои задачи*/
    BUTTONS_USER_ACTIVE_STATE = 0,            // состояние, считающееся нажатием
    BUTTONS_USER_SHORT_LONG_HYSTERESIS = 500, // миллисекунды, время разделения долгого нажатия от короткого
};

int _user_button_time = 0;
bool buttons_initialized = false;

void Buttons_Setup()
{
    pinMode(BUTTONS_USER, INPUT);
}

void Buttons_Quant()
{
    if (buttons_initialized)
    {
        return;
    }
    /*

    TODO: Автомат считывания долгого и короткого нажатия
    digitalRead(BUTTONS_USER) == BUTTONS_USER_ACTIVE_STATE;
    
    */
}

bool Buttons_User_Short()
{
    // заглушка
    return false;
}

bool Buttons_User_Long()
{
    // заглушка
    return false;
}