#include <Arduino.h>
#include "led.hpp"
#include "buttons.hpp"
#include "wifi.hpp"
#include "NTP.hpp"
#include "tools.hpp"

// первое число в строке - время горения в миллисекундах, второе - время отключенного состояния светодиода
// ТЗ: "встроенный светодиод мигает 3 раза 20мс с интервалом 300мс, 2 раза 500/500 и далее по кругу"
unsigned int LED_OUR_MODE[] =
    {20, 300,
     20, 300,
     20, 300,
     500, 500,
     500, 500};

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\nПоследовательный терминал инициализирован");

  Buttons_Setup();

  LED_Setup();
  LED_Set_blink_mode(LED_OUR_MODE);

  WIFI_Start();
  NTP_Connect();

  Serial.println("Настройка завершена, приступаю к выполнению бизнес-логики");
}

Time ntp_time;
void loop()
{
  LED_Quant();
  // здесь стартует бизнес логика

  // ТЗ: кнопка встроенная реализовать короткое и длительное нажатие с выводом в порт - "short" и "long"
  if (Buttons_User_Short())
  {
    Serial.println("short");
  }

  if (Buttons_User_Long())
  {
    Serial.println("long");
  }

  // ТЗ: "подключиться по wifi, получить время, выводить его в консоль раз в 3 сек"
  if (ntp_time.Estimated(3000) && NTP_UpdateTime())
  {
    NTP_Print_Time();
  }
}
