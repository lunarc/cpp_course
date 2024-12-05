#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <execution>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <print>
#include <random>
#include <ranges>
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
    auto lambda = [&z, &a, &x, &y, &n](long start, long end) {
        for (long i = start; i < end; i++)
            z[i] = a * x[i] + y[i];
    };

    jthread t1(lambda, 0, n / 2);
    jthread t2(lambda, n / 2, n);

    // t1.join();
    // t2.join();
}

int main()
{
    const int N = 300000000;

    std::print("Allocatingh arrays...\n");

    auto startTimeAlloc = std::chrono::high_resolution_clock::now();
    auto x = std::make_unique< double[] >(N);
    auto y = std::make_unique< double[] >(N);
    auto z = std::make_unique< double[] >(N);
    auto endTimeAlloc = std::chrono::high_resolution_clock::now();

    std::print("Initialising arrays x, y ...\n");

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution< double > dist;

    auto startTimeInit = std::chrono::high_resolution_clock::now();
    std::for_each(x.get(), x.get() + N, [&gen, &dist](double &v) { v = dist(gen); });
    std::for_each(y.get(), y.get() + N, [&gen, &dist](double &v) { v = dist(gen); });
    auto endTimeInit = std::chrono::high_resolution_clock::now();

    std::print("Starting threaded saxpy calculation...\n");

    auto startTimeThreads = std::chrono::high_resolution_clock::now();
    saxpy(z.get(), 3.14, x.get(), y.get(), N);
    auto endTimeThreads = std::chrono::high_resolution_clock::now();

    std::print("Starting serial saxpy calculation...\n");

    auto startTimeSerial = std::chrono::high_resolution_clock::now();
    saxpy_serial(z.get(), 3.14, x.get(), y.get(), N);
    auto endTimeSerial = std::chrono::high_resolution_clock::now();

    double timeAlloc = std::chrono::duration< double >(endTimeAlloc - startTimeAlloc).count();
    double timeInit = std::chrono::duration< double >(endTimeInit - startTimeInit).count();
    double timeThreads = std::chrono::duration< double >(endTimeThreads - startTimeThreads).count();
    double timeSerial = std::chrono::duration< double >(endTimeSerial - startTimeSerial).count();

    std::print("Alloc time = {} seconds.\n", timeAlloc);
    std::print("Init time = {} seconds.\n", timeInit);
    std::print("Thread execution time = {} seconds.\n", timeThreads);
    std::print("Serial execution time = {} seconds.\n", timeSerial);
    std::print("Speedup = {}\n", timeSerial / timeThreads);

    return 0;
}
