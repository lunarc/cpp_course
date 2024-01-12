#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    string line;
    ifstream infile;
#ifdef _WIN32
    infile.open("C:\\Windows\\System32\\drivers\\etc\\hosts");
#else
    infile.open("/etc/hosts");
#endif
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
