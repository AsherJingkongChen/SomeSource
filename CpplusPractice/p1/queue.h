#ifndef CPPLUSPRAC1_QUEUE_H
#define CPPLUSPRAC1_QUEUE_H

#include <queue>
#include <optional>

/**
 * Abstract class `queue` with template
 */

/**
 * void enqueue(const T& newMember_);
 * std::optional<T> dequeue();
 * bool isFull() const;
 * bool isEmpty() const;
 * size_t get_size() const;
 * std::optional<T> get_oldest() const;
 * std::optional<T> get_newest() const;
 *
 * @tparam T
 * @tparam CAPACITY
 */

template <typename T, size_t CAPACITY>
class queue {
public:
    virtual void enqueue(const T& newMember_) {
        if (isFull()) return;

        base_queue.push(newMember_);
    }

    virtual std::optional<T> dequeue() {
        if (isEmpty()) return {};

        T left = base_queue.front();
        base_queue.pop();
        return left;
    }

    virtual bool isFull() const {
        return (get_size() == CAPACITY);
    }

    virtual bool isEmpty() const {
        return (base_queue.empty());
    }

    virtual size_t get_size() const {
        return base_queue.size();
    }

    virtual std::optional<T> get_oldest() const {
        return base_queue.front();
    }

    virtual std::optional<T> get_newest() const {
        if (isEmpty()) return {};
        return base_queue.back();
    }

protected:
    std::queue<T> base_queue;

};

#endif //CPPLUSPRAC1_QUEUE_H
