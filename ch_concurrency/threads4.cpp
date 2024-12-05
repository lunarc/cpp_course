#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

using namespace std;

void saxpy_serial(double z[], double a, double x[], double y[], long n)
{
    for (long i = 0; i < n; i++)
        z[i] = a * x[i] + y[i];
}

void saxpy(double z[], double a, double x[], double y[], long n)
{
    auto lambda = [z, a, x, y, n](long start, long end) {
        for (long i = start; i < end; i++)
            z[i] = a * x[i] + y[i];
    };

    jthread t1(lambda, 0, n / 2);
    jthread t2(lambda, n / 2, n);

    t1.join();
    t2.join();
}

int main()
{
    const int N = 100000000;

    auto x = new double[N];
    auto y = new double[N];
    auto z = new double[N];

    for (auto i = 0; i < N; i++)
    {
        x[i] = rand();
        y[i] = rand();
    }

    clock_t startTimeThreads = clock();
    saxpy(z, 3.14, x, y, N);
    clock_t endTimeThreads = clock();

    clock_t startTimeSerial = clock();
    saxpy_serial(z, 3.14, x, y, N);
    clock_t endTimeSerial = clock();

    double timeThreads = (double(endTimeThreads) - double(startTimeThreads)) / CLOCKS_PER_SEC;
    double timeSerial = (double(endTimeSerial) - double(startTimeSerial)) / CLOCKS_PER_SEC;

    cout << "Serial execution time = " << timeSerial << " seconds." << endl;
    cout << "Thread execution time = " << timeThreads << " seconds." << endl;

    delete[] x;
    delete[] y;
    delete[] z;

    return 0;
}
