#include <iostream>
#include <fstream>

int main()
{
    std::ofstream myfile;
    myfile.open("myfile.txt");
    myfile << "Hello file!" << "\n";
    myfile << "Second line" << "\n";
    myfile.close();
}