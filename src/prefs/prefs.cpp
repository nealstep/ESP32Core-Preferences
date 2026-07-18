#ifdef ARDUINO

#include "log/e32c_log.hpp"
#include "utils/utils.hpp"

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

void get_pref_bool(const char* key, bool& val, bool verbose, bool use_default,
                   bool dval) {
    Log::Err err = prefs.get_bool(key, val);
    if (err != Log::Err::NoError) {
        LOG_E(Log::Uni::Pref, err, key);
        if (use_default) {
            val = dval;
        } else {
            die();
        }
    }
    if (verbose) {
        LOG_N(Log::Uni::Pref, Log::Sev::Inf, Log::Note::PrefReadS, key,
              b2s(val));
    } else {
        LOG_N(Log::Uni::Pref, Log::Sev::Inf, Log::Note::PrefReadS, key,
              Log::Word::XXX);
    }
}

void get_pref_u16(const char* key, uint16_t& val, uint16_t bad, bool verbose,
                  bool use_default, uint16_t dval) {
    Log::Err err = prefs.get_u16(key, val, bad);
    if (err != Log::Err::NoError) {
        LOG_E(Log::Uni::Pref, err, key);
        if (use_default) {
            val = dval;
        } else {
            die();
        }
    }
    if (verbose) {
        LOG_N(Log::Uni::Pref, Log::Sev::Inf, Log::Note::PrefReadU, key, val);
    } else {
        LOG_N(Log::Uni::Pref, Log::Sev::Inf, Log::Note::PrefReadS, key,
              Log::Word::XXX);
    }
}

void get_pref_u32(const char* key, uint32_t& val, uint32_t bad, bool verbose,
                  bool use_default, uint32_t dval) {
    Log::Err err = prefs.get_u32(key, val, bad);
    if (err != Log::Err::NoError) {
        LOG_E(Log::Uni::Pref, err, key);
        if (use_default) {
            val = dval;
        } else {
            die();
        }
    }
    if (verbose) {
        LOG_N(Log::Uni::Pref, Log::Sev::Inf, Log::Note::PrefReadU, key, val);
    } else {
        LOG_N(Log::Uni::Pref, Log::Sev::Inf, Log::Note::PrefReadS, key,
              Log::Word::XXX);
    }
}

void get_pref_str(const char* key, char* buf, size_t buf_len, const char* bad,
                  bool verbose, bool use_default, const char* dval) {
    Log::Err err = prefs.get_chars(key, buf, buf_len, bad);
    if (err != Log::Err::NoError) {
        LOG_E(Log::Uni::Pref, err, key);
        if (use_default) {
            size_t len = strlcpy(buf, dval, buf_len);
            if (len >= buf_len) {
                LOG_E(Log::Uni::Pref, Log::Err::StringTooBig, key);
                die();
            }
        } else {
            die();
        }
    }
    if (verbose) {
        LOG_N(Log::Uni::Pref, Log::Sev::Inf, Log::Note::PrefReadS, key, buf);
    } else {
        LOG_N(Log::Uni::Pref, Log::Sev::Inf, Log::Note::PrefReadS, key,
              Log::Word::XXX);
    }
}

#endif  // ARDUINO
