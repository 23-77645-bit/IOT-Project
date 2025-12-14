#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <Arduino.h>
#include <WiFi.h>

class WiFiHandler {
private:
    String ssid;
    String password;
    bool connected;
    unsigned long lastReconnectAttempt;
    unsigned long reconnectInterval;
    int reconnectAttempts;

public:
    WiFiHandler(const char* ssid, const char* password);
    ~WiFiHandler();
    
    bool begin();
    bool isConnected() { return connected; }
    void maintainConnection();
    String getLocalIP();
    int getRSSI();
    void disconnect();
    
private:
    void connect();
    void onConnected();
    void onDisconnected();
};

#endif // WIFI_HANDLER_H