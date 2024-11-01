#include <stdio.h>
#include <assert.h>
#include <string.h>

// Enumeration to avoid multiple print statements
typedef enum {
    BATTERY_OK,
    TEMP_OUT_OF_RANGE,
    SOC_OUT_OF_RANGE,
    CHARGE_RATE_OUT_OF_RANGE
} BatterySts_en;

typedef enum {
    NORMAL,
    TOO_LOW,
    TOO_HIGH
} BreachType_en;

typedef struct {
    BatterySts_en status;
    BreachType_en breachType;
} BatteryCheckResult_st;

// Function to check battery conditions
BatterySts_en batteryIsOk(float temperature, float soc, float chargeRate)
{
    // Check temperature
    if (temperature < 0) {
        return TEMP_OUT_OF_RANGE;  // Too low
    }
    if (temperature > 45) {
        return TEMP_OUT_OF_RANGE;  // Too high
    }

    // Check SOC
    if (soc < 20) {
        return SOC_OUT_OF_RANGE;  // Too low
    }
    if (soc > 80) {
        return SOC_OUT_OF_RANGE;  // Too high
    }

    // Check charge rate
    if (chargeRate > 0.8) {
        return CHARGE_RATE_OUT_OF_RANGE;  // Too high
    }

    return BATTERY_OK;  // If all checks passed
}

int main() 
{
    assert(batteryIsOk(-30, 70, 0.7) == TEMP_OUT_OF_RANGE && "Test case for low temperature failed");
    assert(batteryIsOk(40, 10, 0) == SOC_OUT_OF_RANGE && "Test case for low SOC failed");
    assert(batteryIsOk(25, 70, 0.9) == CHARGE_RATE_OUT_OF_RANGE && "Test case for high charge rate failed");
    assert(batteryIsOk(20, 50, 0.5) == BATTERY_OK && "Test case for normal battery failed");

    printf("All tests passed!\n");
    return 0;
}
