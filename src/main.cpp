#include <Arduino.h>
#include "led.hpp"
#include "buttons.hpp"
#include "wifi.hpp"

// первое число в строке - время горения в миллисекундах, второе - время отключенного состояния светодиода
// ТЗ: "встроенный светодиод мигает 3 раза 20мс с интервалом 300мс, 2 раза 500/500 и далее по кругу"
int led_our_mode[] =
    {20, 300,
     20, 300,
     20, 300,
     500, 500,
     500, 500};

void setup()
{
  Serial.begin(9600);

  Buttons_Setup();

  LED_Setup();
  LED_Set_blink_mode(led_our_mode);

  WIFI_Setup();
  WIFI_Start_time_from_server();
}

void loop()
{
  LED_Quant();
  Buttons_Quant();
  WIFI_Time_Quant();

  // здесь стартует бизнес логика

  // ТЗ: кнопка встроенная реализовать короткое и длительное нажатие с выводом в порт - "short" и "long"
  if (Buttons_User_Short())
    Serial.println("Short");

  if (Buttons_User_Long())
    Serial.println("Long");

  // ТЗ: "подключиться по wifi, получить время, выводить его в консоль раз в 3 сек"
  if (WIFI_Time_Updated())
    WIFI_Print_current_time();
}
