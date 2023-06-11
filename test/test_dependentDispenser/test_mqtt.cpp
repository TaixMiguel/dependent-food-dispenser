#include <Arduino.h>
#include <unity.h>

#include "Config.h"
#include "ToolMQTT.h"

ToolMQTT toolMQTT;

void setUp(void) {}

void tearDown(void) {}

void test_mqttConnected(void) {
  toolMQTT.connect();
  TEST_ASSERT_TRUE(toolMQTT.isConnected());
}

void test_mqttDisconnected(void) {
  if (toolMQTT.isConnected()) {
    toolMQTT.disconnect();
    TEST_ASSERT_FALSE(toolMQTT.isConnected());
  }
}

void setup() {
  delay(2000);

  cfg.connectToWiFi();

  UNITY_BEGIN();
  RUN_TEST(test_mqttConnected);
  RUN_TEST(test_mqttDisconnected);
  UNITY_END();
}

void loop() {}
