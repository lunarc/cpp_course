#include <chrono>
#include <iostream>
#include <utils/print.h>
#include <thread>
#include <vector>
#include <sstream>

void myfunc()
{
    std::stringstream idStr;
    idStr << std::this_thread::get_id();

    utils::print("Thread {} starting.\n", idStr.str());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    utils::print("Thread {} stopping.\n", idStr.str());
}

int main()
{
    utils::print("I have {0} hardware threads.\n", std::thread::hardware_concurrency());

    std::vector< std::jthread > threads;

    utils::print("Starting threads...\n");

    for (auto i = 0; i < 10; i++)
        threads.push_back(std::jthread(myfunc));

    utils::print("Waiting for threads to complete...\n");

    for (auto &thread : threads)
        thread.join();

    utils::print("Completed...\n");
}
