#include <vector>
#include <print>
#include <algorithm>
#include <execution>
#include <chrono>
#include <ranges>

bool is_prime(int num) 
{
    if (num < 2)
        return false;
    for (int i = 2; i * i <= num; ++i)
    {
        if (num % i == 0)
            return false;
    }
    return true;
};

int main() 
{
    const int N = 10000000;

	std::vector<int> seqVec(N);
    std::vector<int> parVec(N);
    std::vector<int> parTransformed(N);
    std::vector<int> seqTransformed(N);
    std::vector<int> parPrimes;
    std::vector<int> seqPrimes;

    std::generate(seqVec.begin(), seqVec.end(), [n = 0]() mutable { return n++; });
    std::generate(parVec.begin(), parVec.end(), [n = 0]() mutable { return n++; });

	auto startPar = std::chrono::high_resolution_clock::now();
    std::transform(std::execution::par_unseq, parVec.begin(), parVec.end(), parTransformed.begin(), [](int n) 
    { 
        return is_prime(n) ? n : 0; 
    });
    auto endPar = std::chrono::high_resolution_clock::now();

    // Copy non-zero values (sequential step)

    std::copy_if(parTransformed.begin(), parTransformed.end(), std::back_inserter(parPrimes),
                 [](int n) { return n != 0; });

	std::chrono::duration< double > durationPar = endPar - startPar;

	auto startSeq = std::chrono::high_resolution_clock::now();
    std::transform(std::execution::seq, seqVec.begin(), seqVec.end(), seqTransformed.begin(), [](int n) 
    { 
        return is_prime(n) ? n : 0; 
    });
    auto endSeq = std::chrono::high_resolution_clock::now();

    // Copy non-zero values

    std::copy_if(seqTransformed.begin(), seqTransformed.end(), std::back_inserter(seqPrimes),
                 [](int n) { return n != 0; });

    std::chrono::duration< double > durationSeq = endSeq - startSeq;

	std::print("Time taken sequentially : {} seconds\n", durationSeq.count());
    std::print("Time taken in parallel  : {} seconds\n", durationPar.count());

    std::print("Speedup: {}x\n", durationSeq.count() / durationPar.count());
    std::print("Data size in megabytes: {} MB\n", (N * sizeof(int)) / (1024.0 * 1024.0));


    std::print("First 10 elements after parallel transform: ");
    for (auto n : parPrimes | std::views::take(10))
    {
        std::print("{} ", n);
    }
    std::print("\n");

    std::print("First 10 elements after sequential transform: ");
    for (auto n : seqPrimes | std::views::take(10))
    {
        std::print("{} ", n);
    }
    std::print("\n");

	return 0;
}