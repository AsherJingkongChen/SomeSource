#if 0
#include "export_y.h"
#else
#include "export_n.h"
#endif
#include <iostream>

int main()
{
    dir002::cup c(154, 17.6);

    printf("mass=%llu, temp=%.1lf\n"
    , c.my_water->mass
    , c.my_water->temperature);

    return 0;
}