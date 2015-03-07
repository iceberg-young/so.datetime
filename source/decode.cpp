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
                this->from_year();
            }

        public:
            int digits(int count) {
                int v = 0;
                for (int x = 0; x < count; ++x, ++this->iterator) {
                    char n = *this->iterator;
                    if (n < '0' or n > '9') {
                        throw datetime_decode_error{
                          std::to_string(count) + " digits are expected, "
                            "but only have " + std::to_string(x) + '.'
                        };
                    }
                    v *= 10;
                    v += n - '0';
                }
                return v;
            }

            int sign() {
                char s = *this->iterator;
                if (s == '+' or s == '-') {
                    ++this->iterator;
                    return ',' - s; // '+'(0x2B) ','(0x2C) '-'(0x2D)
                }
                throw datetime_decode_error{"Sign (+/-) or 'Z' is expected."};
            }

        public:
            void from_timezone() {
                if (*this->iterator == 'Z') {
                    ++this->iterator;
                    return;
                }
                int sign = this->sign();
                auto offset = this->digits(2) * 60;
                if (*this->iterator == ':') {
                    ++this->iterator;
                }
                offset += this->digits(2);
                this->axes.tm_yday = sign * offset;
            }

            void from_second() {
                this->axes.tm_sec = this->digits(2);
                if (*this->iterator == '.') {
                    char n = *++this->iterator;
                    if (n < '0' or n > '9') {
                        throw datetime_decode_error{"At least 1 digit is expected since fraction (.) presented."};
                    }
                    int power = 100;
                    int fraction = 0;
                    do {
                        fraction += (n - '0') * power;
                        power /= 10;
                        n = *++this->iterator;
                    }
                    while (n >= '0' and n <= '9');
                    this->axes.tm_wday = fraction;
                }
            }

            void from_minute() {
                this->axes.tm_hour = this->digits(2);
                if (*this->iterator != ':') {
                    throw datetime_decode_error{"Separator (:) is expected between hour and minute."};
                }
                ++this->iterator;
                this->axes.tm_min = this->digits(2);
                if (*this->iterator == ':') {
                    ++this->iterator;
                    this->from_second();
                }
                this->from_timezone();
            }

            void from_day() {
                this->axes.tm_mday = this->digits(2);
                if (*this->iterator == 'T') {
                    ++this->iterator;
                    this->from_minute();
                }
            }

            void from_month() {
                this->axes.tm_mon = this->digits(2) - 1;
                if (*this->iterator == '-') {
                    ++this->iterator;
                    this->from_day();
                }
            }

            void from_year() {
                this->axes.tm_year = this->digits(4) - 1900;
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
        milliseconds ms{s.axes.tm_wday};
        auto offset = s.axes.tm_yday * 60;
        auto t = mktime(&s.axes) - offset;
        return system_clock::from_time_t(t + s.axes.tm_gmtoff) + ms;
    }
}
