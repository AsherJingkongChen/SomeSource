#ifndef CIIS_BYTE_BUFFER_H
#define CIIS_BYTE_BUFFER_H

#include <cstdint>
#include <algorithm>
#include <functional>

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
 * byte_buffer<TYPE>, a simple copy-and-paste buffer
 * 
 * :: TYPE*   frames      | array  of frames
 * :: uint32_t  num_frames  | number of frames 
 * 
 * byte_buffer<TYPE> ~ TYPE frames[num_frames]
 * 
 * -- the contained data type should be either copyable or movable --
 */
template <class TYPE>
class byte_buffer {
protected:
    TYPE*       frames;
    uint32_t    num_frames;

public:
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
        taglog("<DECL> byte_buffer::ctor0  ()\n");
    }

/* ctorA (allocation constructor, requiring `num_frames`, optionally copy raw pointer) */
    explicit
    byte_buffer(uint32_t _num_frames, TYPE* _frames = nullptr) noexcept
        : frames(new TYPE[_num_frames]{})
        , num_frames(_num_frames)
    {
        if (_frames) std::copy(_frames, _frames + _num_frames, frames);

        taglog("<ALOC> byte_buffer::ctorA (uint32_t _num_frames%s)\n"
        , (_frames)?(", TYPE* _frames"):(""));
    }

/* cpctor (copy constructor) */
    byte_buffer(const byte_buffer& _src)
        : frames(new TYPE[_src.num_frames]{})
        , num_frames(_src.num_frames)
    {
        if (_src.frames) std::copy(_src.frames, _src.frames + _src.num_frames, frames);

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

/* paste (copy content of `frames` to raw pointers by assigned `num_frames`) */
    void
    paste(TYPE* _des, uint32_t _num_frames) noexcept
    {
        std::copy(frames, frames + _num_frames, _des);

        taglog("<COPY> byte_buffer::paste  (TYPE* _des, uint32_t _num_frames)\n");
    }

/* paste (copy content of `frames` to raw pointers by default `num_frames`) */
    void
    paste(TYPE* _des) noexcept
    {
        std::copy(frames, frames + num_frames, _des);

        taglog("<COPY> byte_buffer::paste  (TYPE* _des)\n");
    }

/* copy (copy content of raw pointers to `frames` by assigned `num_frames`) */
    void
    copy(TYPE* _src, uint32_t _num_frames) noexcept
    {
        std::copy(_src, _src + _num_frames, frames);

        taglog("<COPY> byte_buffer::copy   (TYPE* _src, uint32_t _num_frames)\n");
    }

/* copy (copy content of raw pointers to `frames` by default `num_frames`) */
    void
    copy(TYPE* _src) noexcept
    {
        std::copy(_src, _src + num_frames, frames);

        taglog("<COPY> byte_buffer::copy   (TYPE* _src)\n");
    }

/* for_each_frame<bool>(buf, [](auto& b){ b = !b; }); */
    template<class TYPE_R>
    friend void 
    for_each_frame(
        const byte_buffer<TYPE_R>& _result,
        std::function<void (TYPE_R&)> _unary_operator)
    {
        TYPE_R* R_IE = _result.frames + _result.num_frames;
        TYPE_R* R_II = _result.frames;
        
        while (R_II != R_IE)
        {
            _unary_operator(*R_II++);
        }
    }

/* for_each_frame<int64_t, int32_t>(rbuf, obuf, [](auto& r, auto& o){ r = o / 3; }); */
    template<class TYPE_R, class TYPE_O>
    friend void
    for_each_frame(
        const byte_buffer<TYPE_R>& _result,
        const byte_buffer<TYPE_O>& _operand, 
        std::function<void (TYPE_R&, TYPE_O&)> _binary_operator)
    {
        if (_result.num_frames != _operand.num_frames) return;

        TYPE_R* R_IE = _result.frames + _result.num_frames;
        TYPE_R* R_II = _result.frames;
        TYPE_O* O_II = _operand.frames;
        
        while (R_II != R_IE)
        {
            _binary_operator(*R_II++, *O_II++);
        }
    }
};

/* friend of byte_buffer */
template<class TYPE, class TYPE_R>
void 
for_each_frame(
    const byte_buffer<TYPE_R>&,
    std::function<void (TYPE_R&)>);

/* friend of byte_buffer */
template<class TYPE, class TYPE_R, class TYPE_O>
void
for_each_frame(
    const byte_buffer<TYPE_R>&,
    const byte_buffer<TYPE_O>&, 
    std::function<void (TYPE_R&, TYPE_O&)>);

#endif //CIIS_BYTE_BUFFER_H
