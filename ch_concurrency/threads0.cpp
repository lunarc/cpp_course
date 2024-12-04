#include <chrono>
#include <print>
#include <thread>

using namespace std;

void myfunc()
{
    std::print("Thread {0} starting.\n", this_thread::get_id());
    this_thread::sleep_for(chrono::seconds(1));
    std::print("Thread {0} stopping.\n", this_thread::get_id());
}

int main()
{
    jthread t(myfunc);
    t.join();
    std::printf("Main thread stopping.\n");
}
