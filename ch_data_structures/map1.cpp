#include <iostream>
#include <map>
#include <string>

int main()
{
    std::map<std::string, int> m;

    m["bob"] = 42;
    m["alice"] = 40;
    m["mike"] = 30;
    m["richard"] = 25;

    m.insert({"john", 84});

    for (auto it = m.begin(); it != m.end(); it++)
        std::cout << it->first << ", " << it->second << "\n";

    std::cout << "\n";

    for (auto &item : m)
        std::cout << item.first << ", " << item.second << "\n";

    std::cout << "\n";

    for (auto &[key, value] : m)
        std::cout << key << ", " << value << "\n";

    std::cout << "\n";

    auto it = m.find("bob");
    std::cout << "found: " << it->first << ", " << it->second << "\n";

    it = m.find("carl");

    if (it != m.end())
        std::cout << "found: " << it->first << ", " << it->second << "\n";
    else
        std::cout << "Could not find Carl." << std::endl;
}
