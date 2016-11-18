#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    string line;
    ifstream infile;
    infile.open("/etc/hosts");
    while (infile.good())
    {
        getline(infile, line);
        string addr;
        string host;
        
        istringstream linestream(line);
        linestream >> addr >> host;
        
        cout << "address = " << addr << ", host = " << host << endl;
    }
    infile.close();
}