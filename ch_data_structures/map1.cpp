#include <print>
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
        std::println("{}, {}", it->first, it->second);

    std::println("");

    for (auto &item : m)
        std::println("{}, {}", item.first, item.second);

    std::println("");

    for (auto &[key, value] : m)
        std::println("{}, {}", key, value);

    std::println("");

    auto it = m.find("bob");
    std::println("found: {}, {}", it->first, it->second);

    it = m.find("carl");

    if (it != m.end())
        std::println("found: {}, {}", it->first, it->second);
    else
        std::println("Could not find Carl.");
}
