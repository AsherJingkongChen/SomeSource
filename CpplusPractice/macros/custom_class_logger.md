### Copy the block to your headers

```h
#undef DEBUG_MODE
#define DEBUG_MODE 1
#if DEBUG_MODE
    #include <stdio.h>

    #define taglog(s) \
        printf(s)
    #define classlog(objname, ins) \
        printf("[%s]\n{\n     this @ 0x%08X\n  .buffer @ 0x%08X\n  .length = %u\n}\n" \
        , objname, (uint32_t)(uint64_t)(&ins), (uint32_t)(uint64_t)ins.buffer, ins.length)
    #define mark_(s) \
        printf("-----u  %s  u-----\n", s)
    #define _mark(s) \
        printf("-----n  %s  n-----\n", s)
#else
    #define taglog(s)       (void)0
    #define classlog(o, i)  (void)0
    #define mark_(s)        (void)0
    #define _mark(s)        (void)0
#endif
```

### Usage

If and only if `DEBUG_MODE` defined as 0:

```h
// literal nothing
```

otherwise (1, -1, or any integer):

```h
taglog("my_class::ctor ()\n");
classlog("this", (*this));
```
