#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

// Define constants for temperature, state of charge, and charge rate limits
#define MIN_TEMP 0.0f
#define MAX_TEMP 45.0f
#define MIN_SOC 20.0f
#define MAX_SOC 80.0f
#define MAX_CHARGE_RATE 0.8f
#define TOLERANCE 0.0001f // Tolerance for floating-point comparison

// Function declarations (prototypes)
bool isInRange(float value, float low, float high);
bool isTemperatureOk(float temperature);
bool isSocOk(float soc);
bool isChargeRateOk(float chargeRate);
bool batteryIsOk(float temperature, float soc, float chargeRate);

/**
 * @brief Check if a value is within a specified range.
 *
 * @param value The value to check.
 * @param low The lower bound of the range.
 * @param high The upper bound of the range.
 * @return true if value is within the range [low, high], false otherwise.
 */
bool isInRange(float value, float low, float high) {
    return value >= low && value <= high;
}

/**
 * @brief Check if the battery temperature is within a safe range.
 *
 * @param temperature The current temperature of the battery.
 * @return true if temperature is between MIN_TEMP and MAX_TEMP, false otherwise.
 */
bool isTemperatureOk(float temperature) {
    return isInRange(temperature, MIN_TEMP, MAX_TEMP);
}

/**
 * @brief Check if the state of charge (SoC) is within a safe range.
 *
 * @param soc The current state of charge of the battery.
 * @return true if SoC is between MIN_SOC and MAX_SOC, false otherwise.
 */
bool isSocOk(float soc) {
    return isInRange(soc, MIN_SOC, MAX_SOC);
}

/**
 * @brief Check if the charge rate is acceptable.
 *
 * @param chargeRate The current charge rate of the battery.
 * @return true if chargeRate is less than or equal to MAX_CHARGE_RATE (with a small tolerance).
 */
bool isChargeRateOk(float chargeRate) {
    return chargeRate <= (MAX_CHARGE_RATE + TOLERANCE);
}

/**
 * @brief Determine overall battery status.
 *
 * @param temperature The current temperature of the battery.
 * @param soc The current state of charge of the battery.
 * @param chargeRate The current charge rate of the battery.
 * @return true if all checks pass, false if any check fails.
 */
bool batteryIsOk(float temperature, float soc, float chargeRate) {
    return isTemperatureOk(temperature) && isSocOk(soc) && isChargeRateOk(chargeRate);
}

int main() {
    // Run assertions to verify battery conditions
    assert(batteryIsOk(25.0f, 70.0f, 0.7f));  // Should pass: all values are within acceptable ranges
    assert(!batteryIsOk(50.0f, 85.0f, 0.0f));  // Should fail: temperature and SoC out of range
    assert(!batteryIsOk(30.0f, 15.0f, 0.5f));  // Should fail: SoC out of range
    assert(!batteryIsOk(10.0f, 75.0f, 0.9f));  // Should fail: charge rate out of range
    assert(batteryIsOk(45.0f, 20.0f, 0.8f));   // Should pass: all values are within acceptable ranges

    // If all assertions pass, print a success message
    printf("All assertions passed.\n");
    return 0; // Exit the program
}
