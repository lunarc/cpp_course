#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <cmath>
#include <ctime>

using namespace std;

double sum(double* array, int start, int stop)
{
    auto sum = 0.0;
    for (auto i=start; i<stop; i++)    
        sum += array[i];
    return sum;
}

int main()
{
    cout << "Number of threads = " << thread::hardware_concurrency() << endl;

    auto N = 1000000000;
    
    double* array = new double[N];
    
    for (auto i=0; i<N; i++)
        array[i] = rand();
    
    auto lambda = [&](int start, int stop) -> double
    {
        return sum(array, start, stop);
    };
    
    cout << "Launching threads..." << endl;
    clock_t t1_async = clock();
    future<double> f1 = async(launch::async, lambda, 0, N/4);
    future<double> f2 = async(launch::async, lambda, N/4, N/2);
    future<double> f3 = async(launch::async, lambda, N/2, N/2+N/4);
    future<double> f4 = async(launch::async, lambda, N/2+N/4, N);    
    auto sum1 = f1.get();
    auto sum2 = f2.get();
    auto sum3 = f3.get();
    auto sum4 = f4.get();    
    clock_t t2_async = clock();

    auto totalSumAsync = sum1 + sum2 + sum3 + sum4;

    cout << "Launching serial..." << endl;
    clock_t t1_serial = clock();
    auto totalSumSerial = sum(array, 0, N);
    clock_t t2_serial = clock();
    cout << "Done..." << endl;

    double t_async = (double(t2_async) - double(t1_async)) / CLOCKS_PER_SEC;
    double t_serial = (double(t2_serial) - double(t1_serial)) / CLOCKS_PER_SEC;    
    
    cout << "Total time async() = " << t_async << " seconds." << endl;
    cout << "Total sum from serial = " << t_serial << " seconds." << endl;        
        
    return 0;        
}
    
    
