/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "datetime.hpp"

namespace so {
    namespace {
        void accrue(std::string& s, size_t p, int c, int v) {
            while (c-- > 0) {
                s[p--] += v % 10;
                if ((v /= 10) <= 0) break;
            }
        }

        bool append(std::string& s, long& c, int u, char d) {
            if (int v = c / u) {
                (s += std::to_string(v)) += d;
            }
            return not (c %= u);
        }
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

    template<>
    std::string to_string(const std::chrono::milliseconds& ms) {
        auto c = std::abs(ms.count());
        std::string p{c != ms.count() ? "-P" : "P"};
        if (!ms.count()) return p += "0D";
        if (append(p, c, 86400000, 'D')) return p;
        p += 'T';
        if (append(p, c, 3600000, 'H')) return p;
        if (append(p, c, 60000, 'M')) return p;
        p += std::to_string(c / 1000);
        if (c %= 1000) {
            char fraction[sizeof(".000")];
            snprintf(fraction, sizeof(fraction), ".%03ld", c);
            p += fraction;
        }
        return p += 'S';
    }
}
