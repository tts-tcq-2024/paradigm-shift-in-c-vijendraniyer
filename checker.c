#include <stdio.h>
#include "checker.h"

// Strategy implementation for temperature check
/**
 * @brief Checks if the temperature is within the acceptable range.
 * 
 * @param temperature The temperature to check.
 * @param breachType Pointer to store the type of breach if applicable.
 * @param warning Pointer to indicate if a warning is triggered.
 * @return BatterySts_en The status indicating if the temperature is OK or out of range.
 */
BatterySts_en checkTemperature(float temperature, BreachType_en *breachType, int *warning) {
    if (temperature < 0) {
        *breachType = TOO_LOW; // Set breach type to TOO_LOW
        *warning = 1;          // Warning enabled
        return TEMP_OUT_OF_RANGE;
    } else if (temperature > 45) {
        *breachType = TOO_HIGH; // Set breach type to TOO_HIGH
        *warning = 1;           // Warning enabled
        return TEMP_OUT_OF_RANGE;
    }
    *warning = 0; // No warning
    return BATTERY_OK;
}

// Strategy implementation for state of charge (SoC) check
/**
 * @brief Checks if the state of charge is within the acceptable range.
 * 
 * @param soc The state of charge to check.
 * @param breachType Pointer to store the type of breach if applicable.
 * @param warning Pointer to indicate if a warning is triggered.
 * @return BatterySts_en The status indicating if the SoC is OK or out of range.
 */
BatterySts_en checkSoc(float soc, BreachType_en *breachType, int *warning) {
    if (soc < 20) {
        *breachType = TOO_LOW; // Set breach type to TOO_LOW
        *warning = 1;          // Warning enabled
        return SOC_OUT_OF_RANGE;
    } else if (soc > 80) {
        *breachType = TOO_HIGH; // Set breach type to TOO_HIGH
        *warning = 1;           // Warning enabled
        return SOC_OUT_OF_RANGE;
    }
    *warning = 0; // No warning
    return BATTERY_OK;
}

// Strategy implementation for charge rate check
/**
 * @brief Checks if the charge rate is within the acceptable range.
 * 
 * @param chargeRate The charge rate to check.
 * @param breachType Pointer to store the type of breach if applicable.
 * @param warning Pointer to indicate if a warning is triggered.
 * @return BatterySts_en The status indicating if the charge rate is OK or out of range.
 */
BatterySts_en checkChargeRate(float chargeRate, BreachType_en *breachType, int *warning) {
    if (chargeRate > 0.8) {
        *breachType = TOO_HIGH; // Set breach type to TOO_HIGH
        *warning = 1;           // Warning enabled
        return CHARGE_RATE_OUT_OF_RANGE;
    }
    *warning = 0; // No warning
    return BATTERY_OK;
}

// Function to check the overall battery status using different strategies
/**
 * @brief Checks the battery status using temperature, SoC, and charge rate checks.
 * 
 * @param temperature The temperature of the battery.
 * @param soc The state of charge of the battery.
 * @param chargeRate The charge rate of the battery.
 * @return BatterySts_en The overall status of the battery after performing all checks.
 */
BatterySts_en batteryIsOk(float temperature, float soc, float chargeRate) {
    BatteryCheckStrategy tempStrategy = {checkTemperature}; // Strategy for temperature
    BatteryCheckStrategy socStrategy = {checkSoc};         // Strategy for SoC
    BatteryCheckStrategy chargeRateStrategy = {checkChargeRate}; // Strategy for charge rate

    BreachType_en breachType; // Variable to store the type of breach
    int warning = 0;          // Variable to indicate if a warning is triggered

    // Check temperature
    BatterySts_en status = tempStrategy.check(temperature, &breachType, &warning);
    if (status != BATTERY_OK) {
        return status; // Return if temperature is out of range
    }

    // Check SoC
    status = socStrategy.check(soc, &breachType, &warning);
    if (status != BATTERY_OK) {
        return status; // Return if SoC is out of range
    }

    // Check charge rate
    return chargeRateStrategy.check(chargeRate, &breachType, &warning); // Return status of charge rate check
}
