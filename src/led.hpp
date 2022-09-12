#pragma once
#include <Arduino.h>

enum LED_Settings
{
    LED_PIN = LED_BUILTIN // используется встроенный на плату светодиод на пине GPIO2
};

/* первое число в строке - время горения в миллисекундах, второе - время отключенного состояния светодиода

Пример:
int _led_default_mode[] =
    {500, 500};
Результат: Поочередное мигание каждые 500мс

int _led_default_mode[] =
    {100, 900};
Результат: Коротко зажигается на 100 миллисекунд 1 раз в секунду (100мс + 900мс = 1000мс = период 1с).

int _led_default_mode[] =
    {500, 500,
     100, 900};
Результат: Длительное горение сменяется короткой вспышкой

*/
int _led_default_mode[] =
    {0, 0};

int *_led_current_mode = NULL;
bool led_initialized = false;

void LED_Set_blink_mode(int *mode)
{
    if (!led_initialized)
    {
        Serial.println("ERROR, Светодиоды не инициализированы!");
        return;
    }
    _led_current_mode = mode;
}
void LED_Setup()
{
    if (led_initialized)
    {
        return;
    }

    pinMode(LED_PIN, OUTPUT);
    LED_Set_blink_mode(_led_default_mode);
}

void LED_Quant()
{
    if (!led_initialized)
    {
        return;
    }

    /*

    TODO: Автомат переключения светодиодов в соответствии с режимом

    */
}