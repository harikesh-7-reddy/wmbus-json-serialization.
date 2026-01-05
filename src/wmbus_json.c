#include "wmbus_json.h"
#include <stdio.h>
#include <stdarg.h>

static int append(char **buf, size_t *remaining, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    int written = vsnprintf(*buf, *remaining, fmt, args);

    va_end(args);

    if (written < 0 || (size_t)written >= *remaining) {
        return -1;
    }

    *buf += written;
    *remaining -= written;
    return 0;
}

json_status_t serialize_to_json(
    const gateway_data_t *in,
    char *out,
    size_t size,
    size_t *used
)
{
    if (!in || !out || size == 0) {
        return JSON_ERR_INVALID_ARG;
    }

    char *ptr = out;
    size_t rem = size;

    if (append(&ptr, &rem, "[{") < 0)
        return JSON_ERR_BUFFER_TOO_SMALL;

    if (append(&ptr, &rem,
        "\"gatewayId\":\"%s\","
        "\"date\":\"%s\","
        "\"deviceType\":\"%s\","
        "\"interval_minutes\":%u,"
        "\"total_readings\":%u,",
        in->gateway_id,
        in->date,
        in->device_type,
        in->interval_minutes,
        in->total_readings) < 0)
        return JSON_ERR_BUFFER_TOO_SMALL;

    if (append(&ptr, &rem,
        "\"values\":{\"device_count\":%u,\"readings\":[",
        in->device_count) < 0)
        return JSON_ERR_BUFFER_TOO_SMALL;

    for (uint8_t i = 0; i < in->device_count; i++) {
        const device_reading_t *d = &in->devices[i];

        if (append(&ptr, &rem,
            "{\"media\":\"%s\",\"meter\":\"%s\","
            "\"deviceId\":\"%s\",\"unit\":\"%s\",\"data\":[",
            d->media, d->meter, d->device_id, d->unit) < 0)
            return JSON_ERR_BUFFER_TOO_SMALL;

        for (uint8_t j = 0; j < d->data_count; j++) {
            const meter_data_t *m = &d->data[j];

            if (append(&ptr, &rem,
                "{\"timestamp\":\"%s\","
                "\"meter_datetime\":\"%s\","
                "\"total_m3\":%.3f,"
                "\"status\":\"%s\"}%s",
                m->timestamp,
                m->meter_datetime,
                m->total_m3,
                m->status,
                (j + 1 < d->data_count) ? "," : "") < 0)
                return JSON_ERR_BUFFER_TOO_SMALL;
        }

        if (append(&ptr, &rem, "]}%s",
            (i + 1 < in->device_count) ? "," : "") < 0)
            return JSON_ERR_BUFFER_TOO_SMALL;
    }

    if (append(&ptr, &rem, "]}}]") < 0)
        return JSON_ERR_BUFFER_TOO_SMALL;

    if (used) {
        *used = size - rem;
    }

    return JSON_OK;
}
