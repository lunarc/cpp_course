#include <vector>
#include <algorithm>
#include <execution>
#include <chrono>
#include <print>

int main() 
{
    std::vector< int > data(100000000);

	// Initialize the vector with some values

	std::generate(data.begin(), data.end(), []() { return rand() % 1000000; });

	// Sort the vector in parallel
    auto startPar = std::chrono::high_resolution_clock::now();
	std::sort(std::execution::par, data.begin(), data.end());
	auto endPar = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> durationPar = endPar - startPar;

	// Sort the vector sequentially
	std::generate(data.begin(), data.end(), []() { return rand() % 1000000; });
    auto startSeq = std::chrono::high_resolution_clock::now();
    std::sort(std::execution::seq, data.begin(), data.end());
    auto endSeq = std::chrono::high_resolution_clock::now();
    std::chrono::duration< double > durationSeq = endSeq - startSeq;

	std::print("Parallel sort time: {} seconds\n", durationPar.count());
    std::print("Sequential sort time: {} seconds\n", durationSeq.count());


	return 0;
}