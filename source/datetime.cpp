/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

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
        this->tv_sec = timegm(&parser) - offset;
    }

    datetime::datetime(const time_point& tp) {
        auto duration = tp.time_since_epoch();
        if (not std::is_same<decltype(duration), std::chrono::nanoseconds>::value) {
            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
        }
        auto ns = duration.count();
        this->tv_sec = ns / std::nano::den;
        this->tv_nsec = ns % std::nano::den;
        if (this->tv_nsec < 0) {
            this->tv_sec -= 1;
            this->tv_nsec += std::nano::den;
        }
    }

    datetime::operator time_point() {
        return std::chrono::system_clock::from_time_t(this->tv_sec)
          + std::chrono::nanoseconds{this->tv_nsec};
    }
}
