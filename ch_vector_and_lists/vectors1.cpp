#include <iostream>
#include <vector>

int main()
{
    std::vector<double> vec;

    for (auto i=0; i<10; i++)
        vec.push_back(i);

    for (auto i=0; i<10; i++)
        std::cout << vec[i] << "\n";
}
