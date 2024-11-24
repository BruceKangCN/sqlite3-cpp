#pragma once

#if defined _WIN32 || defined __CYGWIN__
#    ifdef BUILDING_SQLITE3_CPP
#        define SQLITE_PUB __declspec(dllexport)
#    else
#        define SQLITE_PUB __declspec(dllimport)
#    endif
#else
#    ifdef BUILDING_SQLITE3_CPP
#        define SQLITE_PUB __attribute__((visibility("default")))
#    else
#        define SQLITE_PUB
#    endif
#endif
