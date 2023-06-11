#include "ToolMQTT.h"

ToolMQTT::ToolMQTT() {}

bool ToolMQTT::isConnected() {
  return client.connected();
}

void ToolMQTT::disconnect() {
  client.disconnect();
}

void ToolMQTT::connect() {
  if (!cfg.isWiFiConnected()) delay(2500);
  cfg.connectToMQTT(client, espClient);
}

void ToolMQTT::loop() {
  if (!cfg.isEnabledMQTT()) return;
  if (!isConnected()) connect();
  client.loop();
}
