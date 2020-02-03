/**
 * 功能描述：eeprom结构体操作
 */
#include <EEPROM.h>
#include <ESP8266WiFi.h>

#define DEFAULT_SSID "my_Wifi_1st"
#define DEFAULT_PSW "qianrushi"

typedef struct
{
    char ssid[32];
    char psw[32];
} config_t;

config_t config_for_save, config_for_read;

/**
 * @note 保存参数到EEPROM中
 * @param NONE
 */
void saveConfig()
{
    Serial.println("Saving Config...");
    Serial.print("stassid: ");
    Serial.println(config_for_save.ssid);
    Serial.print("stapwd: ");
    Serial.println(config_for_save.psw);


    EEPROM.begin(1024);
    uint8_t *point = (uint8 *)&config_for_save;
    for (int i = 0; i < sizeof(config_for_save); i++)
    {
        EEPROM.write(i, *(point + i));
    }
    EEPROM.commit();
}

/**
 * @note 从EEPROM中加载参数
 */
void loadConfig()
{
    EEPROM.begin(1024);
    uint8_t *p = (uint8_t *)&config_for_read;
    for (int i = 0; i < sizeof(config_for_read); i++)
    {
        *(p + i) = EEPROM.read(i);
    }
    EEPROM.commit();
    Serial.println("=====read myConfig======");
    Serial.print("stassid: ");
    Serial.println(config_for_read.ssid);
    Serial.print("stapwd: ");
    Serial.println(config_for_read.psw);
}

void setup()
{
    ESP.wdtEnable(5000);
    Serial.begin(115200);
    
    strcpy(config_for_save.ssid, DEFAULT_SSID);
    strcpy(config_for_save.psw, DEFAULT_PSW);
    saveConfig();
}

void loop()
{
    ESP.wdtFeed();
    loadConfig();
    delay(3000);
}
