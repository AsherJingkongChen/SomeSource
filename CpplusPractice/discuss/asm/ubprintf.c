#include <stdio.h>

int* f()
{
    static int i = 0;
    i++;
    return &i;
}

int main()
{
    printf("%d %d %d %d %d", *f(), *f(), *f(), *f(), *f());
    return 0;
}