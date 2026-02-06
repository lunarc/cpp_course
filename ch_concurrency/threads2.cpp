#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <sstream>
#include <print>

void myfunc()
{
    std::stringstream idStr;
    idStr << std::this_thread::get_id();

    std::print("Thread {} starting.\n", idStr.str());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::print("Thread {} stopping.\n", idStr.str());
}

int main()
{
    auto numThreads = std::thread::hardware_concurrency();

    std::print("I have {0} hardware threads.\n", numThreads);

    std::vector< std::jthread > threads;

    std::print("Starting threads...\n");

    for (auto i = 0; i < numThreads; i++)
        threads.emplace_back(myfunc);

    std::print("Waiting for threads to complete...\n");

    for (auto &thread : threads)
        thread.join();

    std::print("Completed...\n");
}
