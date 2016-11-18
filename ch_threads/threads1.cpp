#include <iostream>
#include <thread>

using namespace std;

static const int numThreads = 1;

void sum(int a, int b, int& sum)
{
    sum = 0;
    for (int i=a; i<=b; i++)
        sum += i;
}

int main() 
{
    int a = 0;
    int b = 1000000000;

    thread threads[numThreads];
    int sums[numThreads];

    // a ---- | ---- | ---- | ---- b

    int chunkSize = (b - a) / numThreads;
    int remainder = (b - a) - chunkSize * numThreads;

    int totalSum = 0;
    int i0, i1;

    for (int i=0;i<numThreads; i++)
    {
        i0 = chunkSize*i;
        i1 = chunkSize*(i+1)-1;
        if (i == numThreads-1)
            i1 += remainder + 1;
        cout << "i0 = " << i0 << " i1 = " << i1 << endl;
        threads[i] = thread(sum, i0, i1, totalSum);
    }

    cout << "Waiting for completion..." << endl;

    for (int i=0; i<numThreads; i++)
        threads[i].join();

    return 0;
}
