/**
 * Cplusplus class rule of "2 + basic 6 + custom"
 * _1. private members
 * _2. public members + get + set
 * b1. destructor
 * b2. constructors 
 * b3. copy constructor
 * b4. move constructor
 * b5. copy assignment operator
 * b6. move assignment operator
 * _3. custom methods
 */

#ifndef CIIS_BYTE_FRAME_H
#define CIIS_BYTE_FRAME_H

#include <cstdint>
#include <climits>
#include <memory>
#include <algorithm>
#include <utility>
#include <type_traits>

/**
 * debug tools
 */

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

/**
 * primitive type byte_frame
 */

template <class TYPE>
class byte_frame {

static_assert(std::is_fundamental<TYPE>::value
, "byte_frame<TYPE>, TYPE limits for primitive type only");

private:
    TYPE*       buffer;
    uint32_t    length;

public:
/* get & set */
    uint32_t
    get_length() const
    {
        return length;
    }

// basic method section :

/* dtor */
    ~byte_frame()
    {
        delete[] buffer;
        buffer = nullptr;
        length = 0;

        taglog("byte_frame::destor ()\n");
    }

/* ctor0 */
    byte_frame()
        : buffer(nullptr)
        , length(0)
    {   
        taglog("byte_frame::ctor0  ()\n");
    }

/* ctorA */
    explicit
    byte_frame(uint32_t _length)
        : buffer(new TYPE[_length]())
        , length(_length)
    {
        taglog("byte_frame::ctorA  (_length)\n");
    }

/* ctorC (unsafe, range issue) */
    explicit
    byte_frame(TYPE* _buffer, uint32_t _length) noexcept
        : byte_frame(_length)
    {
        std::copy(_buffer, _buffer + _length, buffer);

        taglog("byte_frame::ctorC  (_buffer, _length)\n");
    }

/* copy ctor */
    byte_frame(const byte_frame& _src)
        : byte_frame(_src.buffer, _src.length)
    {
        taglog("byte_frame::cpctor (const byte_frame& _src)\n");
    }

/* move ctor */
    byte_frame(byte_frame&& _src) noexcept
        : buffer(std::exchange(_src.buffer, nullptr))
        , length(_src.length)
    {
        taglog("byte_frame::mvctor (byte_frame&& _src)\n");
    }

/* copy assign */
    byte_frame&
    operator=(const byte_frame& _rhs)
    {
        *this = byte_frame(_rhs); // cpctor + move=

        taglog("byte_frame::copy=  (const byte_frame& _rhs)\n");

        return *this;
    }

/* move assign */
    byte_frame&
    operator=(byte_frame&& _rhs) noexcept
    {
        std::swap(buffer, _rhs.buffer);
        length = _rhs.length;

        taglog("byte_frame::move=  (byte_frame&& _rhs)\n");
        
        return *this;
    }

// byte_frame method section :

/* assert equivalence of member values (no logging) */
    bool
    operator==(const byte_frame& _rhs) const
    {
        if (length != _rhs.length) return false;

        for (uint32_t i = length; i--;)
        {
            if (buffer[i] != _rhs.buffer[i]) return false;
        }
        return true;
    }

/* assert equivalence of member values (no logging) */
    bool
    operator!=(const byte_frame& _rhs) const
    {
        return !(*this == _rhs);
    }

/* copy (unsafe, range issues) */
    void
    operator<<(TYPE* _src) noexcept
    {
        std::copy(_src, _src + length, buffer);

        taglog("byte_frame::oper<< (TYPE* _src)\n");
    }

/* paste (unsafe, range issues) */
    void
    operator>>(TYPE* _des) noexcept
    {
        std::copy(buffer, buffer + length, _des);

        taglog("byte_frame::oper>> (TYPE* _des)\n");
    }

/* copy */
    void
    operator<<(const byte_frame& _src)
    {
        if (length != _src.length) return;

        std::copy(_src.buffer, _src.buffer + _src.length, buffer);

        taglog("byte_frame::oper<< (const byte_frame& _src)\n");
    }

/* paste */
    void
    operator>>(const byte_frame& _des)
    {
        if (length != _des.length) return;

        std::copy(buffer, buffer + length, _des.buffer);

        taglog("byte_frame::oper>> (const byte_frame& _des)\n");
    }

};

#endif //CIIS_BYTE_FRAME_H
