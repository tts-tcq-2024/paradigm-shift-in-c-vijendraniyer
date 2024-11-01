#include <stdio.h>
#include <assert.h>
#include "checker.h"

int main() {
    // Test cases to validate the battery checks
    assert(batteryIsOk(-30, 70, 0.7) == TEMP_OUT_OF_RANGE); // Test low temperature
    assert(batteryIsOk(40, 10, 0) == SOC_OUT_OF_RANGE);     // Test low SoC
    assert(batteryIsOk(25, 70, 0.9) == CHARGE_RATE_OUT_OF_RANGE); // Test high charge rate
    assert(batteryIsOk(20, 50, 0.5) == BATTERY_OK);         // Test normal conditions

    printf("All tests passed!\n"); // Print success message if all tests pass
    return 0; // Return success
}
