#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    string line;
    ifstream infile;
    infile.open("../data/AEP_hourly.csv");

    while (infile.good())
    {
        getline(infile, line);
        cout << line << endl;
    }
    infile.close();
}
