#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

// Function to check if a value is within a specified range
bool isInRange(float value, float low, float high) {
    return value >= low && value <= high;
}

// Pure functions for battery checks
bool isTemperatureOk(float temperature) {
    return isInRange(temperature, 0, 45);
}

bool isSocOk(float soc) {
    return isInRange(soc, 20, 80);
}

bool isChargeRateOk(float chargeRate) {
    return chargeRate <= 0.8;
}

// Helper function to check and print status
bool checkAndPrint(bool condition, const char* message) {
    if (!condition) {
        printf("%s\n", message);
    }
    return condition;
}

// Function to determine battery status
bool batteryIsOk(float temperature, float soc, float chargeRate) {
    bool isTemperatureValid = checkAndPrint(isTemperatureOk(temperature), "Temperature out of range!");
    bool isSocValid = checkAndPrint(isSocOk(soc), "State of Charge out of range!");
    bool isChargeRateValid = checkAndPrint(isChargeRateOk(chargeRate), "Charge Rate out of range!");

    return isTemperatureValid && isSocValid && isChargeRateValid;
}

int main() {
    assert(batteryIsOk(25, 70, 0.7)); // Should pass
    assert(!batteryIsOk(50, 85, 0));  // Should fail
    assert(!batteryIsOk(30, 15, 0.5)); // Should fail
    assert(!batteryIsOk(10, 75, 0.9)); // Should fail
    assert(batteryIsOk(45, 20, 0.8)); // Upper limits, should pass
}
