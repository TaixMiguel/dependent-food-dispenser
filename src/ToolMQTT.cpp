#include "ToolMQTT.h"

WiFiClient espClient;
int bufferSizeMQTT = 768;
MQTTClient client(bufferSizeMQTT);

ToolMQTT::ToolMQTT() {}

bool ToolMQTT::isConnected() {
  return client.connected();
}

void ToolMQTT::checkConnection() {
  if (!isConnected()) connect();
}

void ToolMQTT::disconnect() {
  client.disconnect();
}

void ToolMQTT::connect() {
  cfg.connectToMQTT(client, espClient);
  client.onMessage(messageReceived);
  client.subscribe(formatTopic("state"));
}

void ToolMQTT::loop() {
  if (cfg.isReceivedDataMQTT() || swLoopToSend) {
    if (!cfg.isEnabledMQTT()) return;
    checkConnection();
    client.loop();
    swLoopToSend = false;
  }
}

bool ToolMQTT::publish(String topicSubfix, String payload, bool retain, int qos) {
  return _publish(formatTopic(topicSubfix), payload, retain, qos);
}

bool ToolMQTT::_publish(String topic, String payload, bool retain, int qos) {
  ESP_LOGD(cfg.appName, "Buffer size: %u.\tJSON size: %u.\tFree heap size: %u", bufferSizeMQTT, payload.length(), ESP.getFreeHeap());
  checkConnection();
  ESP_LOGD(cfg.appName, "Se envia el topic '%s' con valor '%s'", topic.c_str(), payload.c_str());
  if (client.publish(topic.c_str(), payload, retain, qos)) { 
    swLoopToSend = true;
    return true;
  }
  ESP_LOGE(cfg.appName, "Se ha recibido el error '%s' por el topic '%s'", String(client.lastError()), topic.c_str());
  return false;
}

void ToolMQTT::messageReceived(String &topic, String &payload) {
  ESP_LOGD(cfg.appName, "Se recibe el topic '%s' con valor '%s'", topic.c_str(), payload.c_str());

  if (strcmp(topic.c_str(), formatTopic("state").c_str()) == 0) {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    cfg.setReceivedMQTT(false);

    long nextEatDoses = doc["nextEatDoses"];
    long timeDoses = doc["timeDoses"];
    cfg.setDurationNextEat(nextEatDoses * timeDoses);
    cfg.setTimestampNextEat(doc["nextEatTime"]);
  }
}

String ToolMQTT::formatTopic(String topicSubfix) {
  return "/taixmiguel/pets/automaticDispenser_" + cfg.idDevice() + "/" + topicSubfix;
}
