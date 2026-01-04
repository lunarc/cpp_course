#include <print>
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
        std::println("{}", vec[i]);

    std::println("");

    for (auto it=vec.begin(); it!=vec.end(); it++)
        std::println("{}", *it);

    std::println("");

    for (auto& v : vec)
        v = rand();

    for (auto& v : vec)
        std::println("{}", v);
}
