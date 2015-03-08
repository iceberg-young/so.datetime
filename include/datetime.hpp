#ifndef INCLUDE_SO_DATETIME_ONCE_FLAG
#define INCLUDE_SO_DATETIME_ONCE_FLAG

#include <chrono>
#include <string>
#include <stdexcept>

namespace so {
    std::string to_string(const std::chrono::system_clock::time_point& clock);

    std::chrono::system_clock::time_point stotp(typename std::string::const_iterator& datetime);

    inline std::chrono::system_clock::time_point stotp(const std::string& datetime) {
        auto i = datetime.begin();
        return stotp(i);
    }

    class datetime_parse_error :
      public std::domain_error
    {
    public:
        datetime_parse_error(const std::string& what) :
          domain_error(what) {
        }
    };
}

#endif//INCLUDE_SO_DATETIME_ONCE_FLAG
