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
    
    std::vector<int>::iterator it;

    for (it=vec.begin(); it!=vec.end(); it++)
        std::cout << *it << "\n";
}