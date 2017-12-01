// Copyright 2017 Beafantles

#include <iostream>
#include <string>

namespace utils
{
std::string convert_time_to_str(float _seconds)
{
    uint8_t nbHours = _seconds / 3600;
    _seconds -= nbHours * 3600;
    uint8_t nbMinutes = _seconds / 60;
    _seconds -= nbMinutes * 60;
    uint8_t nbSeconds = static_cast<uint8_t>(_seconds);
    _seconds -= nbSeconds;
    uint16_t    nbMilliSeconds = _seconds * 1000;
    std::string millisecondsStr;
    if (nbMilliSeconds < 10)
        millisecondsStr += "00";
    else if (nbMilliSeconds < 100)
        millisecondsStr += "0";
    millisecondsStr += std::to_string(nbMilliSeconds);

    return (nbHours < 10 ? "0" : "") + std::to_string(nbHours) + ":" + (nbMinutes < 10 ? "0" : "")
           + std::to_string(nbMinutes) + ":" + (nbSeconds < 10 ? "0" : "") + std::to_string(nbSeconds) + "."
           + millisecondsStr;
}
}  // namespace utils
