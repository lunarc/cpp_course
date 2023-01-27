#include <iostream>
#include <deque>

using namespace std;

int main()
{
    deque<int> q;
    
    for (auto i=0; i<5; i++)
        q.push_back(i);
    
    for (auto i=5; i<10; i++)
        q.push_front(i);
    
    for (auto it=q.begin(); it!=q.end(); it++)
        cout << *it << ", ";

    cout << "\n";
    cout << "\n";

    for (auto& i : q)
        cout << i << ", ";
    
    cout << "\n";

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