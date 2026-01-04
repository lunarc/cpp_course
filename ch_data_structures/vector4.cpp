#include <print>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>

int main()
{
    srand((unsigned)time(0));
    
    std::vector<int> vec;
    
    for (int i=0; i<10; i++)
        vec.emplace_back(rand());
    
    std::sort(vec.begin(), vec.end());
    std::reverse(vec.begin(), vec.end());
    
    for (auto it=vec.begin(); it!=vec.end(); it++)
        std::println("{}", *it);
}