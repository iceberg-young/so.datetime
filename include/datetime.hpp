#ifndef INCLUDE_SO_DATETIME_ONCE_FLAG
#define INCLUDE_SO_DATETIME_ONCE_FLAG

#include <chrono>
#include <string>
#include <stdexcept>

namespace so {
    using time_point = std::chrono::system_clock::time_point;

    std::string to_string(const time_point& time);

    std::string to_string(const timespec& time);

    class datetime :
      public timespec {
     public:
        static datetime now();

     public:
        datetime(const std::string& w3dt);

        datetime(const timespec& ts) :
          timespec(ts) {}

     public:
        operator time_point();
    };

    class datetime_parse_error :
      public std::domain_error {
     public:
        datetime_parse_error(const std::string& what) :
          domain_error(what) {}
    };
}

#endif//INCLUDE_SO_DATETIME_ONCE_FLAG
