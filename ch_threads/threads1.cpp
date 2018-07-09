#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

static const int numThreads = 8;
std::mutex sumLock;

void sum(double a, double b, int id, double* sum)
{
    double localSum = 0;

    for (double i=a; i<=b; i++)
        localSum += i;

    sumLock.lock();
    sum[id] = localSum;
    sumLock.unlock();
}

int main() 
{
    double a = 0;
    double b = 10000000000;

    thread threads[numThreads];
    double sums[numThreads];

    // a ---- | ---- | ---- | ---- b

    double chunkSize = (b - a) / numThreads;
    double remainder = (b - a) - chunkSize * numThreads;

    double totalSum = 0;
    double i0, i1;

    for (int i=0;i<numThreads; i++)
    {
        i0 = chunkSize*i;
        i1 = chunkSize*(i+1)-1;
        if (i == numThreads-1)
            i1 += remainder + 1;
        cout << "i0 = " << i0 << " i1 = " << i1 << endl;
        threads[i] = thread(sum, i0, i1, i, sums);
    }

    cout << "Waiting for completion..." << endl;

    for (int i = 0; i < numThreads; i++)
    {
        threads[i].join();
        cout << sums[i] << endl;
        totalSum += sums[i];
    }

    cout << "Total sum = " << totalSum;

    return 0;
}
