### Does the order of including header file matter?

Now, we have some header files under a directory `dir002`:

```
- dir002
  - define.h
  - water.h
  - cup.h
  - export.h
  - test.cpp
```
Remember the question (as the topic), and scroll down the content of these 5 files:

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
