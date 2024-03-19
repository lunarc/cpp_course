#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void myfunc()
{
    cout << "Thread " << this_thread::get_id() << " starting." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Thread " << this_thread::get_id() << " stopping." << endl;
}

int main()
{
    thread t(myfunc);
    t.join();
}
    
    