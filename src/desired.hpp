#pragma once

#ifdef ARDUINO
#include <Arduino.h>

// desired values to save
static constexpr bool c_use_serial = USE_SERIAL;
static constexpr uint32_t c_serial_speed = SERIAL_SPEED;
static constexpr const char* const c_tz_full = TZ_FULL;
static constexpr const char* const c_wifi_ssid = WIFI_SSID;
static constexpr const char* const c_wifi_password = WIFI_PASSWORD;
static constexpr const char* const c_ota_password = OTA_PASSWORD;
static constexpr uint16_t c_udp_data_port = UDP_DATA_PORT;
static constexpr bool c_use_queue = USE_QUEUE;
static constexpr uint16_t c_local_queue_size = LOCAL_QUEUE_SIZE;
static constexpr uint16_t c_internet_queue_size = INTERNET_QUEUE_SIZE;
static constexpr bool c_use_aes = USE_AES;
static constexpr char c_hex_key[] = HEX_KEY;

#endif  // ARDUINO
