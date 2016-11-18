#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

mutex g_output;

void myfunc()
{
    g_output.lock();
    cout << "Thread " << this_thread::get_id() << " starting." << endl;
    g_output.unlock();
    
    this_thread::sleep_for(chrono::seconds(1));
    
    g_output.lock();
    cout << "Thread " << this_thread::get_id() << " stopping." << endl;
    g_output.unlock();
}

int main()
{
    cout << "I have " << thread::hardware_concurrency() << " hardware threads." << endl;
    
    vector<thread> threads;
    
    cout << "Starting threads..." << endl;
    
    for (auto i=0; i<10; i++)
        threads.push_back(thread(myfunc));
        
    cout << "Waiting for thread completion..." << endl;
    
    for (auto& thread : threads)
        thread.join();
}
    
    