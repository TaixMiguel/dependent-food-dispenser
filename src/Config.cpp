#include "Config.h"

Config::Config(const char* appName): ConfigApp(appName) {
  swReceivedDataMQTT = true;
  swEnabledMQTT = false;
}

void Config::connectToMQTT(MQTTClient& client, WiFiClient& espClient) {
  if (!isWiFiConnected()) {
    ESP_LOGI(cfg.appName, "No se conecta con el servidor MQTT por no tener conexión WiFi");
    return;
  }

  String mqttServer = getString("mqtt_server");
  if (mqttServer.isEmpty()) {
    ESP_LOGI(cfg.appName, "No se conecta con el servidor MQTT por falta de config");
  } else {
    int count = 0;
    client.setKeepAlive(180);
    client.begin(mqttServer.c_str(), 1883, espClient);
    ESP_LOGD(cfg.appName, "Conectando al servidor MQTT %s.", mqttServer);
    while (!client.connect(getString("mqtt_client").c_str(), getString("mqtt_user").c_str(), getString("mqtt_pass").c_str()) && count++ < 25)
      delay(500);
  }
  swEnabledMQTT = client.connected();
}

bool Config::isEnabledMQTT() {
  return swEnabledMQTT;
}

String Config::idDevice() {
  if (deviceID.isEmpty()) {
    uint8_t baseMac[6];
    char baseMacChr[13] = {0};
    esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
    sprintf(baseMacChr, "%02X%02X%02X%02X%02X%02X", baseMac[1], baseMac[3], baseMac[5], baseMac[4], baseMac[2], baseMac[0]);
    deviceID = String(baseMacChr);
    deviceID.toLowerCase();
  }
  return deviceID;
}

bool Config::isReceivedDataMQTT() {
  return swReceivedDataMQTT;
}
void Config::setReceivedMQTT(bool swReceivedData) {
  swReceivedDataMQTT = swReceivedData;
}
long Config::getDurationNextEat() {
  return durationNextEat;
}
void Config::setDurationNextEat(long durationNextEat) {
  this->durationNextEat = durationNextEat;
}
long Config::getTimestampNextEat() {
  return timestampNextEat;
}
void Config::setTimestampNextEat(long timestampNextEat) {
  this->timestampNextEat = timestampNextEat;
}


#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_CFGHANDLER)
  Config cfg;
#endif
