#include <chrono>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <thread>
#include <iostream>

using namespace std;


void myfunc()
{
    //fmt::print("Thread {} starting.\n", this_thread::get_id());
    cout << "Thread " << this_thread::get_id() << " starting." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    //fmt::print("Thread {} stopping.\n", this_thread::get_id());
    cout << "Thread " << this_thread::get_id() << " stopping." << endl;
}

int main()
{
    jthread t(myfunc);
    t.join();
    fmt::print("Main thread stopping.\n");
}
