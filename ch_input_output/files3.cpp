#include <iostream>
#include <fstream>
#include <cmath>
#include <print>

int main()
{
	double pi = 4 * std::atan(1);
    double x = 0.0;
    double y;
    double dx = 0.1;

    std::ofstream outfile;
    outfile.open("inputfile.dat", std::ios::out);
    while (x<=pi*0.25)
    {
        outfile << x << " " << sin(x) << "\n";
        x += dx;
    }
    outfile.close();
        
    std::ifstream infile;
    infile.open("inputfile.dat");
    while (infile.good())
    {
        infile >> x >> y;
        std::print("x = {}, y = {}\n", x, y);
    }
    infile.close();
}