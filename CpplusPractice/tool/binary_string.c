#include <stdio.h>

typedef char binary_long_strbuf[8 * sizeof(long) + 3];

const char*
binary_long_str(char* _bin, long _dec)
{
    unsigned long mask = 1UL << (8 * sizeof(long) - 1);

    *_bin++ = '0';
    *_bin++ = 'b';

    while (mask)
    {
        *_bin++ = !!(_dec & mask) + '0';
        mask >>= 1;
    }

    return _bin - (8 * sizeof(long) + 2);
}

typedef char binary_int_strbuf[8 * sizeof(int) + 3];

const char*
binary_int_str(char* _bin, int _dec)
{
    unsigned int mask = 1UL << (8 * sizeof(int) - 1);

    *_bin++ = '0';
    *_bin++ = 'b';

    while (mask)
    {
        *_bin++ = !!(_dec & mask) + '0';
        mask >>= 1;
    }

    return _bin - (8 * sizeof(int) + 2);
}

int main()
{
    binary_int_strbuf I = {};
    printf("%s\n", binary_int_str(I, 16843009));

    binary_long_strbuf L = {};
    printf("%s\n", binary_long_str(L, 42424242424242));

    return 0;
}
