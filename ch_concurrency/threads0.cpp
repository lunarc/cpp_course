#include <chrono>
#include <iostream>
#include <print>
#include <thread>

using namespace std;

std::string to_string(std::thread::id id)
{
    std::stringstream ss;
    ss << id;
    return ss.str();
}

void myfunc()
{
    std::print("Thread {} starting.\n", to_string(this_thread::get_id()));
    this_thread::sleep_for(chrono::seconds(1));
    std::print("Thread {} stopping.\n", to_string(this_thread::get_id()));
}

int main()
{
    jthread t(myfunc);
    t.join();
    std::printf("Main thread stopping.\n");
}
