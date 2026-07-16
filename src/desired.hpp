#pragma once

#ifdef ARDUINO
#include <Arduino.h>

#include "constants.hpp"

namespace Desired {
// desired values to save
static constexpr bool use_serial = USE_SERIAL;
static constexpr uint32_t serial_speed = SERIAL_SPEED;
static constexpr const char* const tz_full = TZ_FULL;
static constexpr const char* const wifi_ssid = WIFI_SSID;
static constexpr const char* const wifi_password = WIFI_PASSWORD;
static constexpr const char* const ota_password = OTA_PASSWORD;
static constexpr uint16_t udp_data_port = UDP_DATA_PORT;
static constexpr bool use_queue = USE_QUEUE;
static constexpr uint16_t local_queue_size = LOCAL_QUEUE_SIZE;
static constexpr uint16_t internet_queue_size = INTERNET_QUEUE_SIZE;
static constexpr bool use_aes = USE_AES;
static constexpr char hex_key[] = HEX_KEY;
static constexpr uint32_t keep_alive_int = 15 * Constants::sec_ms;
}  // namespace Desired

#endif  // ARDUINO
