#include <chrono>
#include <print>
#include <random>
#include <thread>

#include "safe_queue.h"

void producer(SafeQueue< int > &queue, int id, int itemCount)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    std::uniform_int_distribution<> sleep(10, 100);

    for (int i = 0; i < itemCount; ++i)
    {
        int value = dis(gen);
        queue.push(value);
        std::println("Producer {} produced: {}", id, value);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep(gen)));
    }

    std::println("Producer {} finished", id);
}

void consumer(SafeQueue< int > &queue, int id, std::atomic< int > &totalConsumed)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> sleep(50, 150);

    while (true)
    {
        auto item = queue.pop();

        if (!item.has_value())
        {
            std::println("Consumer {} finished (no more items)", id);
            break;
        }

        std::println("Consumer {} consumed: {}", id, item.value());
        totalConsumed++;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep(gen)));
    }
}

int main()
{
    const int numProducers = 3;
    const int numConsumers = 2;
    const int itemsPerProducer = 5;

    SafeQueue< int > queue(5); // Buffer size of 5
    std::atomic< int > totalConsumed{0};

    std::println("Starting {} producers and {} consumers", numProducers, numConsumers);
    std::println("Each producer will create {} items\n", itemsPerProducer);

    // Start producers
    std::vector< std::jthread > producers;
    for (int i = 0; i < numProducers; ++i)
        producers.emplace_back(producer, std::ref(queue), i, itemsPerProducer);

    // Start consumers
    std::vector< std::jthread > consumers;
    for (int i = 0; i < numConsumers; ++i)
        consumers.emplace_back(consumer, std::ref(queue), i, std::ref(totalConsumed));

    // Wait for all producers to finish
    producers.clear(); // jthread joins on destruction

    std::println("\nAll producers finished. Signaling consumers...");
    queue.finish();

    // Wait for all consumers to finish
    consumers.clear();

    std::println("\nTotal items produced: {}", numProducers * itemsPerProducer);
    std::println("Total items consumed: {}", totalConsumed.load());

    return 0;
}
