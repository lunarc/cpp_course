#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<int> vec{5, 1, 3, 4, 4, 8};

    std::for_each(vec.begin(), vec.end(), [](auto i) { std::cout << i << "\n"; });

    auto it = find_if(vec.begin(), vec.end(), [](int i) { return i > 5; });

    std::cout << "found " << *it << "\n";

    std::sort(vec.begin(), vec.end());

    std::for_each(vec.begin(), vec.end(), [](int i) { std::cout << i << "\n"; });

    std::cout << "max value = " << *max_element(vec.begin(), vec.end()) << "\n";

    std::cout << "min value = " << *min_element(vec.begin(), vec.end()) << "\n";

    std::fill(vec.begin(), vec.end(), 0);

    std::for_each(vec.begin(), vec.end(), [](int i) { std::cout << i << "\n"; });
}
