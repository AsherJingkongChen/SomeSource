#ifndef CIIS_BYTE_BUFFER_H
#define CIIS_BYTE_BUFFER_H

#include <cstdint>
#include <algorithm>

#ifndef DEBUG_MODE
#define DEBUG_MODE 1
#if DEBUG_MODE
    #include <stdio.h>

    static uint32_t LN = 0;

    #define taglog(...) \
        printf("<L%6.1u-> | ", ++LN); \
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
 * byte_buffer<TYPE>, an simple copy-and-paste buffer
 * 
 * :: TYPE*   frames      | array  of frames
 * :: size_t  num_frames  | number of frames 
 * 
 * byte_buffer<TYPE> ~ TYPE frames[num_frames]
 * 
 * -- the contained data type should be either copyable --
 */
template <class TYPE>
class byte_buffer {

private:
    TYPE*   frames;
    size_t  num_frames;

public:
/* get & set */
    inline size_t
    get_num_frames() const
    {
        return num_frames;
    }

// basic method section :

/* dtor (destructor) */
    ~byte_buffer()
    {
        delete[] frames;
        frames = nullptr;

        num_frames = 0;

        taglog("<DLOC> byte_buffer::destor ()\n");
    }

/* ctor0 (default constructor) */
    byte_buffer()
        : frames(nullptr)
        , num_frames(0)
    {   
        taglog("<DCLR> byte_buffer::ctor0  ()\n");
    }

/* ctorA (allocation constructor) 
   optionally copy content of raw pointers to `frames` by assigned `num_frames` */
    explicit
    byte_buffer(size_t _num_frames, TYPE* _frames = nullptr) noexcept
        : frames(new TYPE[_num_frames]{})
        , num_frames(_num_frames)
    {
        if (_frames) std::copy(_frames, _frames + _num_frames, frames);

        taglog("<A|CP> byte_buffer::ctorAC (size_t _num_frames%s)\n"
        , (_frames)?(""):(", TYPE* _frames"));
    }

/* cpctor (copy constructor) */
    byte_buffer(const byte_buffer& _src)
        : byte_buffer(_src.num_frames, _src.frames)
    {
        taglog("<COPY> byte_buffer::cpctor (const byte_buffer& _src)\n");
    }

/* mvctor (move constructor) */
    byte_buffer(byte_buffer&& _src) noexcept
        : frames(_src.frames)
        , num_frames(_src.num_frames)
    {
        _src.frames = nullptr;
        _src.num_frames = 0;

        taglog("<MOVE> byte_buffer::mvctor (byte_buffer&& _src)\n");
    }

/* copy= (copy assignment operator) */
    void
    operator=(const byte_buffer& _rhs)
    {
        if (num_frames == _rhs.num_frames) 
        {
            std::copy(_rhs.frames, _rhs.frames + num_frames, frames);
        } 
        else // if num_frames are different, create new instance
        {
            *this = byte_buffer(_rhs);
        }

        taglog("<%s> byte_buffer::copy=  (const byte_buffer& _rhs)\n"
        , (num_frames == _rhs.num_frames)?("COPY"):("    "));
    }

/* move= (move assignment operator) */
    void
    operator=(byte_buffer&& _rhs) noexcept
    {
        std::swap(frames, _rhs.frames);
        std::swap(num_frames, _rhs.num_frames);

        taglog("<MOVE> byte_buffer::move=  (byte_buffer&& _rhs)\n");
    }

// custom method section :

/* paste (paste content of `frames` to raw pointers by assigned `num_frames`) */
    void
    paste(TYPE* _des, size_t _num_frames) noexcept
    {
        std::copy(frames, frames + _num_frames, _des);

        taglog("<COPY> byte_buffer::paste  (TYPE* _des, size_t _num_frames)\n");
    }

/* paste (paste content of `frames` to raw pointers by default `num_frames`) */
    void
    paste(TYPE* _des) noexcept
    {
        std::copy(frames, frames + num_frames, _des);

        taglog("<COPY> byte_buffer::paste  (TYPE* _des)\n");
    }

/* copy (copy content of raw pointers to `frames` by assigned `num_frames`) */
    void
    copy(TYPE* _src, size_t _num_frames) noexcept
    {
        std::copy(_src, _src + _num_frames, frames);

        taglog("<COPY> byte_buffer::copy   (TYPE* _src, size_t _num_frames)\n");
    }

/* copy (copy content of raw pointers to `frames` by default `num_frames`) */
    void
    copy(TYPE* _src) noexcept
    {
        std::copy(_src, _src + num_frames, frames);

        taglog("<COPY> byte_buffer::copy   (TYPE* _src)\n");
    }

};

#endif //CIIS_BYTE_BUFFER_H
