#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

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
    auto numThreads = thread::hardware_concurrency();

    cout << "I have " << numThreads << " hardware threads." << endl;
    
    vector<jthread> threads;
    
    cout << "Starting threads..." << endl;
    
    for (auto i=0; i<numThreads; i++)
        threads.emplace_back(myfunc);
        
    cout << "Waiting for thread completion..." << endl;
    
    for (auto& thread : threads)
        thread.join();
}
    
    