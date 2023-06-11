#ifndef ConfigApp_h
#define ConfigApp_h

#include <Preferences.h>
#include <WiFi.h>

/**
 * @author TaixMiguel
 */
class ConfigApp {

  public:
    ConfigApp(const char* appName="autdisp");
    const char* appName;

    void connectToWiFi();
    bool isWiFiConnected();

  protected:
    virtual bool getBool(String key, bool valueDefault=false);
    virtual float getFloat(String key, float valueDefault=-1);
    virtual int getInt(String key, int valueDefault=-1);
    virtual long getLong(String key, long valueDefault=-1);
    virtual String getString(String key, String valueDefault="");

    virtual void saveBool(String key, bool value);
    virtual void saveFloat(String key, float value);
    virtual void saveInt(String key, int value);
    virtual void saveLong(String key, long value);
    virtual void saveString(String key, String value);

  private:
    Preferences preferences;
};

#endif
