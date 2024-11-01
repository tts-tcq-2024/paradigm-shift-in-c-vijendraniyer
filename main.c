#include <stdio.h>
#include <assert.h>
#include "checker.h"

int main() {
    assert(batteryIsOk(-30, 70, 0.7) == TEMP_OUT_OF_RANGE);
    assert(batteryIsOk(40, 10, 0) == SOC_OUT_OF_RANGE);
    assert(batteryIsOk(25, 70, 0.9) == CHARGE_RATE_OUT_OF_RANGE);
    assert(batteryIsOk(20, 50, 0.5) == BATTERY_OK);

    printf("All tests passed!\n");
    return 0;
}
