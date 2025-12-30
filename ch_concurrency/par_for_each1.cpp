#include <vector>
#include <print>
#include <algorithm>
#include <numeric>
#include <execution>
#include <chrono>

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

    std::generate(seqVec.begin(), seqVec.end(), [n = 0]() mutable { return n++; });
    std::generate(parVec.begin(), parVec.end(), [n = 0]() mutable { return n++; });

	auto startPar = std::chrono::high_resolution_clock::now();
    std::for_each(std::execution::par_unseq, parVec.begin(), parVec.end(), [](int &n) {
        n = is_prime(n) ? n : 0;
    });
    auto endPar = std::chrono::high_resolution_clock::now();

	std::chrono::duration< double > durationPar = endPar - startPar;

	auto startSeq = std::chrono::high_resolution_clock::now();
    std::for_each(std::execution::seq, seqVec.begin(), seqVec.end(), [](int &n) {
        n = is_prime(n) ? n : 0; 
    });
    auto endSeq = std::chrono::high_resolution_clock::now();

    std::chrono::duration< double > durationSeq = endSeq - startSeq;

	std::print("Time taken sequentially : {} seconds\n", durationSeq.count());
    std::print("Time taken in parallel  : {} seconds\n", durationPar.count());

    std::print("Speedup: {}x\n", durationSeq.count() / durationPar.count());
    std::print("Data size in megabytes: {} MB\n", (N * sizeof(int)) / (1024.0 * 1024.0));

	std::print("First 10 elements after parallel for_each: ");

	for (int i = 0; i < 10; ++i) {
		std::print("{} ", parVec[i]);
	}
    std::print("\n");

	std::print("First 10 elements after sequential for_each: ");

	for (int i = 0; i < 10; ++i) {
		std::print("{} ", seqVec[i]);
	}
    std::print("\n");

	return 0;
}