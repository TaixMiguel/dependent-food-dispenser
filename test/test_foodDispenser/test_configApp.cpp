#include <Arduino.h>
#include <unity.h>

#include "ConfigApp.h"
#include <Preferences.h>
#include <WiFi.h>

class ConfigTest: public ConfigApp {

  public:
    ConfigTest(const char* appName): ConfigApp(appName) {}

    void saveBool(String key, bool value) {
      ConfigApp::saveBool(key, value);
    }
    bool getBool(String key, bool valueDefault=false) {
      return ConfigApp::getBool(key, valueDefault);
    }
    float getFloat(String key, float valueDefault=-1) {
      return ConfigApp::getFloat(key, valueDefault);
    }
    void saveFloat(String key, float value) {
      ConfigApp::saveFloat(key, value);
    }
    int getInt(String key, int valueDefault=-1) {
      return ConfigApp::getInt(key, valueDefault);
    }
    void saveInt(String key, int value) {
      ConfigApp::saveInt(key, value);
    }
    long getLong(String key, long valueDefault=-1) {
      return ConfigApp::getLong(key, valueDefault);
    }
    void saveLong(String key, long value) {
      ConfigApp::saveLong(key, value);
    }
    String getString(String key, String valueDefault="") {
      return ConfigApp::getString(key, valueDefault);
    }
    void saveString(String key, String value) {
      ConfigApp::saveString(key, value);
    }
};

const char* appName = "appTest";
ConfigTest config(appName);
Preferences preferences;


void setUp(void) {}

void tearDown(void) {}

void test_preferencesBool(void) {
  config.saveBool("SWTEST_TRUE", true);
  config.saveBool("SWTEST_FALSE", false);
  TEST_ASSERT_TRUE(config.getBool("SWTEST_TRUE"));
  TEST_ASSERT_FALSE(config.getBool("SWTEST_FALSE"));

  TEST_ASSERT_FALSE(config.getBool("SW_NOT_EXISTS"));
  TEST_ASSERT_TRUE(config.getBool("SW_NOT_EXISTS", true));
}

void test_preferencesFloat(void) {
  config.saveFloat("FLOAT_NUMBER", 35.25);
  TEST_ASSERT_EQUAL_FLOAT(config.getFloat("FLOAT_NUMBER"), 35.25);

  TEST_ASSERT_EQUAL_FLOAT(config.getFloat("FLOAT_NUMBER_NOT_EXISTS"), -1);
  TEST_ASSERT_EQUAL_FLOAT(config.getFloat("FLOAT_NUMBER_NOT_EXISTS", 20.15), 20.15);
}

void test_preferencesInt(void) {
  config.saveInt("INT_NUMBER", 35);
  TEST_ASSERT_EQUAL_INT(config.getInt("INT_NUMBER"), 35);

  TEST_ASSERT_EQUAL_INT(config.getInt("INT_NUMBER_NOT_EXISTS"), -1);
  TEST_ASSERT_EQUAL_INT(config.getInt("INT_NUMBER_NOT_EXISTS", 20), 20);
}

void test_preferencesLong(void) {
  config.saveLong("LONG_NUMBER", 456789123);
  TEST_ASSERT_EQUAL_INT(config.getLong("LONG_NUMBER"), 456789123);

  TEST_ASSERT_EQUAL_INT(config.getLong("LONG_NUMBER_NOT_EXISTS"), -1);
  TEST_ASSERT_EQUAL_INT(config.getLong("LONG_NUMBER_NOT_EXISTS", 789789456), 789789456);
}

void test_preferencesString(void) {
  config.saveString("STRING", "TEXT string");
  TEST_ASSERT_EQUAL_STRING(config.getString("STRING").c_str(), "TEXT string");

  TEST_ASSERT_EQUAL_STRING(config.getString("STRING_NOT_EXISTS").c_str(), "");
  TEST_ASSERT_EQUAL_STRING(config.getString("STRING_NOT_EXISTS", "NoT exists").c_str(), "NoT exists");
}

void cleanPreferences() {
  preferences.begin(appName, false);
  preferences.clear();
  preferences.end();
}



void test_wiFiConnected(void) {
  ConfigApp config;
  config.connectToWiFi();
  delay(5000);
  TEST_ASSERT_EQUAL_INT(WL_CONNECTED, WiFi.status());
}

void setup() {
  delay(2000);

  UNITY_BEGIN();
  RUN_TEST(test_preferencesBool);
  RUN_TEST(test_preferencesFloat);
  RUN_TEST(test_preferencesInt);
  RUN_TEST(test_preferencesLong);
  RUN_TEST(test_preferencesString);

  RUN_TEST(test_wiFiConnected);
  UNITY_END();

  cleanPreferences();
}

void loop() {}
