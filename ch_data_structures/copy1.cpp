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
    std::vector v2 = { 0, 0, 0, 0, 0, 0, 0, 0 };
    std::vector<int> v3;

    std::copy(v1.begin(), v1.end(), v2.begin());

    print_vector(v2);

    std::copy(v1.begin(), v1.end(), std::back_inserter(v2));

    print_vector(v2);

    std::copy_if(v1.begin(), v1.end(), std::back_inserter(v3), [](int v) {return v % 2 == 0;});

    print_vector(v3);

    std::vector<int> v4(20);

    std::copy_backward(v1.begin(), v1.end(), v4.end());

    print_vector(v4);
}
