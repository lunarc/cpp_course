#include <iostream>
#include <list>

void print_items(const auto &list)
{
    for (auto &v : list)
        std::cout << v << ", ";
    std::cout << "\n";
}

int main()
{
    std::list<int> l;

    // Adding items to the list

    for (auto i = 0; i <= 5; i++)
        l.push_back(i);

    for (auto i = 6; i <= 10; i++)
        l.push_front(i);

    l.insert(l.begin(), 42);

    for (auto it = l.begin(); it != l.end(); it++)
    {
        if (*it == 9)
            l.insert(it, 43);
    }

    // List iteration using iterators

    for (auto it = l.begin(); it != l.end(); it++)
        std::cout << *it << ", ";

    std::cout << "\n";

    // Range based iteration

    for (auto &v : l)
        std::cout << v << ", ";

    std::cout << "\n";

    // Removing items from the front and back

    std::cout << "l front = " << l.front() << "\n";
    std::cout << "pop front"
              << "\n";

    l.pop_front();

    std::cout << "l front = " << l.front() << "\n";
    std::cout << "l back = " << l.back() << "\n";
    std::cout << "pop back"
              << "\n";

    l.pop_back();

    std::cout << "l back = " << l.back() << "\n";

    print_items(l);

    // Removing items using .remove()

    l.remove(0);

    print_items(l);

    // Removing items using .erase()

    for (auto it = l.begin(); it != l.end();)
    {
        if (*it == 3)
            it = l.erase(it); // Returns next iterator after erase.
        else
            ++it;
    }

    print_items(l);
}
