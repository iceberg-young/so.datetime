#include "iostream"
#include "datetime.hpp"

using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;

namespace so {
    namespace {
        void accrue(std::string& s, size_t p, int c, int v) {
            while (c-- > 0) {
                s[p--] += v % 10;
                if ((v /= 10) <= 0) break;
            }
        }
    }

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
        auto ms = duration_cast<milliseconds>(clock.time_since_epoch());
        accrue(s, 22, 3, (ms.count() % 1000 + 1000) % 1000);
        return s;
    }
}
