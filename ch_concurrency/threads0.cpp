#include <chrono>
#include <iostream>
#include <thread>
#include <utils/print.h>

using namespace std;

std::string to_string(std::thread::id id)
{
    std::stringstream ss;
    ss << id;
    return ss.str();
}

void myfunc()
{
    std::printf("Thread {} starting.\n", to_string(this_thread::get_id()));
    this_thread::sleep_for(chrono::seconds(1));
    std::printf("Thread {} stopping.\n", to_string(this_thread::get_id()));
}

int main()
{
    jthread t(myfunc);
    t.join();
    std::print("Main thread stopping.\n");
}
