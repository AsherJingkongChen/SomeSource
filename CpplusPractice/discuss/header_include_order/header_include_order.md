### Does the order of including header file matter?

Now, we have some header files under a directory [__`dir002`__](https://github.com/AsherJingkongChen/PurBrainSource/tree/dir002):

```
- dir002
  - define.h
  - water.h
  - cup.h
  - export_y.h
  - export_n.h
  - test.cpp
```
The compilation fails when including `export_n.h` instead of `export_y.h (successful)`,

and they are different only at the order of including components (`water.h` and `cup.h`).

Scroll down the content of 5 headers and 1 implmentation:

I use one command to compile:

`g++ -o test test.cpp`

__define.h__

```h
#ifndef DIR002_DEFINE_H
#define DIR002_DEFINE_H

#include <cstdint>

namespace dir002 {
    class water;
    class cup;
}

#endif //DIR002_DEFINE_H
```

__water.h__

```h
#ifndef DIR002_WATER_H
#define DIR002_WATER_H

#include "define.h"

namespace dir002 {
    class water {
    public:
        uint64_t  mass;
        double    temperature;
    };
}

#endif //DIR002_WATER_H
```

__cup.h__

```h
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
```

__export_y.h__

```h
#ifndef DIR002_EXPORT_Y_H
#define DIR002_EXPORT_Y_H

#include "water.h"
#include "cup.h"

#endif //DIR002_EXPORT_Y_H
```

__export_n.h__

```h
#ifndef DIR002_EXPORT_Y_H
#define DIR002_EXPORT_Y_H

#include "cup.h"
#include "water.h"

#endif //DIR002_EXPORT_Y_H
```

__test.cpp__

```h
#if 1
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
```
