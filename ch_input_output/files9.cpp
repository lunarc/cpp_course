#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

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
            string strValue = line.substr(pos - line.begin() + 1);

            double dval = 0.0;

            try
            {
                dval = std::stod(strValue);
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }

            std::cout << "date:  " << date << " value: " << dval << "\n";
        }
    }
    infile.close();
}
