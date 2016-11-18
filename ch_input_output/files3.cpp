#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
	double pi = 4 * std::atan(1);
    double x = 0.0;
    double y;
    double dx = 0.1;

    ofstream outfile;
    outfile.open("inputfile.dat", ios::out);
    while (x<=pi*0.25)
    {
        outfile << x << " " << sin(x) << endl;
        x += dx;
    }
    outfile.close();
        
    ifstream infile;
    infile.open("inputfile.dat");
    while (infile.good())
    {
        infile >> x >> y;
        cout << "x = " << x << ", y = " << y << endl;
    }
    infile.close();
}