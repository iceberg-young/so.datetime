#ifndef INCLUDE_SO_DATETIME_PARSER_ONCE_FLAG
#define INCLUDE_SO_DATETIME_PARSER_ONCE_FLAG

#include "datetime.hpp"

namespace so {
    class datetime_parser :
      public tm
    {
    public:
        using literal_t = std::string::const_iterator;

    public:
        datetime_parser(literal_t& iterator);

    protected:
        int digits(int count);

    protected:
        void from_year();

        void from_month();

        void from_day();

        void from_minute();

        void from_second();

        void from_timezone();

    private:
        literal_t& iterator;
    };
}

#endif//INCLUDE_SO_DATETIME_ONCE_FLAG
