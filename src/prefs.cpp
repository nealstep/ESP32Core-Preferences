#ifdef ARDUINO

#include "e32c_log.hpp"

#ifdef ARDUINO_ARCH_ESP32

#include <Preferences.h>

Preferences preferences;

#else
#error "Only ESP32 Supported"
#endif  // ARDUINO_ARCH_ESP32

#include "prefs.hpp"

Log::Err Prefs::open(const char* name, bool read_only) {
#ifdef ARDUINO_ARCH_ESP32
    bool succ = preferences.begin(name, read_only);
    if (!succ) {
#ifdef LOG_SERIAL
        LOG_SERIAL.begin(SERIAL_SPEED);
        return Log::Err::NoPrefs;
#endif  // LOG_SERIAL
    }
#else
#error "Only ESP32 Supported"
#endif  // ARDUINO_ARCH_ESP32
    return Log::Err::NoError;
}

Log::Err Prefs::get_bool(const char* key, bool& val) {
#ifdef ARDUINO_ARCH_ESP32
    if (preferences.isKey(key)) {
        val = preferences.getBool(key);
    } else {
        val = false;
        return Log::Err::PrefUnset;
    }
#else
#error "Only ESP32 Supported"
#endif  // ARDUINO_ARCH_ESP32
    return Log::Err::NoError;
}

Log::Err Prefs::get_u16(const char* key, uint16_t& val, const uint16_t bad) {
#ifdef ARDUINO_ARCH_ESP32
    if (preferences.isKey(key)) {
        val = preferences.getUShort(key, bad);
        if (val == bad) {
            return Log::Err::NoPref;
        }
    } else {
        val = bad;
        return Log::Err::PrefUnset;
    }
#else
#error "Only ESP32 Supported"
#endif  // ARDUINO_ARCH_ESP32
    return Log::Err::NoError;
}

Log::Err Prefs::get_u32(const char* key, uint32_t& val, const uint32_t bad) {
#ifdef ARDUINO_ARCH_ESP32
    if (preferences.isKey(key)) {
        val = preferences.getUInt(key, bad);
        if (val == bad) {
            return Log::Err::NoPref;
        }
    } else {
        val = bad;
        return Log::Err::PrefUnset;
    }
#else
#error "Only ESP32 Supported"
#endif  // ARDUINO_ARCH_ESP32
    return Log::Err::NoError;
}

Log::Err Prefs::get_chars(const char* key, char* buffer, size_t buf_len,
                          const char* bad) {
#ifdef ARDUINO_ARCH_ESP32
    Log::Err err = Log::Err::NoError;
    if (preferences.isKey(key)) {
        size_t len = preferences.getString(key, buffer, buf_len);
        Serial.printf("Length: %d\n", len);
        Serial.printf("Buf Len: %d\n", buf_len -1);
        if ((len == 0) || (len > buf_len - 1)) {
            err = Log::Err::NoPref;
        }
    } else {
        err = Log::Err::PrefUnset;
    }
    if (err != Log::Err::NoError) {
        size_t len = strlcpy(buffer, bad, buf_len);
        if (len >= sizeof(buf_len)) {
            return Log::Err::StringTooBig;
        }
        return err;
    }
#else
#error "Only ESP32 Supported"
#endif  // ARDUINO_ARCH_ESP32
    return Log::Err::NoError;
}

Log::Err Prefs::set_bool(const char* key, const bool val) {
#ifdef ARDUINO_ARCH_ESP32
    size_t len = preferences.putBool(key, val);
    if (len == 0) {
        return Log::Err::PrefUpdateFailed;
    }
#else
#error "Only ESP32 Supported"
#endif  // ARDUINO_ARCH_ESP32
    return Log::Err::NoError;
}

Log::Err Prefs::set_u16(const char* key, const uint16_t val) {
#ifdef ARDUINO_ARCH_ESP32
    size_t len = preferences.putUShort(key, val);
    if (len == 0) {
        return Log::Err::PrefUpdateFailed;
    }
#else
#error "Only ESP32 Supported"
#endif  // ARDUINO_ARCH_ESP32
    return Log::Err::NoError;
}
Log::Err Prefs::set_u32(const char* key, const uint32_t val) {
#ifdef ARDUINO_ARCH_ESP32
    size_t len = preferences.putUInt(key, val);
    if (len == 0) {
        return Log::Err::PrefUpdateFailed;
    }
#else
#error "Only ESP32 Supported"
#endif  // ARDUINO_ARCH_ESP32
    return Log::Err::NoError;
}
Log::Err Prefs::set_chars(const char* key, const char* buffer) {
#ifdef ARDUINO_ARCH_ESP32
    size_t len = preferences.putString(key, buffer);
    if (len == 0) {
        return Log::Err::PrefUpdateFailed;
    }

#else
#error "Only ESP32 Supported"
#endif  // ARDUINO_ARCH_ESP32
    return Log::Err::NoError;
}

void Prefs::close(void) {
#ifdef ARDUINO_ARCH_ESP32
    preferences.end();
#else
#error "Only ESP32 Supported"
#endif  // ARDUINO_ARCH_ESP32
}

#endif  // ARDUINO