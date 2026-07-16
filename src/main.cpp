#include <Arduino.h>

#include "desired.hpp"
#include "e32c_log.hpp"
#include "prefs.hpp"
#include "utils.hpp"

static constexpr const char* const prefs_name = PREFS_NAME;

// update values
bool update = true;

// startup delay
static constexpr uint32_t startup_delay = 3000;
static constexpr uint32_t medium_delay = 500;

// handle display and optional setting of various types
bool handle_bool(const char* key, bool& value, bool desired_value) {
    LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefDesS, key,
          b2s(desired_value));
    Log::Err err = prefs.get_bool(key, value);
    if (err == Log::Err::NoError) {
        LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefReadS, key,
              b2s(value));
    } else {
        LOG_E(Log::Uni::Main, err, key);
        value = !desired_value;
    }
    if (value != desired_value) {
        if (update) {
            err = prefs.set_bool(key, desired_value);
            if (err == Log::Err::NoError) {
                LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefUpdS, key,
                      b2s(desired_value));
            } else {
                LOG_E(Log::Uni::Main, err, key);
            }
        } else {
            LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefNotUpdS, key,
                  b2s(desired_value));
        }
    } else {
        LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefAlready, key);
        return true;
    }
    return false;
}

bool handle_u16(const char* key, uint16_t& value, uint16_t desired_value,
                uint16_t bad_value) {
    LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefDesU, key,
          desired_value);
    Log::Err err = prefs.get_u16(key, value, bad_value);
    if (err == Log::Err::NoError) {
        LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefReadU, key, value);
    } else {
        LOG_E(Log::Uni::Main, err, key);
    }
    if (value != desired_value) {
        if (update) {
            err = prefs.set_u16(key, desired_value);
            if (err == Log::Err::NoError) {
                LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefUpdU, key,
                      desired_value);
            } else {
                LOG_E(Log::Uni::Main, err, key);
            }
        } else {
            LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefNotUpdU, key,
                  desired_value);
        }
    } else {
        LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefAlready, key);
        return true;
    }
    return false;
}

bool handle_u32(const char* key, uint32_t& value, uint32_t desired_value,
                uint32_t bad_value) {
    LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefDesU, key,
          desired_value);
    Log::Err err = prefs.get_u32(key, value, bad_value);
    if (err == Log::Err::NoError) {
        LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefReadU, key, value);
    } else {
        LOG_E(Log::Uni::Main, err, key);
    }
    if (value != desired_value) {
        if (update) {
            err = prefs.set_u32(key, desired_value);
            if (err == Log::Err::NoError) {
                LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefUpdU, key,
                      desired_value);
            } else {
                LOG_E(Log::Uni::Main, err, key);
            }
        } else {
            LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefNotUpdU, key,
                  desired_value);
        }
    } else {
        LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefAlready, key);
        return true;
    }
    return false;
}

bool handle_chars(const char* key, char* value, size_t value_size,
                  const char* desired_value, const char* bad_value) {
    LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefDesS, key,
          desired_value);
    Log::Err err = prefs.get_chars(key, value, value_size, bad_value);
    if (err == Log::Err::NoError) {
        LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefReadS, key, value);
    } else {
        LOG_E(Log::Uni::Main, err, key);
    }
    if (strncmp(value, desired_value, strlen(value)) != 0) {
        if (update) {
            err = prefs.set_chars(key, desired_value);
            if (err == Log::Err::NoError) {
                LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefUpdS, key,
                      desired_value);
            } else {
                LOG_E(Log::Uni::Main, err, key);
            }
        } else {
            LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefNotUpdU, key,
                  desired_value);
        }
    } else {
        LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::PrefAlready, key);
        return true;
    }
    return false;
}

void setup() {
    Serial.begin(Desired::serial_speed);
    delay(startup_delay);
    LOG_N(Log::Uni::Main, Log::Sev::All, Log::Note::Starting);
    Log::Err err = prefs.open(prefs_name, !update);
    if (err != Log::Err::NoError) {
        LOG_E(Log::Uni::Main, err);
        die();
    }

    bool good;
    good = handle_bool(Prefs::Keys::use_serial, prefs.use_serial,
                       Desired::use_serial);
    good &= handle_u32(Prefs::Keys::serial_speed, prefs.serial_speed,
                       Desired::serial_speed, Prefs::BadValues::serial_speed);
    good &=
        handle_u32(Prefs::Keys::keep_alive_int, prefs.keep_alive_int,
                   Desired::keep_alive_int, Prefs::BadValues::keep_alive_int);
    good &=
        handle_chars(Prefs::Keys::tz_full, prefs.tz_full, Prefs::Sizes::tz_full,
                     Desired::tz_full, Prefs::BadValues::tz_full);
    good &= handle_chars(Prefs::Keys::wifi_ssid, prefs.wifi_ssid,
                         Prefs::Sizes::wifi_ssid, Desired::wifi_ssid,
                         Prefs::BadValues::wifi_ssid);
    good &= handle_chars(Prefs::Keys::wifi_password, prefs.wifi_password,
                         Prefs::Sizes::wifi_password, Desired::wifi_password,
                         Prefs::BadValues::wifi_password);
    good &= handle_chars(Prefs::Keys::ota_password, prefs.ota_password,
                         Prefs::Sizes::ota_password, Desired::ota_password,
                         Prefs::BadValues::ota_password);
    good &= handle_u16(Prefs::Keys::udp_data_port, prefs.udp_data_port,
                       Desired::udp_data_port, Prefs::BadValues::udp_data_port);
    good &= handle_bool(Prefs::Keys::use_queue, prefs.use_queue,
                        Desired::use_queue);
    good &= handle_u16(Prefs::Keys::local_queue_size, prefs.local_queue_size,
                       Desired::local_queue_size,
                       Prefs::BadValues::local_queue_size);
    good &= handle_u16(Prefs::Keys::internet_queue_size,
                       prefs.internet_queue_size, Desired::internet_queue_size,
                       Prefs::BadValues::internet_queue_size);
    good &= handle_bool(Prefs::Keys::use_aes, prefs.use_aes, Desired::use_aes);
    good &=
        handle_chars(Prefs::Keys::hex_key, prefs.hex_key, Prefs::Sizes::hex_key,
                     Desired::hex_key, Prefs::BadValues::hex_key);

    if (good) {
        LOG_N(Log::Uni::Main, Log::Sev::All, Log::Note::AllGood);
    }
    LOG_N(Log::Uni::Main, Log::Sev::Inf, Log::Note::Started);
    prefs.close();
}

void loop() { delay(medium_delay); }
