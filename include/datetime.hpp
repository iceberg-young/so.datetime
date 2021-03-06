/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */
#pragma once

#include <chrono>
#include <string>
#include <stdexcept>

namespace so {
    using time_point = std::chrono::system_clock::time_point;

    class datetime :
      public timespec {
     public:
        static datetime now();

     public:
        datetime(const std::string& w3dt);

        datetime(const time_point& tp);

        datetime(const timespec& ts) :
          timespec(ts) {}

     public:
        operator time_point();
    };

    std::string to_string(const timespec& ts);

    inline std::string to_string(const time_point& tp) {
        return to_string(datetime{tp});
    }

    template<typename rep_t, typename period_t>
    std::string to_string(const std::chrono::duration<rep_t, period_t>& duration) {
        return to_string(std::chrono::duration_cast<std::chrono::milliseconds>(duration));
    }

    template<>
    std::string to_string(const std::chrono::milliseconds& ms);

    class datetime_parse_error :
      public std::domain_error {
     public:
        datetime_parse_error(const std::string& what) :
          domain_error(what) {}
    };
}
