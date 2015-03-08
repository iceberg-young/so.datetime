#include "datetime_parser.hpp"

namespace so {
    namespace {
        void accrue(std::string& s, size_t p, int c, int v) {
            while (c-- > 0) {
                s[p--] += v % 10;
                if ((v /= 10) <= 0) break;
            }
        }
    }

    using std::chrono::system_clock;

    std::string to_string(const system_clock::time_point& clock) {
        tm axes;
        time_t t = system_clock::to_time_t(clock);
        gmtime_r(&t, &axes);
        std::string s{
          //123456789 123456789 123
          "0000-00-00T00:00:00.000Z"
        };
        accrue(s, 3, 4, axes.tm_year + 1900);
        accrue(s, 6, 2, axes.tm_mon + 1);
        accrue(s, 9, 2, axes.tm_mday);
        accrue(s, 12, 2, axes.tm_hour);
        accrue(s, 15, 2, axes.tm_min);
        accrue(s, 18, 2, axes.tm_sec);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(clock.time_since_epoch()).count() % 1000;
        accrue(s, 22, 3, ms < 0 ? ms + 1000 : ms);
        return s;
    }

    system_clock::time_point stotp(datetime_parser::literal_t& datetime) {
        datetime_parser parser{datetime};
        std::chrono::milliseconds ms{parser.tm_wday};
        auto offset = parser.tm_yday * 60;
        auto t = mktime(&parser) - offset;
        return system_clock::from_time_t(t + parser.tm_gmtoff) + ms;
    }
}
