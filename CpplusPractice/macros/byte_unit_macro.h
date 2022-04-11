#ifdef BYTE
#undef BYTE
#endif //BYTE

#define BYTE *1UL
#define KB *1024UL BYTE
#define MB *1024UL KB
#define GB *1024UL MB
#define TB *1024UL GB
#define PB *1024UL TB
#define EB *1024UL PB

/* test code, s is UINT64_MAX
#include <iostream>
int main() {
    uint64_t s = 16 EB - 1;
    std::cout << s << std::endl;
    return 0;
}
//*/
