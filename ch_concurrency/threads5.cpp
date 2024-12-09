#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <ctime>
#include <execution>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <random>
#include <ranges>
#include <thread>
#include <vector>

using namespace std;

// Function to perform a computationally intensive task
void heavyComputation(double *arr, size_t start, size_t end)
{
    for (size_t i = start; i < end; ++i)
    {
        arr[i] = std::sin(arr[i]) * std::cos(arr[i]) * std::sqrt(std::abs(arr[i]));
        for (int j = 0; j < 1000; ++j)
        {
            arr[i] = std::sin(arr[i]);
        }
    }
}

// Function to process data sequentially
void processSequential(double *data, size_t size)
{
    heavyComputation(data, 0, size);
}

void processParallel(double *data, size_t size, int numThreads)
{
    std::vector< std::jthread > threads;
    std::atomic< double > sum{0.0};
    threads.reserve(numThreads);

    size_t chunkSize = size / numThreads;

    for (int i = 0; i < numThreads; ++i)
    {
        size_t start = i * chunkSize;
        size_t end = (i == numThreads - 1) ? size : (i + 1) * chunkSize;
        threads.emplace_back(heavyComputation, data, start, end);
    }

    /*
    for (auto &thread : threads)
    {
        thread.join();
    }
    */
}

int main()
{
    const size_t dataSize = 5000000;
    int numThreads = std::thread::hardware_concurrency();

    std::printf("Data size: %zu\n", dataSize);
    std::printf("Number of threads: %d\n", numThreads);

    std::printf("Allocating arrays...\n");

    auto seqData = std::make_unique< double[] >(dataSize);
    auto parData = std::make_unique< double[] >(dataSize);

    std::printf("Initialising arrays...\n");

    std::generate_n(seqData.get(), dataSize, []() { return 1.0; });

    std::printf("Running serially...\n");

    auto start = std::chrono::high_resolution_clock::now();
    processSequential(seqData.get(), dataSize);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration< double > elapsedSerially = end - start;
    std::printf("Time for sequential processing: %f seconds\n", elapsedSerially.count());

    std::printf("Running in parallel...\n");

    start = std::chrono::high_resolution_clock::now();
    processParallel(parData.get(), dataSize, numThreads);
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration< double > elapsedParallel = end - start;

    std::printf("Time for parallel processing: %f seconds\n", elapsedParallel.count());
    std::printf("Speedup: %f\n", elapsedSerially.count() / elapsedParallel.count());

    return 0;
}
