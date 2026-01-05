#include <stdio.h>
#include "wmbus_json.h"

int main(void)
{
    char buffer[2048];
    size_t used;

    gateway_data_t gw = {
        .gateway_id       = "gateway_1234",
        .date             = "1970-01-01",
        .device_type      = "stromleser",
        .interval_minutes = 15,
        .total_readings   = 1,
        .device_count     = 1
    };

    gw.devices[0].media     = "water";
    gw.devices[0].meter     = "waterstarm";
    gw.devices[0].device_id = "stromleser_50898527";
    gw.devices[0].unit      = "m3";
    gw.devices[0].data_count = 1;

    gw.devices[0].data[0] = (meter_data_t){
        "1970-01-01 00:00",
        "1970-01-01 00:00",
        107.752,
        "OK"
    };

    if (serialize_to_json(&gw, buffer, sizeof(buffer), &used) == JSON_OK) {
        printf("%s\n", buffer);
        printf("Bytes used: %zu\n", used);
    }

    return 0;
}

