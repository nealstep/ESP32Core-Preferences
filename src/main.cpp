#include <Arduino.h>
#include <Preferences.h>

Preferences preferences;

// update values
bool update = true;

// startup delay
static constexpr uint32_t startup_delay = 3000;
static constexpr uint32_t medium_delay = 500;

// namespace for preferences
static constexpr const char* const namespace_name = NAMESPACE;

// values to save
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

// bad_values
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

    handle_u32("serial_speed", serial_speed, c_serial_speed, b_serial_speed);
    handle_chars("tz_full", tz_full, sizeof(tz_full), c_tz_full, b_tz_full);
    handle_chars("wifi_ssid", wifi_ssid, sizeof(wifi_ssid), c_wifi_ssid,
                 b_wifi_ssid);
    handle_chars("wifi_password", wifi_password, sizeof(wifi_password),
                 c_wifi_password, b_wifi_password);
    handle_chars("ota_password", ota_password, sizeof(ota_password),
                 c_ota_password, b_ota_password);
    handle_u16("udp_data_port", udp_data_port, c_udp_data_port,
               b_udp_data_port);
    handle_bool("use_queue", use_queue, c_use_queue);
    handle_u16("local_queue_size", local_queue_size, c_local_queue_size,
               b_local_queue_size);
    handle_u16("internet_queue_size", internet_queue_size,
               c_internet_queue_size, b_internet_queue_size);
    handle_bool("use_aes", use_aes, c_use_aes);
    handle_chars("hex_key", hex_key, sizeof(hex_key), c_hex_key, b_hex_key);

    Serial.println();
    Serial.println("Preferences Finished");
    preferences.end();
}

void loop() { delay(medium_delay); }
