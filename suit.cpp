#include <iostream>
#include <unistd.h>
#include "include/datetime.hpp"

using namespace std;
using namespace std::chrono;
using namespace so;

int main() {
    auto n1 = system_clock::now();
    usleep(1000);
    auto n2 = system_clock::now();
    timespec t1 = datetime("2015-03-06T08:13:33.6285-00:03");
    timespec t2 = datetime("1715-03-06T08:13:33.35+06:10");
    cout << to_string(n1) << '\n'
      << to_string(n2) << '\n'
      << to_string(t1) << '\n'
      << to_string(t2) << '\n'
      << to_string(datetime::now());
    return 0;
}
