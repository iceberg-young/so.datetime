#include "datetime.hpp"

using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;

namespace so {
    namespace {
        class segment
        {
        public:
            using literal_t = std::string::const_iterator;

        public:
            segment(literal_t& iterator) :
              iterator(iterator),
              axes({}) {
                this->axes.tm_mday = 1;
            }

        public:
            bool digit(int& v) {
                char n = *this->iterator;
                if (n < '0' or n > '9') return false;

                v *= 10;
                v += n - '0';
                ++this->iterator;
                return true;
            }

            int pair() {
                int v = 0;
                if (not (this->digit(v) and this->digit(v))) {
                    throw datetime_decode_error{"A pair of digits ('0'...'9') is expected."};
                }
                return v;
            }

            int sign() {
                char s = *this->iterator;
                if (s == '+' or s == '-') {
                    ++this->iterator;
                    return 0x44 - s;
                }
                throw datetime_decode_error{"Sign (+/-) or 'Z' is expected."};
            }

        public:
            void from_tz() {
                if (*this->iterator == 'Z') {
                    ++this->iterator;
                    return;
                }
                int sign = this->sign();
                auto offset = this->pair() * 60;
                if (*this->iterator == ':') {
                    ++this->iterator;
                }
                offset += this->pair();
                this->axes.tm_yday = sign * offset;
            }

            void from_second() {
                this->axes.tm_sec = this->pair();
                if (*this->iterator == '.') {
                    char c = *++this->iterator;
                    if (c < '0' or c > '9') {
                        throw datetime_decode_error{"At least 1 digit is required since fraction (.) presented."};
                    }
                    int b = 100;
                    int f = 0;
                    do {
                        f += (c - '0') * b;
                        b /= 10;
                        c = *++this->iterator;
                    }
                    while (c >= '0' and c <= '9');
                    this->axes.tm_wday = f;
                }
            }

            void from_minute() {
                this->axes.tm_hour = this->pair();
                if (*this->iterator != ':') {
                    throw datetime_decode_error{"Separator (:) is expected between hour and minute."};
                }
                ++this->iterator;
                this->axes.tm_min = this->pair();
                if (*this->iterator == ':') {
                    ++this->iterator;
                    this->from_second();
                }
                this->from_tz();
            }

            void from_day() {
                this->axes.tm_mday = this->pair();
                if (*this->iterator == 'T') {
                    ++this->iterator;
                    this->from_minute();
                }
            }

            void from_month() {
                this->axes.tm_mon = this->pair() - 1;
                if (*this->iterator == '-') {
                    ++this->iterator;
                    this->from_day();
                }
            }

            void from_year() {
                this->axes.tm_year = this->pair() * 100 - 1900;
                this->axes.tm_year += this->pair();
                if (*this->iterator == '-') {
                    ++this->iterator;
                    this->from_month();
                }
            }

        public:
            literal_t& iterator;

            tm axes;
        };
    }

    system_clock::time_point stotp(segment::literal_t& datetime) {
        segment s{datetime};
        s.from_year();
        milliseconds ms{s.axes.tm_wday};
        auto offset = s.axes.tm_yday * 60;
        auto t = mktime(&s.axes) - offset;
        return system_clock::from_time_t(t + s.axes.tm_gmtoff) + ms;
    }
}
