#ifndef CIIS_BYTE_FRAME_H
#define CIIS_BYTE_FRAME_H

#include <cstdint>
#include <algorithm>
#include <type_traits>

#ifndef DEBUG_MODE
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
#endif

/**
 * primitive type byte_frame
 */

template <class TYPE>
class byte_frame {

static_assert(std::is_fundamental<TYPE>::value
, "byte_frame<TYPE>, TYPE is limited for primitive type only");

private:
    TYPE*       buffer;
    uint32_t    length;

public:
/* get & set */
    inline uint32_t
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

        taglog("<DLOC> byte_frame::destor ()\n");
    }

/* ctor0 */
    byte_frame()
        : buffer(nullptr)
        , length(0)
    {   
        taglog("<DCLR> byte_frame::ctor0  ()\n");
    }

/* ctorA */
    explicit
    byte_frame(uint32_t _length)
        : buffer(new TYPE[_length])
        , length(_length)
    {
        taglog("<ALOC> byte_frame::ctorA  (_length)\n");
    }

/* ctorC (copy from raw pointers) */
    explicit
    byte_frame(TYPE* _buffer, uint32_t _length) noexcept
        : byte_frame(_length)
    {
        std::copy(_buffer, _buffer + _length, buffer);

        taglog("<COPY> byte_frame::ctorC  (_buffer, _length)\n");
    }

/* copy ctor */
    explicit
    byte_frame(const byte_frame& _src)
        : byte_frame(_src.buffer, _src.length)
    {
        taglog("<COPY> byte_frame::cpctor (const byte_frame& _src)\n");
    }

/* move ctor */
    explicit
    byte_frame(byte_frame&& _src) noexcept
        : buffer(_src.buffer)
        , length(_src.length)
    {
        _src.buffer = nullptr;
        _src.length = 0;

        taglog("<MOVE> byte_frame::mvctor (byte_frame&& _src)\n");
    }

/* copy assign */
    void
    operator=(const byte_frame& _rhs)
    {
        if (length == _rhs.length) 
        {
            std::copy(_rhs.buffer, _rhs.buffer + length, buffer);
        } 
        else // if lengths are different, create new instance
        {
            *this = byte_frame(_rhs);
        }

        taglog("<COPY> byte_frame::copy=  (const byte_frame& _rhs)\n");
    }

/* move assign */
    void
    operator=(byte_frame&& _rhs) noexcept
    {
        std::swap(buffer, _rhs.buffer);
        std::swap(length, _rhs.length);

        taglog("<MOVE> byte_frame::move=  (byte_frame&& _rhs)\n");
    }

// custom method section :

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

/* paste (paste to raw pointers, assigned length) */
    void
    paste(TYPE* _buffer, uint32_t _length) noexcept
    {
        std::copy(buffer, buffer + _length, _buffer);

        taglog("<COPY> byte_frame::paste  (TYPE* _buffer, uint32_t _length)\n");
    }

/* paste (paste to raw pointers, default length) */
    void
    paste(TYPE* _buffer) noexcept
    {
        std::copy(buffer, buffer + length, _buffer);

        taglog("<COPY> byte_frame::paste  (TYPE* _buffer)\n");
    }

/* copy (copy from raw pointers, assigned length) */
    void
    copy(TYPE* _buffer, uint32_t _length) noexcept
    {
        std::copy(_buffer, _buffer + _length, buffer);

        taglog("<COPY> byte_frame::copy   (TYPE* _buffer, uint32_t _length)\n");
    }

/* copy (copy from raw pointers, default length) */
    void
    copy(TYPE* _buffer) noexcept
    {
        std::copy(_buffer, _buffer + length, buffer);

        taglog("<COPY> byte_frame::copy   (TYPE* _buffer)\n");
    }

};

#endif //CIIS_BYTE_FRAME_H
