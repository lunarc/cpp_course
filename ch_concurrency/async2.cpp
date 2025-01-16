#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <ctime>
#include <execution>
#include <future>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <random>
#include <ranges>
#include <thread>
#include <vector>

using namespace std;

// Function to perform a computationally intensive task
double heavyComputation(double *arr, size_t start, size_t end)
{
    double localSum = 0.0;

    for (size_t i = start; i < end; ++i)
    {
        arr[i] = std::sin(arr[i]) * std::cos(arr[i]) * std::sqrt(std::abs(arr[i]));
        for (int j = 0; j < 1000; ++j)
        {
            arr[i] = std::sin(arr[i]);
        }
        localSum += arr[i];
    }

    return localSum;
}

// Function to process data sequentially
double processSequential(double *data, size_t size)
{
    return heavyComputation(data, 0, size);
}

double processAsync(double *data, size_t size, int numThreads)
{
    std::vector< std::future< double > > futures;
    size_t chunkSize = size / numThreads;

    for (int i = 0; i < numThreads; ++i)
    {
        size_t start = i * chunkSize;
        size_t end = (i == numThreads - 1) ? size : (i + 1) * chunkSize;
        futures.push_back(std::async(std::launch::async, heavyComputation, data, start, end));
    }

    double sum = 0.0;

    for (auto &future : futures)
    {
        sum += future.get();
    }

    return sum;
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
    double seqSum{0.0};
    double parSum{0.0};

    std::printf("Initialising arrays...\n");

    std::generate_n(seqData.get(), dataSize, []() { return 1.0; });
    std::generate_n(parData.get(), dataSize, []() { return 1.0; });

    std::printf("Running serially...\n");

    auto start = std::chrono::high_resolution_clock::now();
    seqSum = processSequential(seqData.get(), dataSize);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration< double > elapsedSerially = end - start;
    std::printf("Time for sequential processing: %f seconds\n", elapsedSerially.count());
    std::printf("Sum: %f\n", seqSum);

    std::printf("Running in parallel...\n");

    start = std::chrono::high_resolution_clock::now();
    parSum = processAsync(parData.get(), dataSize, numThreads);
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration< double > elapsedParallel = end - start;

    std::printf("Time for parallel processing: %f seconds\n", elapsedParallel.count());
    std::printf("Sum: %f\n", parSum);
    std::printf("Speedup: %f\n", elapsedSerially.count() / elapsedParallel.count());

    return 0;
}
