#ifndef INCLUDE_SO_DATETIME_PARSER_ONCE_FLAG
#define INCLUDE_SO_DATETIME_PARSER_ONCE_FLAG

#include <limits>
#include "datetime.hpp"

namespace so {
    class datetime_parser :
      public tm
    {
        /** Embezzled Members:
        * tm_wday: hours of timezone offset
        * tm_yday: minutes of timezone offset
        * tm_gmtoff: nanoseconds
        * tm_zone: string pointer to be parsed
        */
        static_assert(
          std::numeric_limits<decltype(tm::tm_gmtoff)>::max() >= std::nano::den,
          "*tm_gmtoff* should be able to hold a nanosecond (999'999'999)."
        );

    public:
        datetime_parser(const char* begin);

    public:
        long gmt_offset() {
            return this->tm_wday * 60 + this->tm_yday;
        }

        decltype(tm::tm_gmtoff) nanoseconds() {
            return this->tm_gmtoff;
        }

    protected:
        int digits(int count);

    protected:
        void from_year();

        void from_month();

        void from_day();

        void from_minute();

        void from_second();

        void from_timezone();
    };
}

#endif//INCLUDE_SO_DATETIME_ONCE_FLAG
