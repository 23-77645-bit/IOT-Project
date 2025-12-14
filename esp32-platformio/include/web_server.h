#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>
#include <WebServer.h>
#include <ArduinoJson.h>

class WebServerHandler {
private:
    WebServer* server;
    String username;
    String password;
    bool isAuthenticated();
    void handleRoot();
    void handleUnlock();
    void handleLock();
    void handleGetLogs();
    void handleNotFound();
    
public:
    WebServerHandler(int port, const char* user, const char* pass);
    ~WebServerHandler();
    
    bool begin();
    void handleClient();
    void setLockCallback(void (*callback)(bool lock));
    
private:
    void (*lockCallback)(bool lock);
};

#endif // WEB_SERVER_H