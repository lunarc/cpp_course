#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    ofstream outfile;
    outfile.open("myfile.txt", ios::out);
    outfile << "Hello file!" << endl;
    outfile << "Second line" << endl;
    outfile.close();

    outfile.open("myfile.txt", ios::out | ios::app);
    outfile << "Third line" << endl;
    outfile.close();
    
    ifstream infile;
    infile.open("myfile2.txt");
    if (!infile.is_open())
        cout << "Could not open file!" << endl;
    else
        infile.close();
}