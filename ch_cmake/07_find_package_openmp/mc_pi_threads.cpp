// The same Monte Carlo estimate of pi, parallelised with std::thread.

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <print>
#include <random>
#include <thread>
#include <vector>

int main()
{
    const std::int64_t n_samples = 200'000'000;
    const unsigned n_threads = std::max(1u, std::thread::hardware_concurrency());

    std::vector<std::int64_t> inside(n_threads, 0);
    std::vector<std::thread> workers;

    const auto start = std::chrono::steady_clock::now();

    for (unsigned t = 0; t < n_threads; ++t)
    {
        workers.emplace_back([&, t] {
            std::mt19937_64 rng(12345 + t);
            std::uniform_real_distribution<double> uniform(0.0, 1.0);

            std::int64_t count = 0;
            for (std::int64_t i = t; i < n_samples; i += n_threads)
            {
                const double x = uniform(rng);
                const double y = uniform(rng);
                if (x * x + y * y <= 1.0)
                    ++count;
            }
            inside[t] = count;
        });
    }

    std::int64_t total = 0;
    for (unsigned t = 0; t < n_threads; ++t)
    {
        workers[t].join();
        total += inside[t];
    }

    const std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;

    std::println("Threads : {}", n_threads);
    std::println("pi      ~ {:.6f}", 4.0 * static_cast<double>(total) / n_samples);
    std::println("Time    : {:.3f} s", elapsed.count());

    return 0;
}
