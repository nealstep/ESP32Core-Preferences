#pragma once
// this file can be copied into another program to use stored prefs

#ifdef ARDUINO
#include <Arduino.h>

// namespace for preferences
static constexpr const char* const namespace_name = NAMESPACE;

// keys
static constexpr const char* const k_use_serial = "use_serial";
static constexpr const char* const k_serial_speed = "serial_speed";
static constexpr const char* const k_tz_full = "tz_full";
static constexpr const char* const k_wifi_ssid = "wifi_ssid";
static constexpr const char* const k_wifi_password = "wifi_password";
static constexpr const char* const k_ota_password = "ota_password";
static constexpr const char* const k_udp_data_port = "udp_data_port";
static constexpr const char* const k_use_queue = "use_queue";
static constexpr const char* const k_local_queue_size = "local_queue_size";
static constexpr const char* const k_internet_queue_size = "internet_queue_size";
static constexpr const char* const k_use_aes = "use_aes";
static constexpr const char* const k_hex_key = "hex_key";

// bad values
static constexpr uint32_t b_serial_speed = 1;
static constexpr const char* const b_tz_full = "X";
static constexpr const char* const b_wifi_ssid = "X";
static constexpr const char* const b_wifi_password = "X";
static constexpr const char* const b_ota_password = "X";
static constexpr uint16_t b_udp_data_port = 1;
static constexpr uint16_t b_local_queue_size = 1;
static constexpr uint16_t b_internet_queue_size = 1;
static constexpr const char* const b_hex_key = "X";

// sizes (adding one so if stored string is too long, we can detect it)
static constexpr size_t tz_full_size = 128 + 1;
static constexpr size_t wifi_ssid_size = 32 + 1;
static constexpr size_t wifi_password_size = 64 + 1;
static constexpr size_t ota_password_size = 64 + 1;
static constexpr size_t hex_key_size = 65 + 1;

// variables to store values
extern bool use_serial;
extern uint32_t serial_speed;
extern char tz_full[tz_full_size];
extern char wifi_ssid[wifi_ssid_size];
extern char wifi_password[wifi_password_size];
extern char ota_password[ota_password_size];
extern uint16_t udp_data_port;
extern bool use_queue;
extern uint16_t local_queue_size;
extern uint16_t internet_queue_size;
extern bool use_aes;
extern char hex_key[hex_key_size];

#endif  // ARDUINO
