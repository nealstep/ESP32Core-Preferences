#pragma once
// this file can be copied into another program to use stored prefs

#ifdef ARDUINO
#include <Arduino.h>
#ifdef ARDUINO_ARCH_ESP32
#include <Preferences.h>
#endif  // ARDUINO_ARCH_ESP32

#include "constants.hpp"

class Prefs {
   public:
    class Keys {
       public:
        static constexpr const char* const use_serial = "use_serial";
        static constexpr const char* const serial_speed = "serial_speed";
        static constexpr const char* const chip_name = "chip_name";
        static constexpr const char* const keep_alive_int = "keep_alive_int";
        static constexpr const char* const check_internet_int = "chk_inter_int";
        static constexpr const char* const tz_full = "tz_full";
        static constexpr const char* const wifi_ssid = "wifi_ssid";
        static constexpr const char* const wifi_password = "wifi_password";
        static constexpr const char* const ota_password = "ota_password";
        static constexpr const char* const udp_data_port = "udp_data_port";
        static constexpr const char* const use_queue = "use_queue";
        static constexpr const char* const local_queue_size = "localq_sz";
        static constexpr const char* const internet_queue_size = "internetq_sz";
        static constexpr const char* const use_aes = "use_aes";
        static constexpr const char* const encrypt_local = "encrypt_local";
        static constexpr const char* const hex_key = "hex_key";
        static constexpr const char* const remote_host = "remote_host";
    };

    class BadValues {
       public:
        static constexpr uint32_t serial_speed = 1;
        static constexpr const char* const chip_name = "X";
        static constexpr uint32_t keep_alive_int = 1;
        static constexpr uint32_t check_internet_int = 1;
        static constexpr const char* const tz_full = "X";
        static constexpr const char* const wifi_ssid = "X";
        static constexpr const char* const wifi_password = "X";
        static constexpr const char* const ota_password = "X";
        static constexpr uint16_t udp_data_port = 1;
        static constexpr uint16_t local_queue_size = 1;
        static constexpr uint16_t internet_queue_size = 1;
        static constexpr const char* const hex_key = "X";
        static constexpr const char* const remote_host = "X";
    };

    class Sizes {
       public:
        static constexpr size_t chip_name = 32 + 1;
        static constexpr size_t tz_full = 128 + 1;
        static constexpr size_t wifi_ssid = 32 + 1;
        static constexpr size_t wifi_password = 64 + 1;
        static constexpr size_t ota_password = 64 + 1;
        static constexpr size_t hex_key = 65 + 1;
        static constexpr size_t remote_host = 253 + 1;
    };

    bool use_serial;
    uint32_t serial_speed;
    char chip_name[Sizes::chip_name];
    uint32_t keep_alive_int;
    uint32_t check_internet_int;
    char tz_full[Sizes::tz_full];
    char wifi_ssid[Sizes::wifi_ssid];
    char wifi_password[Sizes::wifi_password];
    char ota_password[Sizes::ota_password];
    uint16_t udp_data_port;
    bool use_queue;
    uint16_t local_queue_size;
    uint16_t internet_queue_size;
    bool use_aes;
    bool encrypt_local;
    char hex_key[Sizes::hex_key];
    char remote_host[Sizes::remote_host];

    // lazy singleton
    static Prefs& getInstance(void) {
        static Prefs instance;
        return instance;
    }
    Prefs(const Prefs&) = delete;
    Prefs& operator=(const Prefs&) = delete;

    Log::Err open(const char* name, const bool read_only);

    Log::Err get_bool(const char* key, bool& val);
    Log::Err get_u16(const char* key, uint16_t& val, const uint16_t bad);
    Log::Err get_u32(const char* key, uint32_t& val, const uint32_t bad);
    Log::Err get_chars(const char* key, char* buffer, size_t buf_len,
                       const char* bad);

    Log::Err set_bool(const char* key, const bool val);
    Log::Err set_u16(const char* key, const uint16_t val);
    Log::Err set_u32(const char* key, const uint32_t val);
    Log::Err set_chars(const char* key, const char* buffer);

    void close(void);

   private:
#ifdef ARDUINO_ARCH_ESP32
    Preferences preferences;
#endif  /// ARDUINO_ARCH_ESP32

    // hidden creator
    Prefs(void) {};
};

static Prefs& prefs = Prefs::getInstance();

void get_pref_bool(const char* key, bool& val, bool verbose = true,
                   bool use_default = false, bool dval = false);
void get_pref_u16(const char* key, uint16_t& val, uint16_t bad,
                  bool verbose = true, bool use_default = false,
                  uint16_t dval = 0);
void get_pref_u32(const char* key, uint32_t& val, uint32_t bad,
                  bool verbose = true, bool use_default = false,
                  uint32_t dval = 0);
void get_pref_str(const char* key, char* buf, size_t buf_len, const char* bad,
                  bool verbose = true, bool use_default = false,
                  const char* dval = "");

#endif  // ARDUINO
