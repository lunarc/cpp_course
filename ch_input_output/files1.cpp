#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    ofstream myfile;
    myfile.open("myfile.txt");
    myfile << "Hello file!" << endl;
    myfile << "Second line" << endl;
    myfile.close();
}