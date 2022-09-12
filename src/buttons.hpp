#pragma once
#include <Arduino.h>

enum Buttons_Setting
{
    BUTTONS_USER = 0,                         /* GPIO используется для загрузки, но после прохождения начального кода
                                                 бутлоадера может быть назначена под свои задачи*/
    BUTTONS_USER_ACTIVE_STATE = 0,            // состояние, считающееся нажатием
    BUTTONS_USER_SHORT_LONG_HYSTERESIS = 500, // миллисекунды, время разделения долгого нажатия от короткого
    BUTTONS_BOUNCE_TIME = 50,                 // Время между считываниями кнопки
};

enum Buttons_Click_State
{
    BUTTONS_CLICK_STATE_RELEASE,
    BUTTONS_CLICK_STATE_LONG,
    BUTTONS_CLICK_STATE_SHORT,
};

int _buttons_click_state = BUTTONS_CLICK_STATE_RELEASE;
int _buttons_time = 0;
Ticker _buttons_ticker;

void Buttons_Ticker_Estimated()
{
    // if (_buttons_time > 0)
    // {
    //     Serial.print("buttons hold time\t");
    //     Serial.println(_buttons_time);
    // }
    if (digitalRead(BUTTONS_USER) == BUTTONS_USER_ACTIVE_STATE)
    {
        _buttons_time += BUTTONS_BOUNCE_TIME;
    }
    else if (_buttons_time > 0)
    {
        if (_buttons_time < BUTTONS_USER_SHORT_LONG_HYSTERESIS)
        {
            _buttons_click_state = BUTTONS_CLICK_STATE_SHORT;
        }
        else
        {
            _buttons_click_state = BUTTONS_CLICK_STATE_LONG;
        }
        _buttons_time = 0;
    }
}

void Buttons_Setup()
{
    pinMode(BUTTONS_USER, INPUT);
    _buttons_ticker.attach(BUTTONS_BOUNCE_TIME / 1000.0f, &Buttons_Ticker_Estimated);
}

bool Buttons_User_Short()
{
    if (_buttons_click_state == BUTTONS_CLICK_STATE_SHORT)
    {
        _buttons_click_state = BUTTONS_CLICK_STATE_RELEASE;
        return true;
    }
    return false;
}

bool Buttons_User_Long()
{
    if (_buttons_click_state == BUTTONS_CLICK_STATE_LONG)
    {
        _buttons_click_state = BUTTONS_CLICK_STATE_RELEASE;
        return true;
    }
    return false;
}