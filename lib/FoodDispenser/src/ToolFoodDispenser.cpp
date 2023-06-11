#include "ToolFoodDispenser.h"

ToolFoodDispenser::ToolFoodDispenser() {}

void ToolFoodDispenser::updateTime() {
  ConfigApp config;
  if (config.isWiFiConnected()) {
    ESP_LOGD(config.appName, "Actualización de la hora actual");
    TaixArduTime taixTime;
    taixTime.updateTime();
  }
}
