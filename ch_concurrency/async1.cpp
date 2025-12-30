#include <cmath>
#include <ctime>
#include <memory>
#include <thread>
#include <future>
#include <print>
#include <chrono>

double sum(const double *array, int start, int stop)
{
    auto sum = 0.0;
    for (auto i = start; i < stop; i++)
        sum += array[i];
    return sum;
}

int main()
{
    std::println("Starting async example...");
    std::println("Number of threads = {}", std::thread::hardware_concurrency());

    auto N = 1000000000;

    auto array = std::make_unique< double[] >(N);

    for (auto i = 0; i < N; i++)
        array[i] = rand();

    auto lambda = [&](int start, int stop) -> double 
    { 
        return sum(array.get(), start, stop); 
    };

    std::println("Launching async tasks...");

    auto startAsync = std::chrono::high_resolution_clock::now();
    auto f1 = async(std::launch::async, lambda, 0, N / 4);
    auto f2 = async(std::launch::async, lambda, N / 4, N / 2);
    auto f3 = async(std::launch::async, lambda, N / 2, N / 2 + N / 4);
    auto f4 = async(std::launch::async, lambda, N / 2 + N / 4, N);
    auto sum1 = f1.get();
    auto sum2 = f2.get();
    auto sum3 = f3.get();
    auto sum4 = f4.get();
    auto endAsync = std::chrono::high_resolution_clock::now();

    auto elapsedAsync = std::chrono::duration< double >(endAsync - startAsync).count();

    auto totalSumAsync = sum1 + sum2 + sum3 + sum4;

    std::println("Launching serial sum...");
    auto startSerial = std::chrono::high_resolution_clock::now();
    auto totalSumSerial = sum(array.get(), 0, N);
    auto endSerial = std::chrono::high_resolution_clock::now();
    std::println("Done.");

    auto elapsedSerial = std::chrono::duration< double >(endSerial - startSerial).count();

    std::println("Async: sum = {}, time = {} s", totalSumAsync, elapsedAsync);
    std::println("Serial: sum = {}, time = {} s", totalSumSerial, elapsedSerial);
    std::println("Speedup = {}x", elapsedSerial / elapsedAsync);

    return 0;
}
