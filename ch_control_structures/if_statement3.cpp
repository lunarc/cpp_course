#include <iostream>

using namespace std;

int main()
{
    for (int i=1; i<=10; i++)
    {
        cout << "i = " << i << ": ";
        
        if (i==5)
            cout << "i == 5" << endl;
        else if ( (i>=2)&&(i<=3) )
            cout << "2 <= i <= 3" << endl;
        else
            cout << "-" << endl;
    }
}