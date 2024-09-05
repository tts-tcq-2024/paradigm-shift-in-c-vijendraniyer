#include <stdio.h>
#include <assert.h>

// Function to check if a value is within a specified range
int isInRange(float value, float low, float high) {
    return value >= low && value <= high;
}

// Pure functions for battery checks
int isTemperatureOk(float temperature) {
    return isInRange(temperature, 0, 45);
}

int isSocOk(float soc) {
    return isInRange(soc, 20, 80);
}

int isChargeRateOk(float chargeRate) {
    return chargeRate <= 0.8;
}

// Function to determine battery status and print appropriate messages
int batteryIsOk(float temperature, float soc, float chargeRate) {
    int isOk = 1; // Assume battery is ok initially
    
    if (!isTemperatureOk(temperature)) {
        printf("Temperature out of range!\n");
        isOk = 0;
    }
    if (!isSocOk(soc)) {
        printf("State of Charge out of range!\n");
        isOk = 0;
    }
    if (!isChargeRateOk(chargeRate)) {
        printf("Charge Rate out of range!\n");
        isOk = 0;
    }

    return isOk;
}
int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
