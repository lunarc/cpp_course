#include <chrono>
#include <utils/print.h>
#include <thread>
#include <iostream>

using namespace std;


void myfunc()
{
    utils::print("Thread {} starting.\n", utils::to_string(this_thread::get_id()));
    this_thread::sleep_for(chrono::seconds(1));
    utils::print("Thread {} stopping.\n", utils::to_string(this_thread::get_id()));
}

int main()
{
    jthread t(myfunc);
    t.join();
    utils::print("Main thread stopping.\n");
}
