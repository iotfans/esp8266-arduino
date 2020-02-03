#include <Arduino.h>
#line 1 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiScan\\ESP8266WiFiScan.ino"
#include <ESP8266WiFi.h>

//#define SYNC_SCAN_MODE 1      //同步扫描模式
//#define ASYNC_SCAN_MODE 1     //异步扫描模式1
#define ASYNC_SCAN_MODE 2       //异步扫描模式2

int scanPeriod = 5000;      //每隔5000ms扫描一次          
long lastMillis = 0;
long currentMillis = 0;

#if ASYNC_SCAN_MODE == 2
#line 12 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiScan\\ESP8266WiFiScan.ino"
void print_scan_result(int numOfNetworks);
#line 23 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiScan\\ESP8266WiFiScan.ino"
void setup();
#line 39 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiScan\\ESP8266WiFiScan.ino"
void loop();
#line 12 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiScan\\ESP8266WiFiScan.ino"
void print_scan_result(int numOfNetworks)
{
    Serial.printf("%d network(s) founded\r\n", numOfNetworks);
    for (size_t i = 0; i < numOfNetworks; i++)
    {
        Serial.printf("%d: %s, Channel:%d (%ddBm) %s\r\n", i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i) == ENC_TYPE_NONE ? "open" : "encrypted");
    }
    WiFi.scanDelete();
}
#endif

void setup()
{
    Serial.begin(115200);
    delay(5000);

    WiFi.mode(WIFI_STA);
    /* 先断开连接(避免奇怪的bug) */
    WiFi.disconnect();
    delay(100);
    Serial.println("Setup done.");
#if ASYNC_SCAN_MODE == 1
    /* 进入主循环前先获取当前millis */
    lastMillis = millis();
#endif
}

void loop()
{
#ifdef SYNC_SCAN_MODE
    Serial.println("Scan starts...");
    /* 同步扫描(必须等待返回结果) */
    int n = WiFi.scanNetworks();
    Serial.println("Scan progress done!");

    if (n == 0)
    {
        Serial.println("No WiFi AP founded!");
    }
    else
    {
        Serial.print(n);
        Serial.println(" WiFi AP founded!");
        for (int i = 0; i < n; i++)
        {
            Serial.print(i + 1);
            Serial.print(": ");
            //打印wifi账号
            Serial.print(WiFi.SSID(i));
            Serial.print(",");
            Serial.print(String("Ch:") + WiFi.channel(i));
            Serial.print(",");
            Serial.print(WiFi.isHidden(i) ? "hide" : "show");
            Serial.print(" (");
            //打印wifi信号强度
            Serial.print(WiFi.RSSI(i));
            Serial.print("dBm");
            Serial.print(")");
            //打印wifi加密方式
            Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "open" : "*");
            delay(10);
        }
    }
    Serial.println("");
    delay(5000);
#endif

#if ASYNC_SCAN_MODE == 1
    currentMillis = millis();

    if (currentMillis - lastMillis > scanPeriod)
    {
        lastMillis = currentMillis;
        /* 异步扫描模式1 */
        WiFi.scanNetworks(true);
        Serial.println("Scan starts...");
    }
    /* 判断异步扫描模式的状态 */
    /* 注意：scanComplete()会返回负值(-1：扫描未结束，-2：扫描未开始) */
    /* 因此 numOfNetworks 必须定义为有符号数int，不能定义为uint8_t */
    int numOfNetworks = WiFi.scanComplete();
    if (numOfNetworks >= 0)
    {
        Serial.printf("%d network(s) founded!\r\n", numOfNetworks);
        for (int i = 0; i < numOfNetworks; i++)
        {
            Serial.printf("%d: %s, Channel:%d (%ddBm) %s\r\n", i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i) == ENC_TYPE_NONE ? "(open)" : "(encrypted)");
        }
        WiFi.scanDelete();
    }

#endif

#if ASYNC_SCAN_MODE == 2
    currentMillis = millis();

    if (currentMillis - lastMillis > scanPeriod)
    {
        lastMillis = currentMillis;
        Serial.println("Scan starts...");
        /* 异步扫描模式1 */
        WiFi.scanNetworksAsync(print_scan_result);        
    }
#endif
}

