#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    std::vector<int> vec = { 5, 1, 3, 4, 4, 8 };
    
    auto it = std::find(vec.begin(), vec.end(), 4);
    
    if (it!=vec.end())
        std::cout << "found " << *it << "\n";
    else
        std::cout << "Value not found." << "\n";

    it = find(++it, vec.end(), 4);

    if (it!=vec.end())
        std::cout << "found " << *it << "\n";
    else
        std::cout << "Value not found." << "\n";

    it = std::find(++it, vec.end(), 4);
    
    if (it!=vec.end())
        std::cout << "found " << *it << "\n";
    else
        std::cout << "Value not found." << "\n";

}