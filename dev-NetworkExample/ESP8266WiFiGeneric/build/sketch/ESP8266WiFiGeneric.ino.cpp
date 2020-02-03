#include <Arduino.h>
#line 1 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiGeneric\\ESP8266WiFiGeneric.ino"
/*
    This sketch shows how to use WiFi event handlers.

    In this example, ESP8266 works in AP mode.
    Three event handlers are demonstrated:
    - station connects to the ESP8266 AP
    - station disconnects from the ESP8266 AP
    - ESP8266 AP receives a probe request from a station
*/

#include <ESP8266WiFi.h>
#include <stdio.h>

/* 调整注释切换AP模式和STA模式的事件Demo */
//#define AP_WIFI_GENERIC     1
#define STA_WIFI_GENERIC 1

#ifdef AP_WIFI_GENERIC
const char *ssid = "ap-ssid";
const char *password = "ap-password";

WiFiEventHandler stationConnectedHandler;
WiFiEventHandler stationDisconnectedHandler;
WiFiEventHandler probeRequestPrintHandler;
WiFiEventHandler probeRequestBlinkHandler;

bool blinkFlag;

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    // 不保存任何wifi配置到flash
    WiFi.persistent(false);

    // 建立一个AP
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);

    // 注册事件处理器
    // 回调函数会在事件发生时被调用
    // onStationConnected函数会在每一次有station连接时调用
    stationConnectedHandler = WiFi.onSoftAPModeStationConnected(&onStationConnected);
    // onStationDisconnected函数会在每一次有station断开时调用
    stationDisconnectedHandler = WiFi.onSoftAPModeStationDisconnected(&onStationDisconnected);
    // onProbeRequestPrint和onProbeRequestBlink函数会在每一次收到探针请求时调用
    // onProbeRequestPrint会打印station的mac地址和信号强度到串口监视器
    // onProbeRequestBlink会闪烁LED
    probeRequestPrintHandler = WiFi.onSoftAPModeProbeRequestReceived(&onProbeRequestPrint);
    probeRequestBlinkHandler = WiFi.onSoftAPModeProbeRequestReceived(&onProbeRequestBlink);
}

void onStationConnected(const WiFiEventSoftAPModeStationConnected &evt)
{
    Serial.print("Station connected: ");
    Serial.println(macToString(evt.mac));
}

void onStationDisconnected(const WiFiEventSoftAPModeStationDisconnected &evt)
{
    Serial.print("Station disconnected: ");
    Serial.println(macToString(evt.mac));
}

void onProbeRequestPrint(const WiFiEventSoftAPModeProbeRequestReceived &evt)
{
    Serial.print("Probe request from: ");
    Serial.print(macToString(evt.mac));
    Serial.print(" RSSI: ");
    Serial.println(evt.rssi);
}

void onProbeRequestBlink(const WiFiEventSoftAPModeProbeRequestReceived &)
{
    // 我们不能在事件处理函数中调用延时函数或者其他阻塞函数
    // 因此这里设置一个标志位
    blinkFlag = true;
}

void loop()
{
    if (millis() > 10000 && probeRequestPrintHandler)
    {
        // 10s之后，禁止 onProbeRequestPrint
        Serial.println("Not printing probe requests any more (LED should still blink)");
        probeRequestPrintHandler = WiFiEventHandler();
    }
    if (blinkFlag)
    {
        blinkFlag = false;
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
    }
    delay(10);
}

String macToString(const unsigned char *mac)
{
    char buf[20];
    snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(buf);
}
#endif

/* ======================================================================== */
/* 以下为Station模式事件Demo */
#ifdef STA_WIFI_GENERIC

const char *ssid = "my_Wifi_1st";
const char *password = "qianrushi";

WiFiEventHandler STAConnected;
WiFiEventHandler STADisconnected;
WiFiEventHandler STAGotIP;

#line 120 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiGeneric\\ESP8266WiFiGeneric.ino"
void ConnectedHandler(const WiFiEventStationModeConnected &event);
#line 126 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiGeneric\\ESP8266WiFiGeneric.ino"
void DisconnectedHandler(const WiFiEventStationModeDisconnected &event);
#line 132 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiGeneric\\ESP8266WiFiGeneric.ino"
void setup();
#line 149 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiGeneric\\ESP8266WiFiGeneric.ino"
void loop();
#line 120 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiGeneric\\ESP8266WiFiGeneric.ino"
void ConnectedHandler(const WiFiEventStationModeConnected &event)
{
    Serial.println(WiFi.status());
    Serial.println("模块连接到网络");
}

void DisconnectedHandler(const WiFiEventStationModeDisconnected &event)
{
    Serial.println(WiFi.status());
    Serial.println("模块从网络断开");
}

void setup()
{
    Serial.begin(115200);
    Serial.println();

    STAConnected = WiFi.onStationModeConnected(ConnectedHandler);
    STADisconnected = WiFi.onStationModeDisconnected(DisconnectedHandler);
    STAGotIP = WiFi.onStationModeGotIP([](const WiFiEventStationModeGotIP &event) {
        Serial.println(WiFi.status());
        Serial.println("模块获得IP");
    });

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println(WiFi.status());
}

void loop()
{
    delay(5000);       //等待5秒
    WiFi.disconnect(); //断开当前网络连接
    delay(5000);
    WiFi.begin(ssid, password);
    Serial.println(WiFi.status());
}

#endif

