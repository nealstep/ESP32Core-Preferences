#pragma once

#ifdef ARDUINO
#include <Arduino.h>

#include "constants.hpp"

namespace Desired {
static constexpr bool use_serial = USE_SERIAL;
static constexpr uint32_t serial_speed = SERIAL_SPEED;
static constexpr const char* const chip_name = CHIP_NAME;
static constexpr uint32_t keep_alive_int = KEEP_ALIVE_INT;
static constexpr uint32_t check_internet_int = CHECK_INTERNET_INT;
static constexpr const char* const tz_full = TZ_FULL;
static constexpr const char* const wifi_ssid = WIFI_SSID;
static constexpr const char* const wifi_password = WIFI_PASSWORD;
static constexpr const char* const ota_password = OTA_PASSWORD;
static constexpr uint16_t udp_data_port = UDP_DATA_PORT;
static constexpr bool use_queue = USE_QUEUE;
static constexpr uint16_t local_queue_size = LOCAL_QUEUE_SIZE;
static constexpr uint16_t internet_queue_size = INTERNET_QUEUE_SIZE;
static constexpr bool use_aes = USE_AES;
static constexpr const char* const encrypt_local = ENCRYPT_LOCAL;
static constexpr char hex_key[] = HEX_KEY;
static constexpr const char* const remote_host = REMOTE_HOST;
}  // namespace Desired

#endif  // ARDUINO
