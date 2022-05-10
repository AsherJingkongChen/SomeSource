#ifndef CIIS_FATTY_CLASS_H
#define CIIS_FATTY_CLASS_H

#include <cstdint>
#include <string>

#ifndef DEBUG_MODE
#define DEBUG_MODE 1
#endif//DEBUG_MODE
#if     DEBUG_MODE
    #include <stdio.h>

    #define tlog(...) \
        printf("<TLOG> | " __VA_ARGS__)
    #define tagV(S) \
        printf("V ---- ----  %s  ---- ---- V\n", S)
    #define tagA(S) \
        printf("A ---- ----  %s  ---- ---- A\n", S)

#else
    #define tlog(...)   (void)0
    #define tagV(s)     (void)0
    #define tagA(s)     (void)0

#endif

static constexpr inline size_t
PILE_SIZE = 200;

class bulk {
private:
    size_t id;
    std::string pile;

public:
    ~bulk()
    {
        tlog("dtor %zu\n", id);
        id = 0;
    }

    bulk()
        : id(0)
        , pile()
    {
        tlog("ctor0\n");
    }

    bulk(size_t _id)
        : id(_id)
        , pile(PILE_SIZE, 'p')
    {
        tlog("ctorAS %zu\n", id);
    }

    bulk(const bulk& b)
        : id(b.id)
        , pile(b.pile)
    {
        tlog("cpctor %zu\n", id);
    }

    bulk(bulk&& b)
        : id(b.id)
        , pile(std::move(b.pile))
    {
        tlog("mvctor %zu\n", id);
        b.id = 0;
    }

    void
    operator=(const bulk& b)
    {
        tlog("copy= %zu . %zu\n", id, b.id);
        id = b.id;
        pile = b.pile;
    }

    void
    operator=(bulk&& b)
    {
        tlog("move= %zu . %zu\n", id, b.id);
        std::swap(id, b.id);
        std::swap(pile, b.pile);
    }
};

#endif //CIIS_FATTY_CLASS_H
