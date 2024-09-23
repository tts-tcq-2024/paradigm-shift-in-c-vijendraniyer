#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

// Function to check if a value is within a specified range
bool isInRange(float value, float low, float high) {
    return value >= low && value <= high;
}

// Pure functions for battery checks
bool isTemperatureOk(float temperature) {
    return isInRange(temperature, 0, 45); // Check temperature range
}

bool isSocOk(float soc) {
    return isInRange(soc, 20, 80); // Check SoC range
}

bool isChargeRateOk(float chargeRate) {
    return chargeRate <= 0.8; // Check charge rate
}

// Helper function to check and print status
bool checkAndPrint(bool condition, const char* message, float value) {
    if (!condition) {
        printf("%s: %f\n", message, value); // Print message if condition fails
    }
    return condition;
}

// Function to determine battery status
bool batteryIsOk(float temperature, float soc, float chargeRate) {
    bool isTemperatureValid = checkAndPrint(isTemperatureOk(temperature), "Temperature out of range!", temperature);
    bool isSocValid = checkAndPrint(isSocOk(soc), "State of Charge out of range!", soc);
    bool isChargeRateValid = checkAndPrint(isChargeRateOk(chargeRate), "Charge Rate out of range!", chargeRate);

    return isTemperatureValid && isSocValid && isChargeRateValid; // Return overall validity
}

int main() {
    // Individual assertions for each check
    assert(batteryIsOk(25, 70, 0.7));  // Should pass
    assert(!batteryIsOk(50, 85, 0));   // Should fail
    assert(!batteryIsOk(30, 15, 0.5));  // Should fail
    assert(!batteryIsOk(10, 75, 0.9));  // Should fail
    assert(batteryIsOk(45, 20, 0.8));   // Should pass

    // Assert individual conditions
    assert(isTemperatureOk(45));  // Should pass
    assert(isSocOk(20));          // Should pass
    assert(isChargeRateOk(0.8));  // Should pass

    printf("All assertions passed.\n");
    return 0;
}
