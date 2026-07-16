#pragma once

#define UNIT_LIST(X) \
    X(Main, "Main")  \
    X(Pref, "Pref")  \
    X(Last, "Last")
// Last entry for masking

#define ERROR_LIST(X)                                   \
    X(NoError, "No Error")                              \
    X(UnexpectedError, "Unexpected Error")              \
    X(NoPrefs, "No Preferences found")                  \
    X(NoPref, "No Preference found: %s")                \
    X(PrefUnset, "Prefence unset: %s")                  \
    X(PrefUpdateFailed, "Preference Update Failed: %s") \
    X(StringTooBig, "String too big: %s")               \
    X(Died, "Died")

#define NOTICE_LIST(X)                           \
    X(NoNotice, "No Notice")                     \
    X(Starting, "Starting up")                   \
    X(Started, "Started up")                     \
    X(PrefDesS, "Pref %s Desired as %s")         \
    X(PrefDesU, "Pref %s Desired as %u")         \
    X(PrefReadS, "Read Pref %s as %s")           \
    X(PrefReadU, "Read Pref %s as %u")           \
    X(PrefUpdS, "Updated Pref %s as %s")         \
    X(PrefUpdU, "Updated Pref %s as %u")         \
    X(PrefNotUpdS, "Not updating Pref %s as %s") \
    X(PrefNotUpdU, "Not updating Pref %s as %u") \
    X(PrefAlready, "Already Desired value: %s")  \
    X(AllGood, "All Values set and correct")

#define WORD_LIST(X)      \
    X(Unknown, "Unknown") \
    X(XXX, "XXX")

#define SEVERITY_LIST(X) \
    X(Dbg, "Debug")      \
    X(Inf, "Info")       \
    X(Wrn, "Warning")    \
    X(Err, "Error")      \
    X(All, "All")
