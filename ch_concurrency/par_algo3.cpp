#include <algorithm>
#include <chrono>
#include <execution>
#include <print>
#include <random>
#include <vector>

int main()
{
    const int N = 100000000;
    std::vector< int > parData(N);
    std::vector< int > seqData(N);

    // Initialize the vector with some values

    std::print("Initializing data...\n");

    std::mt19937 gen(42); // Fixed seed for reproducibility
    std::uniform_int_distribution<> dis(1, N);
    std::generate(parData.begin(), parData.end(), [&]() { return dis(gen); });
    std::copy(parData.begin(), parData.end(), seqData.begin());

    std::print("Starting sort operations...\n");

    // Sort the vector in parallel
    auto startPar = std::chrono::high_resolution_clock::now();
    std::sort(std::execution::par, parData.begin(), parData.end());
    auto endPar = std::chrono::high_resolution_clock::now();
    std::chrono::duration< double > durationPar = endPar - startPar;

    // Sort the vector sequentially
    auto startSeq = std::chrono::high_resolution_clock::now();
    std::sort(std::execution::seq, seqData.begin(), seqData.end());
    auto endSeq = std::chrono::high_resolution_clock::now();
    std::chrono::duration< double > durationSeq = endSeq - startSeq;

    // Check if sort opereration was successful

    std::print("Verifying sorted data...\n");

    std::is_sorted(std::execution::par, parData.begin(), parData.end()) ? std::print("Parallel sort successful.\n")
                                                                        : std::print("Parallel sort failed.\n");

    std::is_sorted(std::execution::par, seqData.begin(), seqData.end()) ? std::print("Sequential sort successful.\n")
                                                                        : std::print("Sequential sort failed.\n");

    std::print("Parallel sort time: {} seconds\n", durationPar.count());
    std::print("Sequential sort time: {} seconds\n", durationSeq.count());
    std::print("Speedup: {:.2f}x\n", durationSeq.count() / durationPar.count());

    return 0;
}