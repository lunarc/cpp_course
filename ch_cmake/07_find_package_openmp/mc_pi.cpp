// Estimate pi by throwing random points into the unit square and
// counting how many land inside the quarter circle.

#include <chrono>
#include <cstdint>
#include <print>
#include <random>

#ifdef _OPENMP
#include <omp.h> // only available when compiling with OpenMP
#endif

int main()
{
    const std::int64_t n_samples = 200'000'000;
    std::int64_t inside = 0;

    int n_threads = 1;
#ifdef _OPENMP
    n_threads = omp_get_max_threads();
#endif

    const auto start = std::chrono::steady_clock::now();

    // Each thread gets its own random generator. Without OpenMP the
    // pragmas are ignored and the loop runs serially.
#pragma omp parallel reduction(+ : inside)
    {
        int thread_id = 0;
#ifdef _OPENMP
        thread_id = omp_get_thread_num();
#endif
        std::mt19937_64 rng(12345 + thread_id);
        std::uniform_real_distribution<double> uniform(0.0, 1.0);

#pragma omp for
        for (std::int64_t i = 0; i < n_samples; ++i)
        {
            const double x = uniform(rng);
            const double y = uniform(rng);
            if (x * x + y * y <= 1.0)
                ++inside;
        }
    }

    const std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;

    std::println("Threads : {}", n_threads);
    std::println("pi      ~ {:.6f}", 4.0 * static_cast<double>(inside) / n_samples);
    std::println("Time    : {:.3f} s", elapsed.count());

    return 0;
}
