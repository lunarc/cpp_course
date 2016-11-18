#include <iostream>
#include <deque>

using namespace std;

int main()
{
    deque<int> q;
    
    for (int i=0; i<=5; i++)
        q.push_back(i);
    
    for (int i=6; i<=10; i++)
        q.push_front(i);
    
    deque<int>::iterator it;

    for (it=q.begin(); it!=q.end(); it++)
        cout << *it << ", ";
    
    cout << endl;

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