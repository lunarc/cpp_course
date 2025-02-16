#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    string line;
    ifstream infile;
    infile.open("../data/AEP_hourly.csv");

    if (!infile.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    while (infile.good())
    {
        getline(infile, line);
        cout << line << endl;
    }
    infile.close();
}
