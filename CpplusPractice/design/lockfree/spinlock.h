#ifndef CIIS_SPINLOCK_H
#define CIIS_SPINLOCK_H

#include <atomic>
#include <thread>

/**
 * spinlock : atomic flag based spinlock, thread-safe for MPMC
 * 
 * - enter() | lock, enter the active section
 * - leave() | unlock, leave the recent active section
 */
class spinlock {
protected:
    std::atomic_flag lock{};

// internal method :

/* rename enum memory_order */
    static constexpr inline std::memory_order
    MO_ACQ = std::memory_order_acquire,
    MO_REL = std::memory_order_release;

public:
// basic method :
    spinlock(){}

// custom method :

/* acquire the lock (spinlock - lock) */
    void
    enter()
    {
        while (lock.test_and_set(MO_ACQ))
        {
            std::this_thread::yield();
        }
    }

/* release the lock (spinlock - unlock) */
    void
    leave()
    {
        lock.clear(MO_REL);
    }

// any copy and move operation is not recommended :
    spinlock(const spinlock&)          = delete;
    spinlock(spinlock&&)               = delete;
    void operator=(const spinlock&)    = delete;
    void operator=(spinlock&&)         = delete;
};

#endif //CIIS_SPINLOCK_H
