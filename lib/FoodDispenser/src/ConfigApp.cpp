#include "ConfigApp.h"

ConfigApp::ConfigApp(const char* appName) {
  this->appName = appName;
}

bool ConfigApp::getBool(String key, bool value) {
  preferences.begin(appName, true);
  value = preferences.getBool(key.c_str(), value);
  preferences.end();
  return value;
}
void ConfigApp::saveBool(String key, bool value) {
  preferences.begin(appName, false);
  preferences.putBool(key.c_str(), value);
  preferences.end();
}
float ConfigApp::getFloat(String key, float value) {
  preferences.begin(appName, true);
  value = preferences.getFloat(key.c_str(), value);
  preferences.end();
  return value;
}
void ConfigApp::saveFloat(String key, float value) {
  preferences.begin(appName, false);
  preferences.putFloat(key.c_str(), value);
  preferences.end();
}
int ConfigApp::getInt(String key, int value) {
  preferences.begin(appName, true);
  value = preferences.getInt(key.c_str(), value);
  preferences.end();
  return value;
}
void ConfigApp::saveInt(String key, int value) {
  preferences.begin(appName, false);
  preferences.putInt(key.c_str(), value);
  preferences.end();
}
long ConfigApp::getLong(String key, long value) {
  preferences.begin(appName, true);
  value = preferences.getLong(key.c_str(), value);
  preferences.end();
  return value;
}
void ConfigApp::saveLong(String key, long value) {
  preferences.begin(appName, false);
  preferences.putLong(key.c_str(), value);
  preferences.end();
}
String ConfigApp::getString(String key, String value) {
  preferences.begin(appName, true);
  value = preferences.getString(key.c_str(), value);
  preferences.end();
  return value;
}
void ConfigApp::saveString(String key, String value) {
  preferences.begin(appName, false);
  preferences.putString(key.c_str(), value);
  preferences.end();
}
