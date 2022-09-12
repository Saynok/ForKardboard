#pragma once
#include <Arduino.h>
#include <Ticker.h>

enum LED_Settings
{
    LED_PIN = LED_BUILTIN // используется встроенный на плату светодиод на пине GPIO2
};

/* первое число в строке - время горения в миллисекундах, второе - время отключенного состояния светодиода
Размер последовательности должен быть четным.

Пример:
int _LED_DEFAULT_MODE[] =
    {500, 500};
Результат: Поочередное мигание каждые 500мс

int _LED_DEFAULT_MODE[] =
    {100, 900};
Результат: Коротко зажигается на 100 миллисекунд 1 раз в секунду (100мс + 900мс = 1000мс = период 1с).

int _LED_DEFAULT_MODE[] =
    {500, 500,
     100, 900};
Результат: Длительное горение сменяется короткой вспышкой
*/
#define LED_Set_blink_mode(mode) _LED_Set_blink_mode(mode, sizeof(mode));

enum LED_FSM
{
    LED_STATE_NOT_INITIALIZED,
    LED_STATE_BUSY,
    LED_STATE_CHANGE,
};

unsigned int _LED_DEFAULT_MODE[] =
    {0, 0};

LED_FSM _led_state = LED_STATE_NOT_INITIALIZED;
unsigned int _current_timing = 0;
Ticker _ticker;
unsigned int *_led_current_mode = NULL;
unsigned int _led_current_mode_size = 0;

void _LED_Set_blink_mode(unsigned int *mode, unsigned int mode_size)
{
    if (_led_state == LED_STATE_NOT_INITIALIZED)
    {
        Serial.println("\nERROR\nСветодиоды не инициализированы!\n");
        return;
    }
    if (_led_current_mode == mode)
        return;
    _current_timing = 0;
    _led_current_mode = mode;
    _led_current_mode_size = mode_size / 4; // int занимает 4 байта
    digitalWrite(LED_PIN, 0);
}

void LED_Setup()
{
    if (_led_state != LED_STATE_NOT_INITIALIZED)
    {
        return;
    }
    pinMode(LED_PIN, OUTPUT);
    _led_state = LED_STATE_CHANGE;
    LED_Set_blink_mode(_LED_DEFAULT_MODE);
}

void LED_Ticker_Estimated()
{
    _led_state = LED_STATE_CHANGE;
}

void LED_Quant()
{
    switch (_led_state)
    {
    case LED_STATE_NOT_INITIALIZED:
    case LED_STATE_BUSY:
        break;

    case LED_STATE_CHANGE:
        if (_led_current_mode == NULL || _led_current_mode_size == 0)
            _led_state = LED_STATE_BUSY;

        if (_current_timing == _led_current_mode_size)
        {
            _current_timing = 0;
        }

        digitalWrite(LED_PIN, (_current_timing % 2) == 1);
        _ticker.attach(_led_current_mode[_current_timing] / 1000.0f, &LED_Ticker_Estimated);

        // Serial.print("time\t");
        // Serial.print(_led_current_mode[_current_timing] / 1000.0f);
        // Serial.print("\tstate\t");
        // Serial.print((_current_timing % 2) == 0);
        // Serial.print("\t_current_timing\t");
        // Serial.print(_current_timing);
        // Serial.print("\tsize of mode\t");
        // Serial.println(_led_current_mode_size);

        if (_current_timing < _led_current_mode_size)
        {
            _current_timing++;
        }

        _led_state = LED_STATE_BUSY;
        break;
    }
}