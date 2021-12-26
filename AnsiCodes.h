
#include <string>

#ifndef ANSI_CODES
#define ANSI_CODES

namespace AnsiCodes {
#ifdef __WIN32
    const std::string red = "";
    const std::string green = "";
    const std::string yellow = "";
    const std::string blue = "";
    const std::string magenta = "";
    const std::string cyan = "";
    const std::string white = "";
    const std::string reset = "";

#else
    const std::string red = "\u001b[31;1m";
    const std::string green = "\u001b[32;1m";
    const std::string yellow = "\u001b[33;1m";
    const std::string blue = "\u001b[34;1m";
    const std::string magenta = "\u001b[35;1m";
    const std::string cyan = "\u001b[36;1m";
    const std::string white = "\u001b[37;1m";
    const std::string reset = "\u001b[0;1m";
#endif
}

#endif