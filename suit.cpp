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
    auto t1 = stotp("2015-03-06T08:13:33.62+01:00");
    auto t2 = stotp("1715-03-06T08:13:33.6285+01:00");
    cout << to_string(n1) << '\n'
      << to_string(n2) << '\n'
      << to_string(t1) << '\n'
      << to_string(t2) << '\n';
    return 0;
}
