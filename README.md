# JSON Serialization Library for Embedded Smart Meter Gateways

## Project Overview
This project implements a small, dependency-free JSON serialization library intended for embedded firmware used in smart-meter / w-M-Bus gateway systems.

The library converts structured meter data into a strictly defined JSON format suitable for gateway-to-backend communication.

w-M-Bus radio communication, OMS, encryption, and real meter interaction are intentionally out of scope.

---

## Platform & Programming Language

- Programming Language: C (C99)
- Target Platform: Embedded systems (STM32 / ESP32 / generic MCU)

### Justification
C is widely used in embedded firmware due to its deterministic memory usage, low overhead, and portability across microcontroller platforms. The implementation avoids dynamic memory allocation and external dependencies, making it suitable for constrained systems.

---

## Project Structure
/
├── include/
│ └── wmbus_json.h
├── src/
│ └── wmbus_json.c
├── examples/
│ └── demo.c
├── README.md
└── LICENSE (optional)

---

## Data Model

The library uses fixed-size structures to ensure predictable memory usage.

- Gateway metadata
- Device readings
- Meter data points

All limits (maximum devices and data points) are defined at compile time.

---

## Public API
json_status_t serialize_to_json(
const gateway_data_t *input,
char *output_buffer,
size_t buffer_size,
size_t *bytes_written
);

### API Characteristics
- Caller provides output buffer
- No dynamic memory allocation
- Buffer overflow protection
- Clear error codes for failure handling

---

## JSON Format Compliance

The generated JSON strictly follows the required structure:
- Field names are unchanged
- No additional fields
- Numeric values are not serialized as strings
- The outermost element is always a JSON array

---

## Example JSON Output
[
{
"gatewayId": "gateway_1234",
"date": "1970-01-01",
"deviceType": "stromleser",
"interval_minutes": 15,
"total_readings": 1,
"values": {
"device_count": 1,
"readings": [
{
"media": "water",
"meter": "waterstarm",
"deviceId": "stromleser_50898527",
"unit": "m3",
"data": [
{
"timestamp": "1970-01-01 00:00",
"meter_datetime": "1970-01-01 00:00",
"total_m3": 107.752,
"status": "OK"
}
]
}
]
}
}
]

---

## Demo Application

The demo application:
1. Creates sample gateway and device data
2. Calls the serialization function
3. Prints the generated JSON output

This demonstrates correct usage of the library API.

---

## Design Decisions & Assumptions

- Fixed maximum sizes for devices and data points
- All strings are null-terminated UTF-8
- Floating-point values are formatted with three decimal places
- Time formatting is handled outside the library

---

## Possible Extensions

- Support for multiple gateway entries
- Minified JSON output option
- Integer-only build for MCUs without FPU
- Unit tests and static analysis integration

---

## Conclusion

This project demonstrates a clean, embedded-oriented approach to JSON serialization with strict format compliance, deterministic memory usage, and a clear public API suitable for smart-meter gateway firmware.
