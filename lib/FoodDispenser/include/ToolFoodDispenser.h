#ifndef ToolFoodDispenser_h
#define ToolFoodDispenser_h

#include "ConfigApp.h"
#include <taixArduTime.hpp>

#define FACTOR_MICRO_SECONDS 1000000

/**
 * @author TaixMiguel
 */
class ToolFoodDispenser {

  public:
    ToolFoodDispenser();

    void updateTime();

    void launcherFood(uint8_t pin, int dispenseTime);
    float getBatteryLevel(uint8_t pin);

    void externalShutdown();
    void launchSleepMode(long timeSleep, long timeExternalSleep=0);

  private:
    ConfigApp config;
};

#endif
