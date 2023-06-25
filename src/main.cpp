#include <Arduino.h>

#include "Config.h"
#include "ToolFoodDispenser.h"
#include "ToolMQTT.h"
#include <WiFi.h>

StaticJsonDocument<200> jsonOutput;
ToolFoodDispenser toolDispenser;
float batteryLevel = 0;
ToolMQTT toolMQTT;
int count = 1;

uint8_t pinDispenserMotor, pinBattery;
bool swBattery, swMotor;

void wiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  toolDispenser.updateTime();
  toolMQTT.connect();
  // toolMQTT.publish("status");
}
void wiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  ESP_LOGD(cfg.appName, "Conexión WiFi perdida. Causa %s. Intentando re-conectar", info.wifi_sta_disconnected.reason);
  toolMQTT.disconnect();
  cfg.connectToWiFi();
}

void setupDispenserMotor();
long getTimeToNextEat();
long getTimestampNow();
void setupBattery();

void setup() {
  Serial.begin(115200);
  WiFi.onEvent(wiFiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(wiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  cfg.connectToWiFi();

  setupDispenserMotor();
  setupBattery();
}

void loop() {
  if (swMotor) {
    delay(2500);
    toolMQTT.loop();
    if (swBattery) batteryLevel += toolDispenser.getBatteryLevel(pinBattery);

    if (cfg.getTimestampNextEat() > 0) {
      long timeToEat = getTimeToNextEat();
      if (timeToEat <= 0) {
        long now = getTimestampNow();
        toolDispenser.launcherFood(pinDispenserMotor, cfg.getDurationNextEat());
        cfg.setTimestampNextEat(now + 20); // Se suman 20 segundos
        jsonOutput["lastEatTime"] = now;
        cfg.setReceivedMQTT(true);
      } else if (timeToEat <= 10) {
        // Condición para 10 segundos
        delay((timeToEat * 1000) - 2500);
      } else {
        String payload;
        if (swBattery) jsonOutput["battery"] = batteryLevel/count;
        if (!jsonOutput.isNull()) {
          serializeJson(jsonOutput, payload);
          toolMQTT.publish("set", payload);
        }
        toolDispenser.launchSleepMode(timeToEat);
      }
    }

    if (count++ > 10) ESP.restart();
  } else ESP.restart();

  // TODO: cuando se actualice automáticamente se tiene que quitar el reinicio cuando no hay motor
}

long getTimeToNextEat() {
  return cfg.getTimestampNextEat() - getTimestampNow();
}
long getTimestampNow() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    ESP_LOGE(cfg.appName, "Error al obtener la hora");
    return(1000);
  }
  time(&now);
  return now;
}

void setupDispenserMotor() {
  pinDispenserMotor = cfg.getDispenserMotorPin();
  if (pinDispenserMotor <= 0) {
    ESP_LOGE(cfg.appName, "No se ha definido un pin válido (%i) para el uso del motor", pinDispenserMotor);
    swMotor = false;
    return;
  }
  ESP_LOGD(cfg.appName, "Se establece el pin %i para el uso del motor", pinDispenserMotor);
  pinMode(pinDispenserMotor, INPUT);
  swMotor = true;
}

void setupBattery() {
  swBattery = cfg.isBatteryEnabled();
  if (swBattery) {
    pinBattery = cfg.getBatteryPin();
    if (pinBattery > 0) pinMode(pinBattery, INPUT);
    else swBattery = false;
  }
  ESP_LOGD(cfg.appName, "%s => %i", swBattery ? "Batería habilitada" : "Batería no habilitada", pinBattery);
}
