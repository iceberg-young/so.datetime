/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "datetime_parser.hpp"

namespace so {
    datetime_parser::datetime_parser(const char* begin) :
      tm({}) {
        this->tm_mday = 1;
        this->tm_zone = begin;
        this->from_year();
    }

    int datetime_parser::digits(int count) {
        int v = 0;
        for (int x = 0; x < count; ++x, ++this->tm_zone) {
            char n = *this->tm_zone;
            if (n < '0' or n > '9') {
                throw datetime_parse_error{
                  std::to_string(count) + " digits are expected, "
                    "but only have " + std::to_string(x) + '.'
                };
            }
            v *= 10;
            v += n - '0';
        }
        return v;
    }

    void datetime_parser::from_year() {
        this->tm_year = this->digits(4) - 1900;
        if (*this->tm_zone == '-') {
            ++this->tm_zone;
            this->from_month();
        }
    }

    void datetime_parser::from_month() {
        this->tm_mon = this->digits(2) - 1;
        if (*this->tm_zone == '-') {
            ++this->tm_zone;
            this->from_day();
        }
    }

    void datetime_parser::from_day() {
        this->tm_mday = this->digits(2);
        if (*this->tm_zone == 'T') {
            ++this->tm_zone;
            this->from_minute();
        }
    }

    void datetime_parser::from_minute() {
        this->tm_hour = this->digits(2);
        if (*this->tm_zone != ':') {
            throw datetime_parse_error{
              "Separator (:) is expected between hour and minute."
            };
        }
        ++this->tm_zone;
        this->tm_min = this->digits(2);
        if (*this->tm_zone == ':') {
            ++this->tm_zone;
            this->from_second();
        }
        this->from_timezone();
    }

    void datetime_parser::from_second() {
        this->tm_sec = this->digits(2);
        if (*this->tm_zone == '.') {
            char n = *++this->tm_zone;
            if (n < '0' or n > '9') {
                throw datetime_parse_error{
                  "At least 1 digit is expected since fraction (.) presented."
                };
            }
            auto power = std::nano::den;
            do {
                power /= 10;
                this->tm_gmtoff += (n - '0') * power;
                n = *++this->tm_zone;
            }
            while (n >= '0' and n <= '9');
        }
    }

    void datetime_parser::from_timezone() {
        char s = *this->tm_zone;
        if (s == 'Z') {
            ++this->tm_zone;
            return;
        }
        if (s != '+' and s != '-') {
            throw datetime_parse_error{"Sign (+/-) or 'Z' is expected."};
        }
        this->tm_isdst = ',' - s; // '+'(0x2B) ','(0x2C) '-'(0x2D)
        ++this->tm_zone;
        this->tm_wday = this->digits(2);
        if (*this->tm_zone == ':') {
            ++this->tm_zone;
        }
        this->tm_yday = this->digits(2);
    }
}
