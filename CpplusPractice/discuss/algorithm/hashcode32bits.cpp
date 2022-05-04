#include <iostream>
#include <cstdint>

int32_t hash_code(const char* str)
{
    int32_t result = 0;
    for (const char* C = str; *C != 0; C++)
    {
        result *= 31;
        result += *C;
    }
    return result;
}

int main() {
    std::cout << hash_code("abcd");
    return 0;
}
