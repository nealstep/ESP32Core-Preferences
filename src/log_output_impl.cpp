#include <Arduino.h>

#include <e32c_log.hpp>
#include <prefs.hpp>

void log_output_impl(const char* str, bool error, bool truncated) {
    if (error) {
        // there was a an error expanding the string
        Serial.printf("Format!: %s\n", str);
    } else if (truncated) {
        Serial.printf("Trunc!: %s\n", str);
    } else {
        // all is good
        Serial.println(str);
    }
}