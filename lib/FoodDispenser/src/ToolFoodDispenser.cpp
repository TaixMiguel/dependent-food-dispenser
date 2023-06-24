#include "ToolFoodDispenser.h"

ToolFoodDispenser::ToolFoodDispenser() {}

void ToolFoodDispenser::updateTime() {
  if (config.isWiFiConnected()) {
    ESP_LOGD(config.appName, "Actualización de la hora actual");
    TaixArduTime taixTime;
    taixTime.updateTime();
  }
}

void ToolFoodDispenser::launcherFood(uint8_t pin, int dispenseTime) {
  ESP_LOGD(config.appName, "Se va a dar comida durante %i segundos", dispenseTime/1000);
  digitalWrite(pin, HIGH);
  delay(dispenseTime);
  digitalWrite(pin, LOW);
  ESP_LOGI(config.appName, "Se ha dispensado comida durante %i segundos", dispenseTime/1000);
}

float ToolFoodDispenser::getBatteryLevel(uint8_t pin) {
  return map(analogRead(pin), 0.0f, 4095.0f, 0, 100);
}

void ToolFoodDispenser::externalShutdown() {
  // TODO
}

void ToolFoodDispenser::launchSleepMode(long timeSleep, long timeExternalSleep) {
  if (timeExternalSleep > 0 && timeExternalSleep < timeSleep) {
    ESP_LOGD(config.appName, "Se intenta apagar la placa %i segundos por el apagado externo", timeExternalSleep);
    externalShutdown();
  }

  if (timeSleep < 0 || timeSleep > TIME_MAX_SLEEP) timeSleep = TIME_MAX_SLEEP;
  ESP_LOGD(config.appName, "Se procede a dormir durante %i segundos", timeSleep);
  esp_sleep_enable_timer_wakeup(timeSleep * FACTOR_MICRO_SECONDS);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  esp_deep_sleep_start();
}
