#include <Arduino.h>

#include "ConfigApp.h"
#include <WiFi.h>

ConfigApp config;

void wiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
  ESP_LOGD(config.appName, "Conexión WiFi perdida. Causa %s. Intentando re-conectar", info.wifi_sta_disconnected.reason);
  config.connectToWiFi();
}

void setup() {
  Serial.begin(115200);
  config.connectToWiFi();
  WiFi.onEvent(wiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2500);
  Serial.println(WiFi.status());
}
