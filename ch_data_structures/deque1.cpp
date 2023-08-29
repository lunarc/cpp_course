#include <deque>
#include <iostream>

using namespace std;

int main()
{
    deque<int> q;

    // Add items to the back

    for (auto i = 0; i < 5; i++)
        q.push_back(i);

    // Add items to the front

    for (auto i = 5; i < 10; i++)
        q.push_front(i);

    // Iterate using iterators

    for (auto it = q.begin(); it != q.end(); it++)
        cout << *it << ", ";

    cout << "\n";
    cout << "\n";

    // Iterate using range-based loop

    for (auto &i : q)
        cout << i << ", ";

    cout << "\n";

    // Popping and popping

    cout << "q front = " << q.front() << endl;
    cout << "pop front" << endl;
    q.pop_front();
    cout << "q front = " << q.front() << endl;
    cout << "q back = " << q.back() << endl;
    cout << "pop back" << endl;
    q.pop_back();
    cout << "q back = " << q.back() << endl;
    cout << "q[3] = " << q[3] << endl;
}
