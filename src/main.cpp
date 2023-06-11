#include <Arduino.h>

#include "Config.h"
#include "ToolFoodDispenser.h"
#include "ToolMQTT.h"
#include <WiFi.h>

ToolFoodDispenser toolDispenser;
ToolMQTT toolMQTT;

void wiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  toolDispenser.updateTime();
  toolMQTT.connect();
  // toolMQTT.publish("status");
}
void wiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  ESP_LOGD(cfg.appName, "Conexión WiFi perdida. Causa %s. Intentando re-conectar", info.wifi_sta_disconnected.reason);
  cfg.connectToWiFi();
}

void setup() {
  Serial.begin(115200);
  WiFi.onEvent(wiFiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(wiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  cfg.connectToWiFi();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2500);
  toolMQTT.loop();
  Serial.println(WiFi.status());
  Serial.println(toolMQTT.isConnected());
}
