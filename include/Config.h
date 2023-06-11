#ifndef Config_h
#define Config_h

#include "ConfigApp.h"
#include <MQTT.h>
#include <WiFi.h>

/**
 * @author TaixMiguel
 */
class Config: public ConfigApp {

  public:
    Config(const char* appName="autdisp");

    void connectToMQTT(MQTTClient& client, WiFiClient& espClient);
    bool isEnabledMQTT();

  private:
    bool swEnabledMQTT = false;
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_CFGHANDLER)
  extern Config cfg;
#endif

#endif