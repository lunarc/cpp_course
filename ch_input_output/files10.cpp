#include <array>
#include <fstream>
#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    ifstream infile;
    infile.open("../data/colorado_elev.vit", ios::in | ios::binary);

    if (!infile.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    std::array<uint8_t, 400 * 400> buffer;

    infile.seekg(268, ios::beg);

    infile.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

    infile.close();

    fstream outfile;
    outfile.open("../data/colorado_elev.csv", ios::out);

    if (!outfile.is_open())
    {
		cout << "Error opening file" << endl;
		return 1;
	}

    for (auto i = 0; i < 400; i++)
    {
        for (auto j = 0; j < 400; j++)
            outfile << static_cast<int>(buffer[i * 400 + j]) << ",";
        outfile << "\n";
    }

    outfile.close();
}
