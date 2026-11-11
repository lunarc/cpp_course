#include <cmath>
#include <cstdio>
#include <fstream>
#include <print>
#include <vector>

int main(int argc, char* argv[])
{
    const char* filename = argc > 1 ? argv[1] : "positions.txt";

    std::ifstream in(filename);
    if (!in)
    {
        // The first argument selects where to print, here standard error.
        std::println(stderr, "Could not open {} - run simulate first.", filename);
        return 1;
    }

    std::vector<double> x;
    for (double value; in >> value;)
        x.push_back(value);

    double mean = 0.0;
    for (double v : x)
        mean += v;
    mean /= static_cast<double>(x.size());

    double var = 0.0;
    for (double v : x)
        var += (v - mean) * (v - mean);
    var /= static_cast<double>(x.size() - 1);

    std::println("Samples  : {}", x.size());
    std::println("Mean     : {:.4f}", mean);
    std::println("Std. dev.: {:.4f}  (theory for 100 steps: 10)", std::sqrt(var));
    return 0;
}
