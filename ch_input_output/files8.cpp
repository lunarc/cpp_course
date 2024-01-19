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

        auto pos = std::find(line.begin(), line.end(), ',');

        if (pos != line.end())
        {
            string date = line.substr(0, pos - line.begin());
            string value = line.substr(pos - line.begin() + 1);

            std::cout << "date:  " << date << " value: " << value << "\n";
        }
    }
    infile.close();
}
