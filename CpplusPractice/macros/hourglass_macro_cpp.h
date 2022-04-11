#ifndef NANOSEC_TEST_CPP
#define NANOSEC_TEST_CPP

#include <chrono>
#include <iostream>

static std::chrono::steady_clock::time_point begin;
static std::chrono::steady_clock::time_point end;

#define nano_ \
    begin = std::chrono::steady_clock::now();

#define _nano \
    end = std::chrono::steady_clock::now(); \
    std::cout \
    << "Elapsed " \
    << std::chrono::duration_cast<std::chrono::nanoseconds> \
    (end - begin).count() \
    << " nsec" \
    << std::endl

/* timer usage example:
int main() {
    nano_;
    for (uint64_t i = 0; i < 10000; i++);
    _nano;
    
    nano_;
    void(0);
    _nano;
    
    return 0;
}
//*/

#endif //NANOSEC_TEST_CPP
