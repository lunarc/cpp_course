#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <print>


// Shared resource that multiple threads will modify
int g_counter = 0;
std::mutex g_counter_mutex;

void increment_counter_unsafe(int iterations)
{
    for (auto i = 0; i < iterations; i++)
        g_counter++;
}

void increment_counter_safe(int iterations)
{
    for (auto i = 0; i < iterations; i++)
    {
        std::lock_guard<std::mutex> lock(g_counter_mutex);
        g_counter++;
    }
}

int main()
{
    const int num_threads = 10;
    const int iterations_per_thread = 100000;
    
    // Test 1: Without mutex (race condition)
 
    std::println("Test 1: WITHOUT mutex protection");
    g_counter = 0;
    
    {
        std::vector<std::jthread> threads;
        for (int i = 0; i < num_threads; i++)
            threads.emplace_back(increment_counter_unsafe, iterations_per_thread);
    }

    std::println("Expected: {}", num_threads * iterations_per_thread);
    std::println("Actual:   {}", g_counter);
    std::println("Lost updates: {}", num_threads * iterations_per_thread - g_counter);
    
    // Test 2: With mutex (correct)
    std::println("Test 2: WITH mutex protection (using lock_guard)");
    g_counter = 0;
    
    {
        std::vector<std::jthread> threads;
        for (int i = 0; i < num_threads; i++)
            threads.emplace_back(increment_counter_safe, iterations_per_thread);
    }
    
    std::println("Expected: {}", num_threads * iterations_per_thread);
    std::println("Actual:   {}", g_counter);
    std::println("Lost updates: {}", num_threads * iterations_per_thread - g_counter);
    
    return 0;
}