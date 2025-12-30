#include <algorithm>
#include <chrono>
#include <cmath>
#include <future>
#include <memory>
#include <print>
#include <thread>
#include <vector>

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

// Function to process data in parallel using std::async
double processAsync(double *data, size_t size, int numThreads)
{
    std::vector< std::future< double > > futures;
    futures.reserve(numThreads);
    
    size_t chunkSize = size / numThreads;

    for (int i = 0; i < numThreads; ++i)
    {
        size_t start = i * chunkSize;
        size_t end = (i == numThreads - 1) ? size : (i + 1) * chunkSize;
        futures.push_back(std::async(std::launch::async, heavyComputation, data, start, end));
    }

    double sum = 0.0;

    for (auto &future : futures)
        sum += future.get();

    return sum;
}

int main()
{
    const size_t dataSize = 5000000;
    const int numThreads = std::thread::hardware_concurrency();

    std::println("Data size: {}", dataSize);
    std::println("Number of threads: {}\n", numThreads);

    // Allocate separate arrays for sequential and parallel processing
    std::println("Allocating and initializing arrays...");
    auto seqData = std::make_unique< double[] >(dataSize);
    auto parData = std::make_unique< double[] >(dataSize);

    std::generate_n(seqData.get(), dataSize, []() { return 1.0; });
    std::generate_n(parData.get(), dataSize, []() { return 1.0; });

    // Sequential processing
    std::println("Running sequentially...");
    auto startSeq = std::chrono::high_resolution_clock::now();
    double seqSum = processSequential(seqData.get(), dataSize);
    auto endSeq = std::chrono::high_resolution_clock::now();

    auto elapsedSeq = std::chrono::duration< double >(endSeq - startSeq).count();
    std::println("Sequential - Time: {:.4f} s, Sum: {:.6f}\n", elapsedSeq, seqSum);

    // Parallel processing
    std::println("Running in parallel...");
    auto startPar = std::chrono::high_resolution_clock::now();
    double parSum = processAsync(parData.get(), dataSize, numThreads);
    auto endPar = std::chrono::high_resolution_clock::now();

    auto elapsedPar = std::chrono::duration< double >(endPar - startPar).count();
    std::println("Parallel   - Time: {:.4f} s, Sum: {:.6f}\n", elapsedPar, parSum);

    // Results summary
    std::println("--- Performance Metrics ---");
    std::println("Speedup: {:.2f}x", elapsedSeq / elapsedPar);
    std::println("Efficiency: {:.1f}%", (elapsedSeq / elapsedPar / numThreads) * 100);
    
    double sumDiff = std::abs(seqSum - parSum);
    double relativeError = sumDiff / std::abs(seqSum);
    std::println("Sum difference: {:.2e} (relative error: {:.2e})", sumDiff, relativeError);
    
    // Verify results are reasonably close
    if (relativeError < 1e-10)
        std::println("OK - Results match within acceptable tolerance");
    else
        std::println("Warning: Large difference between sequential and parallel sums");

    return 0;
}
