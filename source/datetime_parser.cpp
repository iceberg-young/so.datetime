#include "datetime_parser.hpp"

namespace so {
    datetime_parser::datetime_parser(literal_t& iterator) :
      tm({}),
      iterator(iterator) {
        this->tm_mday = 1;
        this->from_year();
    }

    int datetime_parser::digits(int count) {
        int v = 0;
        for (int x = 0; x < count; ++x, ++this->iterator) {
            char n = *this->iterator;
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
        if (*this->iterator == '-') {
            ++this->iterator;
            this->from_month();
        }
    }

    void datetime_parser::from_month() {
        this->tm_mon = this->digits(2) - 1;
        if (*this->iterator == '-') {
            ++this->iterator;
            this->from_day();
        }
    }

    void datetime_parser::from_day() {
        this->tm_mday = this->digits(2);
        if (*this->iterator == 'T') {
            ++this->iterator;
            this->from_minute();
        }
    }

    void datetime_parser::from_minute() {
        this->tm_hour = this->digits(2);
        if (*this->iterator != ':') {
            throw datetime_parse_error{"Separator (:) is expected between hour and minute."};
        }
        ++this->iterator;
        this->tm_min = this->digits(2);
        if (*this->iterator == ':') {
            ++this->iterator;
            this->from_second();
        }
        this->from_timezone();
    }

    void datetime_parser::from_second() {
        this->tm_sec = this->digits(2);
        if (*this->iterator == '.') {
            char n = *++this->iterator;
            if (n < '0' or n > '9') {
                throw datetime_parse_error{"At least 1 digit is expected since fraction (.) presented."};
            }
            int power = 100; // Keep 3 digits at most.
            int fraction = 0;
            do {
                fraction += (n - '0') * power;
                power /= 10;
                n = *++this->iterator;
            }
            while (n >= '0' and n <= '9');
            this->tm_wday = fraction;
        }
    }

    void datetime_parser::from_timezone() {
        char s = *this->iterator;
        if (s == 'Z') {
            ++this->iterator;
            return;
        }
        if (s != '+' and s != '-') {
            throw datetime_parse_error{"Sign (+/-) or 'Z' is expected."};
        }
        int sign = ',' - s; // '+'(0x2B) ','(0x2C) '-'(0x2D)
        ++this->iterator;
        auto offset = this->digits(2) * 60;
        if (*this->iterator == ':') {
            ++this->iterator;
        }
        offset += this->digits(2);
        this->tm_yday = sign * offset;
    }
}
