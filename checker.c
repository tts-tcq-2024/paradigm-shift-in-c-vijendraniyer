#include <stdio.h>
#include "checker.h"

// Strategy implementations
BatterySts_en checkTemperature(float temperature, BreachType_en *breachType, int *warning) {
    if (temperature < 0) {
        *breachType = TOO_LOW;
        *warning = 1; // Warning enabled
        return TEMP_OUT_OF_RANGE;
    } else if (temperature > 45) {
        *breachType = TOO_HIGH;
        *warning = 1; // Warning enabled
        return TEMP_OUT_OF_RANGE;
    }
    *warning = 0; // No warning
    return BATTERY_OK;
}

BatterySts_en checkSoc(float soc, BreachType_en *breachType, int *warning) {
    if (soc < 20) {
        *breachType = TOO_LOW;
        *warning = 1; // Warning enabled
        return SOC_OUT_OF_RANGE;
    } else if (soc > 80) {
        *breachType = TOO_HIGH;
        *warning = 1; // Warning enabled
        return SOC_OUT_OF_RANGE;
    }
    *warning = 0; // No warning
    return BATTERY_OK;
}

BatterySts_en checkChargeRate(float chargeRate, BreachType_en *breachType, int *warning) {
    if (chargeRate > 0.8) {
        *breachType = TOO_HIGH;
        *warning = 1; // Warning enabled
        return CHARGE_RATE_OUT_OF_RANGE;
    }
    *warning = 0; // No warning
    return BATTERY_OK;
}

// Function to check battery status using strategies
BatterySts_en batteryIsOk(float temperature, float soc, float chargeRate) {
    BatteryCheckStrategy tempStrategy = {checkTemperature};
    BatteryCheckStrategy socStrategy = {checkSoc};
    BatteryCheckStrategy chargeRateStrategy = {checkChargeRate};

    BreachType_en breachType;
    int warning = 0;

    BatterySts_en status = tempStrategy.check(temperature, &breachType, &warning);
    if (status != BATTERY_OK) {
        return status;
    }

    status = socStrategy.check(soc, &breachType, &warning);
    if (status != BATTERY_OK) {
        return status;
    }

    return chargeRateStrategy.check(chargeRate, &breachType, &warning);
}
