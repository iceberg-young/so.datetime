#include "datetime.hpp"

namespace so {
    namespace {
        void accrue(std::string& s, size_t p, int c, int v) {
            while (c-- > 0) {
                s[p--] += v % 10;
                if ((v /= 10) <= 0) break;
            }
        }
    }

    std::string to_string(const time_point& time) {
        auto duration = time.time_since_epoch();
        if (not std::is_same<decltype(duration), std::chrono::nanoseconds>::value) {
            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
        }
        auto ns = duration.count() % std::nano::den;
        timespec ts{std::chrono::system_clock::to_time_t(time), ns};
        if (ns < 0) {
            ts.tv_sec -= 1;
            ts.tv_nsec += std::nano::den;
        }
        return to_string(ts);
    }

    std::string to_string(const timespec& time) {
        tm axes;
        gmtime_r(&time.tv_sec, &axes);
        std::string s{
          //          111111111 222
          //123456789 123456789 123
          "0000-00-00T00:00:00.000Z"
        };
        accrue(s, 3, 4, axes.tm_year + 1900);
        accrue(s, 6, 2, axes.tm_mon + 1);
        accrue(s, 9, 2, axes.tm_mday);
        accrue(s, 12, 2, axes.tm_hour);
        accrue(s, 15, 2, axes.tm_min);
        accrue(s, 18, 2, axes.tm_sec);
        accrue(s, 22, 3, int(time.tv_nsec / 1000000));
        return s;
    }
}
