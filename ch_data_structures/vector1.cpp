#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main()
{
    srand((unsigned)time(0));
    
    std::vector<int> vec;
    
    for (auto i=0; i<10; i++)
        vec.emplace_back(rand());

    for (size_t i=0; i<vec.size(); i++)
        std::cout << vec[i] << "\n";

    std::cout << "\n";

    for (auto it=vec.begin(); it!=vec.end(); it++)
        std::cout << *it << "\n";

    std::cout << "\n";

    for (auto& v : vec)
        v = rand();

    for (auto& v : vec)
        std::cout << v << "\n";
}
