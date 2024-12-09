#include <iostream>
#include <mutex>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <thread>

using namespace std;

static const auto numThreads = 8;
std::mutex sumLock;

void sum(const double a, const double b, const int id, double *sum)
{
    double localSum = 0;

    for (double i = a; i <= b; i++)
        localSum += i;

    std::lock_guard< std::mutex > lock(sumLock);
    sum[id] = localSum;
}

int main()
{
    double a = 0;
    double b = 10000000000;

    jthread threads[numThreads];
    double sums[numThreads];

    // a ---- | ---- | ---- | ---- b

    double chunkSize = (b - a) / numThreads;
    double remainder = (b - a) - chunkSize * numThreads;

    double totalSum = 0;
    double i0, i1;

    for (int i = 0; i < numThreads; i++)
    {
        i0 = chunkSize * i;
        i1 = chunkSize * (i + 1) - 1;
        if (i == numThreads - 1)
            i1 += remainder + 1;

        fmt::print("i0 = {0} i1 = {1}\n", i0, i1);
        threads[i] = jthread(sum, i0, i1, i, sums);
    }

    fmt::print("Waiting for completion...\n");

    for (int i = 0; i < numThreads; i++)
    {
        threads[i].join();
        fmt::print("Sum {0} = {1}\n", i, sums[i]);
        totalSum += sums[i];
    }

    fmt::print("Total sum = {0}\n", totalSum);

    return 0;
}
