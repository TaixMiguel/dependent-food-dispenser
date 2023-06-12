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

    String idDevice();
    bool isReceivedDataMQTT();
    void setReceivedMQTT(bool swReceivedData);
    void setDurationNextEat(long durationNextEat);
    long getTimestampNextEat();
    void setTimestampNextEat(long timestampNextEat);

  private:
    bool swEnabledMQTT, swReceivedDataMQTT;
    long durationNextEat, timestampNextEat;
    String deviceID;
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_CFGHANDLER)
  extern Config cfg;
#endif

#endif