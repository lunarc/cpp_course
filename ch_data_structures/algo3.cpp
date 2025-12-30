#include <algorithm>
#include <print>
#include <vector>

int main()
{
    std::vector<int> vec{5, 1, 3, 4, 4, 8};

    std::for_each(vec.begin(), vec.end(), [](auto i) { std::print("{}\n", i); });

    auto it = find_if(vec.begin(), vec.end(), [](int i) { return i > 5; });

    std::print("found {}\n", *it);

    std::sort(vec.begin(), vec.end());

    std::for_each(vec.begin(), vec.end(), [](int i) { std::print("{}\n", i); });

    std::print("max value = {}\n", *max_element(vec.begin(), vec.end()));

    std::print("min value = {}\n", *min_element(vec.begin(), vec.end()));

    std::fill(vec.begin(), vec.end(), 0);

    std::for_each(vec.begin(), vec.end(), [](int i) { std::print("{}\n", i); });
}
