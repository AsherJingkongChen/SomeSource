#include <iostream>
#include <ctime>
#include <cmath>

#define CLK(t) ( printf("time=%.3fus\n", ((float)(clock() - t))*1000000 / CLOCKS_PER_SEC) )

/* O(n) simple */
uint64_t fib(uint64_t n)
{
    uint64_t a = 0;
    uint64_t b = 1;
    while (n-- > 1) {
        uint64_t t = a;
        a = b;
        b += t;
    }
    return b;
}

int main() {
    clock_t t;
    for (uint64_t N = 0; N <= 93; N++) {
        t = clock();
        uint64_t f = fib(N);
        printf("N=%lu, fib(N)=%lu, ", N, f);
        CLK(t);
    }
    
    return 0;
}
