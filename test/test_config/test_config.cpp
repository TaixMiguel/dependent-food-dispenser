#include <Arduino.h>
#include <unity.h>

#include "Config.h"


void setUp(void) {}

void tearDown(void) {}

void test_idDevice(void) {
  TEST_ASSERT_FALSE(cfg.idDevice().isEmpty());
}


void setup() {
  delay(2000);

  UNITY_BEGIN();
  RUN_TEST(test_idDevice);
  UNITY_END();
}

void loop() {}
