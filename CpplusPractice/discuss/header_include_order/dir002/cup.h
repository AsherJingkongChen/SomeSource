#ifndef DIR002_CUP_H
#define DIR002_CUP_H

#include "define.h"

namespace dir002 {
    class cup {
    public:
        water* my_water;
        cup(uint64_t w_m, double w_t) {
            my_water->mass        = w_m;
            my_water->temperature = w_t;
        }
    };
}

#endif //DIR002_CUP_H