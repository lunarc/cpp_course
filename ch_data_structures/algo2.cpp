#include <algorithm>
#include <print>
#include <vector>

void myfunc(int i)
{
    std::println("{}", i);
}

bool greaterThan5(int i)
{
    return i > 5;
}

int main()
{
    std::vector<int> vec{5, 1, 3, 4, 4, 8};

    std::for_each(vec.begin(), vec.end(), myfunc);

    auto it = std::find_if(vec.begin(), vec.end(), greaterThan5);

    std::print("found {}\n", *it);

    std::sort(vec.begin(), vec.end());

    std::for_each(vec.begin(), vec.end(), myfunc);

    std::print("max value = {}\n", *std::max_element(vec.begin(), vec.end()));

    std::print("min value = {}\n", *std::min_element(vec.begin(), vec.end()));

    std::fill(vec.begin(), vec.end(), 0);

    std::for_each(vec.begin(), vec.end(), myfunc);
}
