#include <Arduino.h>
#include <Preferences.h>

#include "desired.hpp"
#include "prefs.hpp"
#include "vars.hpp"

Preferences preferences;

// update values
bool update = true;

// startup delay
static constexpr uint32_t startup_delay = 3000;
static constexpr uint32_t medium_delay = 500;

// handle display and optional setting of various types
void handle_bool(const char* key, bool& value, bool desired_value) {
    Serial.println();
    Serial.printf("%s (desired): %u\n", key, desired_value);
    if (preferences.isKey(key)) {
        value = preferences.getBool(key);
        Serial.printf("%s: %u\n", key, value);
    } else {
        Serial.printf("%s: not found\n", key);
        value = !desired_value;
    }
    if (value != desired_value) {
        if (update) {
            size_t len = preferences.putBool(key, desired_value);
            if (len == 0) {
                Serial.printf("%s: update failed\n", key);
            } else {
                Serial.printf("%s: updated to %u\n", key, desired_value);
            }
        } else {
            Serial.printf("%s: NOT updating from %u to %u\n", key, value,
                          desired_value);
        }
    } else {
        Serial.printf("%s: already set to desired value\n", key);
    }
}

void handle_u16(const char* key, uint16_t& value, uint16_t desired_value,
                uint16_t bad_value) {
    Serial.println();
    Serial.printf("%s (desired): %u\n", key, desired_value);
    if (preferences.isKey(key)) {
        value = preferences.getUShort(key, bad_value);
        if (value == bad_value) {
            Serial.printf("%s: unset\n", key);
        } else {
            Serial.printf("%s: %u\n", key, value);
        }
    } else {
        Serial.printf("%s: not found\n", key);
        value = bad_value;
    }
    if (value != desired_value) {
        if (update) {
            size_t len = preferences.putUShort(key, desired_value);
            if (len == 0) {
                Serial.printf("%s: update failed\n", key);
            } else {
                Serial.printf("%s: updated to %u\n", key, desired_value);
            }
        } else {
            Serial.printf("%s: NOT updating from %u to %u\n", key, value,
                          desired_value);
        }
    } else {
        Serial.printf("%s: already set to desired value\n", key);
    }
}

void handle_u32(const char* key, uint32_t& value, uint32_t desired_value,
                uint32_t bad_value) {
    Serial.println();
    Serial.printf("%s (desired): %u\n", key, desired_value);
    if (preferences.isKey(key)) {
        value = preferences.getUInt(key, bad_value);
        if (value == bad_value) {
            Serial.printf("%s: unset\n", key);
        } else {
            Serial.printf("%s: %u\n", key, value);
        }
    } else {
        Serial.printf("%s: not found\n", key);
        value = bad_value;
    }
    if (value != desired_value) {
        if (update) {
            size_t len = preferences.putUInt(key, desired_value);
            if (len == 0) {
                Serial.printf("%s: update failed\n", key);
            } else {
                Serial.printf("%s: updated to %u\n", key, desired_value);
            }
        } else {
            Serial.printf("%s: NOT updating from %u to %u\n", key, value,
                          desired_value);
        }
    } else {
        Serial.printf("%s: already set to desired value\n", key);
    }
}

void handle_chars(const char* key, char* value, size_t value_size,
                  const char* desired_value, const char* bad_value) {
    Serial.println();
    Serial.printf("%s (desired): %s\n", key, desired_value);
    if (preferences.isKey(key)) {
        size_t len = preferences.getString(key, value, value_size);
        if (len == 0) {
            Serial.printf("%s: unset\n", key);
        } else if (len >= value_size - 1) {
            Serial.printf("%s: too long\n", key);
        } else {
            Serial.printf("%s: %s\n", key, value);
        }
    } else {
        Serial.printf("%s: not found\n", key);
        strcpy(value, bad_value);
    }
    if (strcmp(value, desired_value) != 0) {
        if (update) {
            size_t len = preferences.putString(key, desired_value);
            if (len == 0) {
                Serial.printf("%s: update failed\n", key);
            } else {
                Serial.printf("%s: updated to %s\n", key, desired_value);
            }
        } else {
            Serial.printf("%s: NOT updating from %s to %s\n", key, value,
                          desired_value);
        }
    } else {
        Serial.printf("%s: already set to desired value\n", key);
    }
}

void setup() {
    Serial.begin(serial_speed);
    delay(startup_delay);
    Serial.println();
    Serial.println("Preferences Starting");

    preferences.begin(namespace_name, false);

    handle_bool(k_use_serial, use_serial, c_use_serial);
    handle_u32(k_serial_speed, serial_speed, c_serial_speed, b_serial_speed);
    handle_chars(k_tz_full, tz_full, sizeof(tz_full), c_tz_full, b_tz_full);
    handle_chars(k_wifi_ssid, wifi_ssid, sizeof(wifi_ssid), c_wifi_ssid,
                 b_wifi_ssid);
    handle_chars(k_wifi_password, wifi_password, sizeof(wifi_password),
                 c_wifi_password, b_wifi_password);
    handle_chars(k_ota_password, ota_password, sizeof(ota_password),
                 c_ota_password, b_ota_password);
    handle_u16(k_udp_data_port, udp_data_port, c_udp_data_port,
               b_udp_data_port);
    handle_bool(k_use_queue, use_queue, c_use_queue);
    handle_u16(k_local_queue_size, local_queue_size, c_local_queue_size,
               b_local_queue_size);
    handle_u16(k_internet_queue_size, internet_queue_size,
               c_internet_queue_size, b_internet_queue_size);
    handle_bool(k_use_aes, use_aes, c_use_aes);
    handle_chars(k_hex_key, hex_key, sizeof(hex_key), c_hex_key, b_hex_key);

    Serial.println();
    Serial.println("Preferences Finished");
    preferences.end();
}

void loop() { delay(medium_delay); }
