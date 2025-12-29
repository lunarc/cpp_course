#include <chrono>
#include <memory>
#include <thread>
#include <print>
#include <vector>

using namespace std;

void saxpy_serial(double z[], double a, double x[], double y[], long n)
{
    std::println("Performing SAXPY serially.");

    for (long i = 0; i < n; i++)
        z[i] = a * x[i] + y[i];
}

void saxpy(double z[], double a, double x[], double y[], long n)
{
    const auto numThreads = std::min(8u, std::thread::hardware_concurrency());

    std::println("Performing SAXPY with {0} threads.", numThreads);
    
    auto lambda = [z, a, x, y](long start, long end) {
        for (long i = start; i < end; i++)
            z[i] = a * x[i] + y[i];
    };

    std::vector<std::jthread> threads;
    long chunkSize = n / numThreads;

    std::print("Chunk size = {0}\n", chunkSize);
    
    for (unsigned int i = 0; i < numThreads; i++)
    {
        long start = i * chunkSize;
        long end = (i == numThreads - 1) ? n : (i + 1) * chunkSize;
        threads.emplace_back(lambda, start, end);
    }
    
    // jthread automatically joins on destruction
}

int main()
{
    const int N = 200000000; // 100 million elements

    std::print("Allocating arrays of size N = {0}...\n", N);
    std::print("Allocated size in MB = {0}\n", (3 * N * sizeof(double)) / (1024.0 * 1024.0));

    auto x = std::make_unique<double[]>(N);
    auto y = std::make_unique<double[]>(N);
    auto z = std::make_unique<double[]>(N);

    for (auto i = 0; i < N; i++)
    {
        x[i] = static_cast<double>(i);
        y[i] = static_cast<double>(i * 2);
    }

    auto startTimeThreads = std::chrono::high_resolution_clock::now();
    saxpy(z.get(), 3.14, x.get(), y.get(), N);
    auto endTimeThreads = std::chrono::high_resolution_clock::now();

    std::print("Completed SAXPY (threaded) with N = {0} elements.\n", N);

    auto startTimeSerial = std::chrono::high_resolution_clock::now();
    saxpy_serial(z.get(), 3.14, x.get(), y.get(), N);
    auto endTimeSerial = std::chrono::high_resolution_clock::now();

    std::print("Completed SAXPY (serial) with N = {0} elements.\n", N);

    auto timeThreads = std::chrono::duration<double>(endTimeThreads - startTimeThreads).count();
    auto timeSerial = std::chrono::duration<double>(endTimeSerial - startTimeSerial).count();

    std::print("Serial execution time = {0} seconds.\n", timeSerial);
    std::print("Thread execution time = {0} seconds.\n", timeThreads);
    std::print("Speedup = {0}x\n", timeSerial / timeThreads);

    return 0;
}
