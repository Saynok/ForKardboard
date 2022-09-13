#pragma once

#include "Arduino.h"
#include <WiFiUdp.h>

enum NTP_Settings
{
    NTP_SEVENZYYEARS = 2208988800UL,
    NTP_PACKET_SIZE = 48,
    NTP_DEFAULT_LOCAL_PORT = 1337,
    NTP_TIMEOUT = 1000,
    NTP_TIMEZONE = 3, // +3, Москва
};
const char *NTP_poolServerName = "pool.ntp.org";

WiFiUDP NTP_udp;
byte NTP_packetBuffer[NTP_PACKET_SIZE];
unsigned long NTP_lastUpdate = 0;  
unsigned long NTP_currentEpoc = 0; 
long NTP_timeOffset;

void NTP_Connect()
{
    NTP_timeOffset = NTP_TIMEZONE * 60 * 60;
    NTP_udp.begin(NTP_DEFAULT_LOCAL_PORT);
}

bool NTP_UpdateTime()
{
    while (NTP_udp.parsePacket() != 0)
        NTP_udp.flush();
    memset(NTP_packetBuffer, 0, NTP_PACKET_SIZE);
    NTP_packetBuffer[0] = 0b11100011;
    NTP_packetBuffer[1] = 0;
    NTP_packetBuffer[2] = 6;
    NTP_packetBuffer[3] = 0xEC;
    NTP_packetBuffer[12] = 49;
    NTP_packetBuffer[13] = 0x4E;
    NTP_packetBuffer[14] = 49;
    NTP_packetBuffer[15] = 52;

    NTP_udp.beginPacket(NTP_poolServerName, 123);
    NTP_udp.write(NTP_packetBuffer, NTP_PACKET_SIZE);
    NTP_udp.endPacket();

    long timeout = millis();
    while (NTP_udp.parsePacket() == 0)
    {
        if (millis() - timeout > NTP_TIMEOUT)
        {
            return false;
        }
        delay(10);
    }

    NTP_lastUpdate = millis() - (10 * (millis() - timeout + 1));
    NTP_udp.read(NTP_packetBuffer, NTP_PACKET_SIZE);

    unsigned long highWord = word(NTP_packetBuffer[40], NTP_packetBuffer[41]);
    unsigned long lowWord = word(NTP_packetBuffer[42], NTP_packetBuffer[43]);
    unsigned long secsSince1900 = highWord << 16 | lowWord;

    NTP_currentEpoc = secsSince1900 - NTP_SEVENZYYEARS;
    return true;
}

void NTP_Print_Time()
{
    unsigned long rawTime = NTP_timeOffset +
                            NTP_currentEpoc +
                            ((millis() - NTP_lastUpdate) / 1000);

    unsigned long hours = (rawTime % 86400L) / 3600;
    unsigned long minutes = (rawTime % 3600) / 60;
    unsigned long seconds = rawTime % 60;

    Serial.println((hours < 10 ? "0" + String(hours) : String(hours)) 
    + ":" + (minutes < 10 ? "0" + String(minutes) : String(minutes))
    + ":" + (seconds < 10 ? "0" + String(seconds) : String(seconds)));
}