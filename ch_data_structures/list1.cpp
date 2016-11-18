#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<int> l;
    
    for (int i=0; i<=5; i++)
        l.push_back(i);
    
    for (int i=6; i<=10; i++)
        l.push_front(i);
    
    list<int>::iterator it;

    for (it=l.begin(); it!=l.end(); it++)
        cout << *it << ", ";
    
    cout << endl;

    cout << "l front = " << l.front() << endl;
    cout << "pop front" << endl;
    l.pop_front();
    cout << "l front = " << l.front() << endl;
    cout << "l back = " << l.back() << endl;
    cout << "pop back" << endl;
    l.pop_back();
    cout << "l back = " << l.back() << endl;
}