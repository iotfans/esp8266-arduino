# 1 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiGeneric\\ESP8266WiFiGeneric.ino"
/*

    This sketch shows how to use WiFi event handlers.



    In this example, ESP8266 works in AP mode.

    Three event handlers are demonstrated:

    - station connects to the ESP8266 AP

    - station disconnects from the ESP8266 AP

    - ESP8266 AP receives a probe request from a station

*/
# 11 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiGeneric\\ESP8266WiFiGeneric.ino"
# 12 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiGeneric\\ESP8266WiFiGeneric.ino" 2
# 13 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiGeneric\\ESP8266WiFiGeneric.ino" 2

/* 调整注释切换AP模式和STA模式的事件Demo */
//#define AP_WIFI_GENERIC     1
# 109 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiGeneric\\ESP8266WiFiGeneric.ino"
/* ======================================================================== */
/* 以下为Station模式事件Demo */


const char *ssid = "my_Wifi_1st";
const char *password = "qianrushi";

WiFiEventHandler STAConnected;
WiFiEventHandler STADisconnected;
WiFiEventHandler STAGotIP;

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
    delay(5000); //等待5秒
    WiFi.disconnect(); //断开当前网络连接
    delay(5000);
    WiFi.begin(ssid, password);
    Serial.println(WiFi.status());
}
