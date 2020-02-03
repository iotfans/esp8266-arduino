# 1 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiScan\\ESP8266WiFiScan.ino"
# 2 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiScan\\ESP8266WiFiScan.ino" 2

//#define SYNC_SCAN_MODE 1      //同步扫描模式
//#define ASYNC_SCAN_MODE 1     //异步扫描模式1


int scanPeriod = 5000; //每隔5000ms扫描一次          
long lastMillis = 0;
long currentMillis = 0;


void print_scan_result(int numOfNetworks)
{
    Serial.printf("%d network(s) founded\r\n", numOfNetworks);
    for (size_t i = 0; i < numOfNetworks; i++)
    {
        Serial.printf("%d: %s, Channel:%d (%ddBm) %s\r\n", i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i) == ENC_TYPE_NONE ? "open" : "encrypted");
    }
    WiFi.scanDelete();
}


void setup()
{
    Serial.begin(115200);
    delay(5000);

    WiFi.mode(WIFI_STA);
    /* 先断开连接(避免奇怪的bug) */
    WiFi.disconnect();
    delay(100);
    Serial.println("Setup done.");




}

void loop()
{
# 106 "d:\\arduino-1.8.10\\sketch_WorkSpace\\ESP8266WiFiScan\\ESP8266WiFiScan.ino"
    currentMillis = millis();

    if (currentMillis - lastMillis > scanPeriod)
    {
        lastMillis = currentMillis;
        Serial.println("Scan starts...");
        /* 异步扫描模式1 */
        WiFi.scanNetworksAsync(print_scan_result);
    }

}
