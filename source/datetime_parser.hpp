/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */
#pragma once

#include "datetime.hpp"
#include <limits>

namespace so {
    class datetime_parser :
      public tm {
        /** Embezzled Members:
         * tm_wday: hour part of timezone offset
         * tm_yday: minute part of timezone offset
         * tm_isdst: sign part of timezone offset
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
            return this->tm_isdst * (this->tm_wday * 60 + this->tm_yday);
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
