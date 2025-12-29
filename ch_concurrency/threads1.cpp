#include <thread>
#include <vector>
#include <print>

void sum(const int a, const int b, const int id, long long *sums)
{
    long long localSum = 0;

    for (int i = a; i <= b; i++)
        localSum += i;

    sums[id] = localSum;
}

int main()
{
    const int a = 0;
    const int b = 100000000;

    const auto numThreads = std::min(8u, std::thread::hardware_concurrency());

    std::vector< std::jthread > threads;

    std::vector< long long > sums;
    sums.resize(numThreads);
    
    const int chunkSize = (b - a + 1) / numThreads;
    const int remainder = (b - a + 1) % numThreads;

    std::print("Summing from {0} to {1} using {2} threads\n", a, b, numThreads);
    std::print("Chunk size = {0}, Remainder = {1}\n", chunkSize, remainder);

    int i0, i1;

    for (auto i = 0; i < numThreads; i++)
    {
        i0 = a + chunkSize * i + std::min(i, remainder);
        i1 = i0 + chunkSize - 1;

        if (i < remainder)
            i1++;

        std::print("Thread {0}: i0 = {1}, i1 = {2} (count = {3})\n", i, i0, i1, i1 - i0 + 1);
        threads.emplace_back(sum, i0, i1, i, sums.data());
    }

    std::print("Waiting for completion...\n");

    for (auto& thread : threads)
        thread.join();

    long long totalSum = 0;
    auto i = 0;

    for (auto& sum : sums)
    {
        totalSum += sum;
        std::print("Sum {0} = {1}\n", i, sums[i++]);
    }

    std::print("Total sum = {0}\n", totalSum);
    
    long long expected = (long long)(b - a + 1) * (a + b) / 2;
    std::print("Expected sum = {0}\n", expected);
    std::print("Difference = {0}\n", totalSum - expected);

    return 0;
}
