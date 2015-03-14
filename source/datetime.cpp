#include "datetime_parser.hpp"

namespace so {
    datetime datetime::now() {
        timespec ts;
        timespec_get(&ts, TIME_UTC);
        return ts;
    }

    datetime::datetime(const std::string& w3dt) {
        datetime_parser parser{w3dt.c_str()};
        this->tv_nsec = parser.nanoseconds();
        auto offset = parser.gmt_offset() * 60;
        this->tv_sec = mktime(&parser) - offset;
        this->tv_sec += parser.tm_gmtoff;
    }

    datetime::operator time_point() {
        return std::chrono::system_clock::from_time_t(this->tv_sec)
          + std::chrono::nanoseconds{this->tv_nsec};
    }
}
