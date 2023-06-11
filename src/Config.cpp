#include "Config.h"

Config::Config(const char* appName): ConfigApp(appName) {}

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

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_CFGHANDLER)
  Config cfg;
#endif
