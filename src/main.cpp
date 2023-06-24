#include <Arduino.h>

#include "Config.h"
#include "ToolFoodDispenser.h"
#include "ToolMQTT.h"
#include <WiFi.h>

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
  // TODO: tener en cuenta el valor de swMotor
  if (swBattery) batteryLevel += toolDispenser.getBatteryLevel(pinBattery);
  // put your main code here, to run repeatedly:
  delay(2500);
  toolMQTT.loop();
  Serial.println(getTimeToNextEat());
  Serial.println(WiFi.status());
  Serial.println(toolMQTT.isConnected());

  if (cfg.getTimestampNextEat() > 0) {
    long timeToEat = getTimeToNextEat();
    if (timeToEat <= 0) {
      toolDispenser.launcherFood(pinDispenserMotor, cfg.getDurationNextEat());
    } else
      toolDispenser.launchSleepMode(timeToEat);
  }

  if (count++ > 10) ESP.restart();
}

long getTimeToNextEat() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    ESP_LOGE(cfg.appName, "Error al obtener la hora");
    return(1000);
  }
  time(&now);
  return cfg.getTimestampNextEat() - now;
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
