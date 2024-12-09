#include <chrono>
#include <iostream>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <thread>
#include <vector>
#include <sstream>

void myfunc()
{
    std::stringstream idStr;
    idStr << std::this_thread::get_id();

    fmt::print("Thread {} starting.\n", idStr.str());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    fmt::print("Thread {} stopping.\n", idStr.str());
}

int main()
{
    fmt::print("I have {0} hardware threads.\n", std::thread::hardware_concurrency());

    std::vector< std::jthread > threads;

    fmt::print("Starting threads...\n");

    for (auto i = 0; i < 10; i++)
        threads.push_back(std::jthread(myfunc));

    fmt::print("Waiting for threads to complete...\n");

    for (auto &thread : threads)
        thread.join();

    fmt::print("Completed...\n");
}
