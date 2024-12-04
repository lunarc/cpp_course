#include <chrono>
#include <iostream>
#include <print>
#include <thread>
#include <vector>

void myfunc()
{
    std::print("Thread {0} starting.\n", std::this_thread::get_id());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::print("Thread {0} stopping.\n", std::this_thread::get_id());
}

int main()
{
    std::print("I have {0} hardware threads.\n", std::thread::hardware_concurrency());

    std::vector< std::jthread > threads;

    std::print("Starting threads...\n");

    for (auto i = 0; i < 10; i++)
        threads.push_back(std::jthread(myfunc));

    std::print("Waiting for threads to complete...\n");

    for (auto &thread : threads)
        thread.join();

    std::print("Completed...\n");
}
