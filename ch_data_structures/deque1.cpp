#include <deque>
#include <print>

int main()
{
    std::deque<int> q;

    // Add items to the back

    for (auto i = 0; i < 5; i++)
        q.push_back(i);

    // Add items to the front

    for (auto i = 5; i < 10; i++)
        q.push_front(i);

    // Iterate using iterators

    for (auto it = q.begin(); it != q.end(); it++)
        std::print("{}, ", *it);

    std::print("\n");

    // Iterate using range-based loop

    for (auto &i : q)
        std::print("{}, ", i);

    std::print("\n");

    // Popping and popping

    std::println("q front = {}", q.front());
    std::println("pop front");
    q.pop_front();
    std::println("q front = {}", q.front());
    std::println("q back = {}", q.back());
    std::println("pop back");
    q.pop_back();
    std::println("q back = {}", q.back());
    std::println("q[3] = {}", q[3]);
}
