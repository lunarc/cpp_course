#include <iostream>
#include <vector>
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
    cout << "I have " << thread::hardware_concurrency() << " hardware threads." << endl;
    
    vector<thread> threads;
    
    cout << "Starting threads..." << endl;
    
    for (auto i=0; i<10; i++)
        threads.push_back(thread(myfunc));
        
    cout << "Waiting for thread completion..." << endl;
    
    for (auto& thread : threads)
        thread.join();
}
    
    