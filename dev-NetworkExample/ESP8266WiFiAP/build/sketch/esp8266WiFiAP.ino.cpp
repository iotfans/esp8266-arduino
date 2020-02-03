#include <Arduino.h>
#line 1 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiAP\\esp8266WiFiAP.ino"
#include <ESP8266WiFi.h>

/* 修改为喜欢的接入点与密码 */
#define AP_SSID "my_esp8266_ap"
#define AP_PSW "qianrushi"

uint8_t macAddr[6];

IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);

#line 13 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiAP\\esp8266WiFiAP.ino"
void setup();
#line 47 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiAP\\esp8266WiFiAP.ino"
void loop();
#line 13 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiAP\\esp8266WiFiAP.ino"
void setup()
{
    Serial.begin(115200);
    /* 为了演示效果 */
    delay(2000);

    Serial.print("Setting Soft-AP Configuration ... ");

    /* 配置WiFi的工作模式为Soft-AP */
    WiFi.mode(WIFI_AP);
    /* 配置AP的IP、网关和子网掩码 */
    Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

    /* 启动AP工作模式，并设置账号和密码 */
    Serial.print("Setting Soft-AP Config ... ");
    boolean result = WiFi.softAP(AP_SSID, AP_PSW);
    if (result)
    {
        Serial.println("Ready");
        /* 输出Soft-AP的IP地址 */
        Serial.println(String("Soft-AP's IP Address =") + WiFi.softAPIP().toString());
        /* 输出Soft-AP的mac地址 */
        Serial.println(String("MAC Address = ") + WiFi.softAPmacAddress().c_str());
        /* 输出另一个格式的mac地址 */
        WiFi.softAPmacAddress(macAddr);
        Serial.printf("MAC address = %02x:%02x:%02x:%02x:%02x:%02x\n", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
    }
    else
    {
        Serial.println("Failed!!!");
    }
    Serial.println("End Setup!");
}

void loop()
{
    Serial.println(String("Stations connected =") + WiFi.softAPgetStationNum());
    delay(3000);
}

