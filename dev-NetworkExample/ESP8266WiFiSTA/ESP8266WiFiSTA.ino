#include <ESP8266WiFi.h>

/* 静态IP地址模式 */
#define STATIC_IP_MODE 1

/* 修改为喜欢的接入点与密码 */
#define ROUTER_SSID "my_Wifi_1st"
#define ROUTER_PSW "qianrushi"

IPAddress staticIP(192, 168, 2, 188); //固定IP地址
IPAddress gateway(192, 168, 2, 1);    //网关地址
IPAddress subnet(255, 255, 255, 0);   //子网掩码地址

uint8_t macAddr[6];

void setup()
{
    Serial.begin(115200);
    /* 为了演示效果 */
    delay(2000);

    Serial.println("Setting Station Configuration ... ");

    /* 配置WiFi的工作模式为Station */
    /* 连接到路由器 */
    WiFi.begin(ROUTER_SSID, ROUTER_PSW);
    /* 设置自动连接 */
    if (WiFi.getAutoConnect() == false)
    {
        WiFi.setAutoConnect(true);
    }

    /* 设置自动重连 */
    if (WiFi.getAutoReconnect() == false)
    {
        WiFi.setAutoReconnect(true);
    }

    Serial.print(String("Connecting to ") + ROUTER_SSID);

#if defined STATIC_IP_MODE
    /* 手动配置指定的IP地址 */
    WiFi.config(staticIP, gateway, subnet);
#endif
    while (WiFi.status() != WL_CONNECTED /* condition */)
    {
        /* code */
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    /* 打印输出一系列网络信息 */
    Serial.println("Print the network information...");

    if (WiFi.status() == WL_CONNECTED)
    {
        /* 输出mac地址 */
        Serial.println(String("Connected, mac address: ") + WiFi.macAddress().c_str());

        /* 输出station IP地址，这里的IP地址由DHCP分配 */
        Serial.println(String("Connected, IP address: ") + WiFi.localIP().toString());

        /* 输出子网掩码地址 */
        Serial.println(String("Subnet mask: ") + WiFi.subnetMask().toString());

        /* 输出网关 IP地址 */
        Serial.println(String("Gataway IP: ") + WiFi.gatewayIP().toString());

        /* 输出hostname */
        Serial.println(String("Default hostname: ") + WiFi.hostname());
        /* 设置新的hostname */
        WiFi.hostname("Station_host_Liguo");
        Serial.println(String("New hostname: ") + WiFi.hostname());

        /* 输出SSID */
        Serial.println(String("SSID: ") + WiFi.SSID());

        /* 输出psk */
        Serial.println(String("psk: ") + WiFi.psk());

        //输出BSSID
        Serial.println(String("BSSID: ") + WiFi.BSSIDstr());

        //输出RSSI
        Serial.println(String("RSSI: ") + WiFi.RSSI() + " dBm");
    }else{
        Serial.println("WiFi connect abnornal, Station Config Over.");
    }
}

void loop()
{
}
