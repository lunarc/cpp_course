#include <iostream>

using namespace std;

class KillMeNow {
public:
    KillMeNow() { cout << "KillMeNow " << this << " created." << endl; };
    virtual ~KillMeNow() { cout << "KillMeNow " << this << " destroyed." << endl; };
};

int main()
{
    cout << "---- Program start ----" << endl;
    
    KillMeNow k1;
    
    unique_ptr<KillMeNow> k2(new KillMeNow());
    unique_ptr<KillMeNow> k3 = nullptr;
    
    cout << "Before pointer move" << endl;
    cout << "k2 = " << k2.get() << endl;
    cout << "k3 = " << k3.get() << endl;
    
    k3 = move(k2);
    
    cout << "After pointer move" << endl;
    cout << "k2 = " << k2.get() << endl;
    cout << "k3 = " << k3.get() << endl;    
    
    shared_ptr<KillMeNow> k4(new KillMeNow());
    shared_ptr<KillMeNow> k5 = k4;
    weak_ptr<KillMeNow> k6 = k4;
    
    cout << "k4.use_count() = " << k4.use_count() << endl;
    cout << "k5 = nullptr" << endl;
    k5 = nullptr;
    cout << "k4.use_count() = " << k4.use_count() << endl;
    cout << "k4 = nullptr" << endl;
    k4 = nullptr;
    cout << "k4.use_count() = " << k4.use_count() << endl;
    
    cout << "---- Program end ------" << endl;
}