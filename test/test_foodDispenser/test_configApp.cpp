#include <Arduino.h>
#include <unity.h>

#include "ConfigApp.h"
#include <Preferences.h>

const char* appName = "appTest";
ConfigApp configApp(appName);
Preferences preferences;

void setUp(void) {}

void tearDown(void) {}

void test_preferencesBool(void) {
  TEST_ASSERT_TRUE(configApp.getBool("SWTEST_TRUE"));
  TEST_ASSERT_FALSE(configApp.getBool("SWTEST_FALSE"));

  TEST_ASSERT_FALSE(configApp.getBool("SW_NOT_EXISTS"));
  TEST_ASSERT_TRUE(configApp.getBool("SW_NOT_EXISTS", true));
}

void test_preferencesFloat(void) {
  TEST_ASSERT_EQUAL_FLOAT(configApp.getFloat("FLOAT_NUMBER"), 35.25);

  TEST_ASSERT_EQUAL_FLOAT(configApp.getFloat("FLOAT_NUMBER_NOT_EXISTS"), -1);
  TEST_ASSERT_EQUAL_FLOAT(configApp.getFloat("FLOAT_NUMBER_NOT_EXISTS", 20.15), 20.15);
}

void test_preferencesInt(void) {
  TEST_ASSERT_EQUAL_INT(configApp.getInt("INT_NUMBER"), 35);

  TEST_ASSERT_EQUAL_INT(configApp.getInt("INT_NUMBER_NOT_EXISTS"), -1);
  TEST_ASSERT_EQUAL_INT(configApp.getInt("INT_NUMBER_NOT_EXISTS", 20), 20);
}

void test_preferencesLong(void) {
  TEST_ASSERT_EQUAL_INT(configApp.getLong("LONG_NUMBER"), 456789123);

  TEST_ASSERT_EQUAL_INT(configApp.getLong("LONG_NUMBER_NOT_EXISTS"), -1);
  TEST_ASSERT_EQUAL_INT(configApp.getLong("LONG_NUMBER_NOT_EXISTS", 789789456), 789789456);
}

void test_preferencesString(void) {
  TEST_ASSERT_EQUAL_STRING(configApp.getString("STRING").c_str(), "TEXT string");

  TEST_ASSERT_EQUAL_STRING(configApp.getString("STRING_NOT_EXISTS").c_str(), "");
  TEST_ASSERT_EQUAL_STRING(configApp.getString("STRING_NOT_EXISTS", "NoT exists").c_str(), "NoT exists");
}

void setPreferencesDefault() {
  preferences.begin(appName, false);
  preferences.putBool("SWTEST_TRUE", true);
  preferences.putBool("SWTEST_FALSE", false);
  preferences.putFloat("FLOAT_NUMBER", 35.25);
  preferences.putInt("INT_NUMBER", 35);
  preferences.putLong("LONG_NUMBER", 456789123);
  preferences.putString("STRING", "TEXT string");
  preferences.end();
}
void cleanPreferences() {
  preferences.begin(appName, false);
  preferences.clear();
  preferences.end();
}

void setup() {
  delay(2000);

  setPreferencesDefault();

  UNITY_BEGIN();
  RUN_TEST(test_preferencesBool);
  RUN_TEST(test_preferencesFloat);
  RUN_TEST(test_preferencesInt);
  RUN_TEST(test_preferencesLong);
  RUN_TEST(test_preferencesString);
  UNITY_END();

  cleanPreferences();
}

void loop() {}
