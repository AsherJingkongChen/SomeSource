/**
 * task_queue,
 * 
 * A C++ Version of lock-free queue,
 * guarantees lock-free & thread-safe on SPSC case.
 *
 * Based on atomic and ring-buffer, No mutex, sync-locks.
 * Self-documenting & Easy naming codes.
 *
 * Whether objects are copied or moved depends on you.
 * 
 * "Simple to use"
 * 
 * - Single Constructor which determines the capacity (rule of zero)
 *
 * - void enqueue(const TYPE &) / void enqueue(TYPE &&)
 *     => copy/move assignment
 *
 * - TYPE dequeue() / void dequeue(TYPE &)
 *     => copy/move assignment
 *
 * - void reset()
 *     => set "size" to zero after both threads are manually stopped
 *
 * - that's all!
 */

#ifndef CIIS_LOCKFREE_TASK_QUEUE_H
#define CIIS_LOCKFREE_TASK_QUEUE_H

#include <atomic>
#include <cstdint>
#include <thread>

/*
 * lock-free FIFO container
 * guarantees lock-free & thread-safe on SPSC case
 */
template<class TYPE>
class task_queue {
private:
    std::atomic<uint32_t>     in{};
    std::atomic<uint32_t>     out{};
    uint32_t                  cap;
    TYPE*                     buf;

// internal method :

/* rename enum std::memory_order */
    static constexpr inline std::memory_order  
    MO_RLX = std::memory_order_relaxed,
    MO_ACQ = std::memory_order_acquire,
    MO_REL = std::memory_order_release;

/* reduce capacity down to 2^N */
    static constexpr inline uint32_t
    Fit(uint32_t c)
    {
        // for 32-bit integer
        c--;
        c |= c >> 1;
        c |= c >> 2;
        c |= c >> 4;
        c |= c >> 8;
        c |= c >> 16;
        c++;

        return c;
    }

/* index masker */
    static constexpr inline uint32_t
    At(uint32_t p, uint32_t c) 
    {
        return p & (c - 1);
    }

/* if full, delay enqueue */
    static constexpr inline bool
    Full(uint32_t i, uint32_t o, uint32_t c) 
    {
        return i - o == c;
    }

/* if empty, delay dequeue */
    static constexpr inline bool
    Empty(uint32_t i, uint32_t o) 
    {
        return i == o;
    }

/* request to enqueue */
    inline void
    req_enq()
    {
        // wait for `out` updated
        while (Full(
            in.load(MO_RLX), 
            out.load(MO_ACQ),
            cap))
        {
            std::this_thread::yield();
        }
    }

/* request to dequeue */
    inline void
    req_deq()
    {
        // wait for `in` updated
        while (Empty(
            in.load(MO_ACQ), 
            out.load(MO_RLX)))
        {
            std::this_thread::yield();
        }
    }

public:
// basic method :

/* dtor (destructor) */
    ~task_queue()
    {
        delete[] buf;
        buf = nullptr;

        cap = 0;
    }

/* ctorA (allocation constructor) */
    explicit
    task_queue(uint32_t capacity)
        : cap(Fit(capacity))
        , buf(new TYPE[cap]{}) {}

// custom method :

/* enqueue, push, or write (copy assignment) */
    void
    enqueue(const TYPE& input)
    {
        req_enq();

        // copy assigment operator
        buf[At(in.load(MO_RLX), cap)] = input;

        in.fetch_add(1, MO_REL);
    }

/* enqueue, push, or write (move assignment) */
    void
    enqueue(TYPE&& input)
    {
        req_enq();

        // move assignment operator
        buf[At(in.load(MO_RLX), cap)] = std::move(input);

        in.fetch_add(1, MO_REL);
    }

/* dequeue, pop, or read (copy assignment) */
    TYPE
    dequeue()
    {
        req_deq();

        // copy constructor
        TYPE output(buf[ At(out.load(MO_RLX), cap) ]);

        out.fetch_add(1, MO_REL);

        return output;
    }
    
/* dequeue, pop, or read (move assignment) */
    void
    dequeue(TYPE& output)
    {
        req_deq();

        // move assignment operator
        output = std::move(buf[ At(out.load(MO_RLX), cap) ]);

        out.fetch_add(1, MO_REL);
    }

/* reset (do it after reader and writer being manually stopped) */
    void
    reset()
    {
        out.store(in.load(MO_ACQ), MO_REL);
    }

// any copy and move operation is not recommended :
    task_queue(const task_queue&)       = delete;
    task_queue(task_queue&&)            = delete;
    void operator=(const task_queue&)   = delete;
    void operator=(task_queue&&)        = delete;
};

#endif //CIIS_LOCKFREE_TASK_QUEUE_H
