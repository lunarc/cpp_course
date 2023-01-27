#include <iostream>
#include <list>

int main()
{
    std::list<int> l;
    
    for (auto i=0; i<=5; i++)
        l.push_back(i);
    
    for (auto i=6; i<=10; i++)
        l.push_front(i);
    
    for (auto it=l.begin(); it!=l.end(); it++)
        std::cout << *it << ", ";
    
    std::cout << "\n";

    std::cout << "l front = " << l.front() << "\n";
    std::cout << "pop front" << "\n";
    l.pop_front();
    std::cout << "l front = " << l.front() << "\n";
    std::cout << "l back = " << l.back() << "\n";
    std::cout << "pop back" << "\n";
    l.pop_back();
    std::cout << "l back = " << l.back() << "\n";
}