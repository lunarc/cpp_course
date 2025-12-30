#include <vector>
#include <array>
#include <algorithm>
#include <execution>
#include <chrono>
#include <print>
#include <random>
#include <cmath>

int main() 
{
    std::vector< int > data(100000000);

    // Initialize with random values

    std::mt19937 gen(42); // Fixed seed for reproducibility
    std::uniform_int_distribution<> dis(1, 10000000);
    std::generate(data.begin(), data.end(), [&]() { return dis(gen); });

    // Find max element sequentially

    auto startSeq = std::chrono::high_resolution_clock::now();
    auto maxSeq = *std::max_element(std::execution::seq, data.begin(), data.end());
    auto endSeq = std::chrono::high_resolution_clock::now();
    auto durationSeq = std::chrono::duration< double >(endSeq - startSeq).count();
    std::println("Sequential max: {}, time: {:.4f} s", maxSeq, durationSeq);

    // Find max element in parallel

    auto startPar = std::chrono::high_resolution_clock::now();
    auto maxPar = *std::max_element(std::execution::par_unseq, data.begin(), data.end());
    auto endPar = std::chrono::high_resolution_clock::now();
    auto durationPar = std::chrono::duration< double >(endPar - startPar).count();
    std::println("Parallel max: {}, time: {:.4f} s", maxPar, durationPar);

    return 0;
}