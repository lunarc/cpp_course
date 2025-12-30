#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

template < typename T > class SafeQueue {
private:
    std::queue< T > m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_cond;
    bool m_finished = false;
    size_t m_maxSize;

public:
    SafeQueue(size_t maxSize = 10) : m_maxSize(maxSize)
    {
    }

    // Producer: Add item to queue (blocks if full)
    void push(T item)
    {
        std::unique_lock< std::mutex > lock(m_mutex);

        // Wait until queue has space
        m_cond.wait(lock, [this]() { return m_queue.size() < m_maxSize || m_finished; });

        if (!m_finished)
        {
            m_queue.push(std::move(item));
            m_cond.notify_one(); // Notify a waiting consumer
        }
    }

    // Consumer: Remove item from queue (blocks if empty)
    std::optional< T > pop()
    {
        std::unique_lock< std::mutex > lock(m_mutex);

        // Wait until queue has data or is finished
        m_cond.wait(lock, [this]() { return !m_queue.empty() || m_finished; });

        if (m_queue.empty())
            return std::nullopt; // No more data

        T item = std::move(m_queue.front());
        m_queue.pop();
        m_cond.notify_one(); // Notify a waiting producer
        return item;
    }

    // Signal that no more items will be produced
    void finish() 
    {
        std::unique_lock< std::mutex > lock(m_mutex);
        m_finished = true;
        m_cond.notify_all(); // Wake all waiting threads
    }

    size_t size() const
    {
        std::unique_lock< std::mutex > lock(m_mutex);
        return m_queue.size();
    }
};
