#ifndef ToolMQTT_h
#define ToolMQTT_h

#include "Config.h"
#include <MQTT.h>
#include <WiFi.h>

/**
 * @author TaixMiguel
 */
class ToolMQTT {

  public:
    ToolMQTT();

    bool isConnected();
    void disconnect();
    void connect();
    void loop();

  private:
    MQTTClient client;
    WiFiClient espClient;
};

#endif