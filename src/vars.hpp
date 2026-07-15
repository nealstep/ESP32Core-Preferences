#pragma once
// this file can be copied into another program to use stored prefs

#ifdef ARDUINO
#include <Arduino.h>

#include "prefs.hpp"

// variables to store values
bool use_serial;
uint32_t serial_speed;
char tz_full[tz_full_size];
char wifi_ssid[wifi_ssid_size];
char wifi_password[wifi_password_size];
char ota_password[ota_password_size];
uint16_t udp_data_port;
bool use_queue;
uint16_t local_queue_size;
uint16_t internet_queue_size;
bool use_aes;
char hex_key[hex_key_size];

#endif  // ARDUINO