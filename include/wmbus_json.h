#ifndef WMBUS_JSON_H
#define WMBUS_JSON_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Limits */
#define MAX_DEVICES     4
#define MAX_DATA_POINTS 8

/* Meter data point */
typedef struct {
    const char *timestamp;
    const char *meter_datetime;
    double      total_m3;
    const char *status;
} meter_data_t;

/* Device reading */
typedef struct {
    const char   *media;
    const char   *meter;
    const char   *device_id;
    const char   *unit;
    uint8_t       data_count;
    meter_data_t  data[MAX_DATA_POINTS];
} device_reading_t;

/* Gateway payload */
typedef struct {
    const char        *gateway_id;
    const char        *date;
    const char        *device_type;
    uint16_t           interval_minutes;
    uint16_t           total_readings;
    uint8_t            device_count;
    device_reading_t   devices[MAX_DEVICES];
} gateway_data_t;

/* Serialization status codes */
typedef enum {
    JSON_OK = 0,
    JSON_ERR_BUFFER_TOO_SMALL,
    JSON_ERR_INVALID_ARG
} json_status_t;

/* JSON serialization API */
json_status_t serialize_to_json(
    const gateway_data_t *input,
    char                 *out_buf,
    size_t                buf_size,
    size_t               *bytes_written
);

#ifdef __cplusplus
}
#endif

#endif /* WMBUS_JSON_H */
