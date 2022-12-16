#ifndef ZR_CORE_H
#define ZR_CORE_H

#include <iostream>
#include <string>

namespace zr{
    enum VERBOSITY_LEVEL{
        DEBUG = 0, INFO = 1, WARNING = 2, ERROR = 3
    };
    extern std::string level_name[4];
    extern VERBOSITY_LEVEL log_level;
    void log(std::string, zr::VERBOSITY_LEVEL error_level=VERBOSITY_LEVEL::INFO);
}
#endif
