#pragma once

#define UNIT_LIST(X) \
    X(Main, "Main")  \
    X(Last, "Last")
// Last entry for masking

#define ERROR_LIST(X)                               \
    X(NoError, "No Error")                          \
    X(UnexpectedError, "Unexpected Error")          \
    X(NoPrefs, "No Preferences found")              \
    X(NoPref, "No Preference found")                \
    X(PrefUnset, "Prefence unset")                  \
    X(PrefUpdateFailed, "Preference Update Failed") \
    X(StringTooBig, "String too big")               \
    X(Died, "Died")

#define NOTICE_LIST(X)          \
    X(NoNotice, "No Notice")    \
    X(SimpleValueStr, "%s: %s") \
    X(SimpleValueInt, "%s: %d")

#define WORD_LIST(X) X(Unknown, "Unknown")

#define SEVERITY_LIST(X) \
    X(Dbg, "Debug")      \
    X(Inf, "Info")       \
    X(Wrn, "Warning")    \
    X(Err, "Error")      \
    X(All, "All")
