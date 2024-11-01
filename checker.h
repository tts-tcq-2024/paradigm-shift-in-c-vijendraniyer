#ifndef CHECKER_H
#define CHECKER_H

// Enumeration for battery status and breach type
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

// Strategy interface for battery checks
typedef struct BatteryCheckStrategy {
    BatterySts_en (*check)(float value, BreachType_en *breachType, int *warning);
} BatteryCheckStrategy;

// Function prototypes
BatterySts_en batteryIsOk(float temperature, float soc, float chargeRate);

#endif // CHECKER_H
