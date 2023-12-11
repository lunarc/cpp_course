#include <algorithm>
#include <iostream>
#include <vector>

void print_vector(auto v)
{
    for (auto& item : v)
        std::cout << item << " ";
    std::cout << std::endl;
}

int main()
{
	std::vector v1 = { 6, 4, 7, 3, 9, 0, 1, 5 };

    std::transform(v1.cbegin(), v1.cend(), v1.begin(), [](int v){return v*v;});

    print_vector(v1);

    std::vector<int> v2(8);

    std::transform(v1.cbegin(), v1.cend(), v2.begin(), [](int v){return v*v;});

    print_vector(v2);

    std::vector<int> v3;

    std::transform(v1.cbegin(), v1.cend(), std::back_inserter(v3), [](int v){return v*v;});

    print_vector(v3);
}
