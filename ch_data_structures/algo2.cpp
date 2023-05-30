#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void myfunc(int i)
{
    std::cout << i << "\n";
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

    std::cout << "found " << *it << "\n";

    std::sort(vec.begin(), vec.end());

    std::for_each(vec.begin(), vec.end(), myfunc);

    std::cout << "max value = " << *std::max_element(vec.begin(), vec.end()) << "\n";

    std::cout << "min value = " << *std::min_element(vec.begin(), vec.end()) << "\n";

    std::fill(vec.begin(), vec.end(), 0);

    std::for_each(vec.begin(), vec.end(), myfunc);
}
