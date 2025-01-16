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
#include <random>
#include <ranges>
#include <thread>
#include <utils/print.h>
#include <vector>

using namespace std;

// Function to perform a computationally intensive task
void heavyComputation(double *arr, size_t start, size_t end, std::atomic< double > &sum)
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

    sum += localSum;
}

void initialiseArray(double *arr, size_t start, size_t end, double value)
{
    for (size_t i = start; i < end; ++i)
        arr[i] = value;
}

// Function to process data sequentially
void processSequential(double *data, size_t size, std::atomic< double > &sum)
{
    heavyComputation(data, 0, size, sum);
}

void initialiseParallel(double *data, size_t size, double value)
{
    size_t chunkSize = size / std::thread::hardware_concurrency();

    std::vector< std::jthread > threads;
    threads.reserve(std::thread::hardware_concurrency());

    for (int i = 0; i < std::thread::hardware_concurrency(); ++i)
    {
        size_t start = i * chunkSize;
        size_t end = (i == std::thread::hardware_concurrency() - 1) ? size : (i + 1) * chunkSize;
        threads.emplace_back(initialiseArray, data, start, end, value);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }
}

void processParallel(double *data, size_t size, int numThreads, std::atomic< double > &sum)
{
    std::vector< std::jthread > threads;
    threads.reserve(numThreads);

    size_t chunkSize = size / numThreads;

    for (int i = 0; i < numThreads; ++i)
    {
        size_t start = i * chunkSize;
        size_t end = (i == numThreads - 1) ? size : (i + 1) * chunkSize;
        threads.emplace_back(heavyComputation, data, start, end, std::ref(sum));
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
    const size_t dataSize = 500000;
    int numThreads = std::thread::hardware_concurrency();

    std::printf("Data size: %zu\n", dataSize);
    std::printf("Number of threads: %d\n", numThreads);

    std::print("Allocating arrays...\n");

    auto seqData = std::make_unique< double[] >(dataSize);
    auto parData = std::make_unique< double[] >(dataSize);
    std::atomic< double > seqSum{0.0};
    std::atomic< double > parSum{0.0};

    // ----- SERIAL CODE -----

    std::print("Initialising arrays serially...\n");

    std::generate_n(seqData.get(), dataSize, []() { return 1.0; });
    /*
    std::generate_n(parData.get(), dataSize, []() { return 1.0; });
    */

    std::print("Running serially...\n");

    auto start = std::chrono::high_resolution_clock::now();
    processSequential(seqData.get(), dataSize, seqSum);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration< double > elapsedSerially = end - start;
    std::printf("Time for sequential processing: %f seconds\n", elapsedSerially.count());
    std::printf("Sum: %f\n", seqSum.load());

    // ----- PARALLEL CODE -----

    start = std::chrono::high_resolution_clock::now();
    initialiseParallel(parData.get(), dataSize, 1.0);
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration< double > elapsedInitParallel = end - start;
    std::printf("Time for parallel processing: %f seconds\n", elapsedInitParallel.count());

    std::print("Running in parallel...\n");

    start = std::chrono::high_resolution_clock::now();
    processParallel(parData.get(), dataSize, numThreads, parSum);
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration< double > elapsedParallel = end - start;

    std::printf("Time for parallel processing: %f seconds\n", elapsedParallel.count());
    std::printf("Sum: %f\n", parSum.load());
    std::printf("Speedup: %f\n", elapsedSerially.count() / elapsedParallel.count());

    return 0;
}
