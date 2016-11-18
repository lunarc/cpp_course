#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

int main()
{
    string line;
    fstream nameFile("../../../../exercises/data_structures/names.txt", ios::in);
    
    map<string, string> nameMap;
    
    while (nameFile.good())
    {
        getline(nameFile, line);
        string firstName;
        string lastName;
        
        istringstream linestream(line);
        linestream >> firstName >> lastName;
        
        nameMap[lastName] = firstName + " " + lastName;
    }
    
    nameFile.close();
    
    fstream sortedFile("../../../../exercises/data_structures/sorted_names.txt", ios::out);
    
    map<string, string>::iterator it;
    
    for (it=nameMap.begin(); it!=nameMap.end(); it++)
        sortedFile << it->second << endl;

    sortedFile.close();    
    
}