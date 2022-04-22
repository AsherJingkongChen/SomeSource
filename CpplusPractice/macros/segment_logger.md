### To mark-up your segments (C/C++)

```h
#undef DEBUG_MODE
#define DEBUG_MODE 1
#if DEBUG_MODE
    #include <stdio.h>

    static uint16_t LN = 0;

    #define taglog(...) \
        printf("<L%5.1u-> | ", ++LN); \
        printf(__VA_ARGS__)
    #define mark_(s) \
        printf("u ----  %s  ---- u\n", s)
    #define _mark(s) \
        printf("n ----  %s  ---- n\n", s)
#else
    #define taglog(...)         (void)0
    #define mark_(s)            (void)0
    #define _mark(s)            (void)0
#endif
```

`LN` is the Line Number (static counter to taglog)

`taglog` is an optional printer: `taglog("just like printf(...), right? %s", "Yes!");`

`mark_ and _mark` highlight the specific segment `mark_("test"); ... _mark("test");`

#### example:

```h
/* ctor0 */
    my_class()
    : my_pointer(nullptr)
    , my_number(0)
    {   
        taglog("byte_frame::ctor0  ()\n");
    }
```

```h
mark_("declare N");
int N;
_mark("declare N");
```
