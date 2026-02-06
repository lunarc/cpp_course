#include <vector>
#include <array>
#include <algorithm>
#include <execution>
#include <chrono>
#include <print>
#include <random>
#include <cmath>                                                                                                                                                                                                                                                                                                            
#include <thread>

int main() 
{
    std::array dataSizes = {10000, 100000, 1000000, 10000000, 100000000};

    for (const auto& size : dataSizes)
    {
        std::vector<double> dataSeq(size);
        std::vector<double> dataPar(size);

        // Initialize with simple values first
        std::iota(dataSeq.begin(), dataSeq.end(), 0.0);                                                     
        std::iota(dataPar.begin(), dataPar.end(), 0.0);

        // Computationally intensive transformation
        auto heavyTransform = [](double x) {
            double result = x;
            for (int i = 0; i < 100; ++i) {
                result = std::sin(result) * std::cos(result);
            }
            return result;
        };

        // Sequential execution
        auto startSeq = std::chrono::high_resolution_clock::now();
        std::transform(std::execution::seq, dataSeq.begin(), dataSeq.end(),                                                                                                                                                                                                     
                      dataSeq.begin(), heavyTransform);
        auto endSeq = std::chrono::high_resolution_clock::now();

        // Parallel execution
        auto startPar = std::chrono::high_resolution_clock::now();
        std::transform(std::execution::par, dataPar.begin(), dataPar.end(), 
                      dataPar.begin(), heavyTransform);
        auto endPar = std::chrono::high_resolution_clock::now();

        auto durationSeq = std::chrono::duration<double>(endSeq - startSeq).count();
        auto durationPar = std::chrono::duration<double>(endPar - startPar).count();

        std::println("========================================");
        std::println("Data size: {}", size);
        std::println("Data size in MB: {:.2f}", size * sizeof(double) / (1024.0 * 1024.0));
        std::println("Sequential time: {:.4f} s", durationSeq);
        std::println("Parallel time: {:.4f} s", durationPar);
        
        if (durationPar > 0) {
            std::println("Speedup: {:.2f}x", durationSeq / durationPar);
            std::println("Efficiency: {:.1f}%", (durationSeq / durationPar / std::thread::hardware_concurrency()) * 100);
        }
        
        // Verify results match
        bool resultsMatch = std::equal(dataSeq.begin(), dataSeq.end(), dataPar.begin(),
            [](double a, double b) { return std::abs(a - b) < 1e-10; });
        std::println("Results match: {}", resultsMatch ? "Yes" : "No");
    }

    return 0;
}