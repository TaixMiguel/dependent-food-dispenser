#ifndef ToolMQTT_h
#define ToolMQTT_h

#include <ArduinoJson.h>
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

    bool publish(String topicSubfix, String payload="", bool retain=false, int qos=2);

  private:
    static String formatTopic(String topicSubfix);
    static void messageReceived(String &topic, String &payload);
    bool _publish(String topic, String payload, bool retain, int qos);

    void checkConnection();
    bool swLoopToSend = false;
};

#endif