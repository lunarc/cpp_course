#include <print>
#include <map>
#include <string>

int main()
{
    std::map<std::string,int> m;
    
    m["bob"] = 42;
    m["alice"] = 40;
    m["mike"] = 30;
    m["richard"] = 25;
    
    for (auto it=m.begin(); it!=m.end(); it++)
        std::println("{}, {}", it->first, it->second);
    
    m.erase(m.find("mike"));

    std::println("--");
    
    for (auto it=m.begin(); it!=m.end(); it++)
        std::println("{}, {}", it->first, it->second);
    
    m.insert(std::pair<std::string,int>("carl", 43));

    std::println("--");
    
    for (auto it=m.begin(); it!=m.end(); it++)
        std::println("{}, {}", it->first, it->second);
    
    m.clear();
    
    std::println("--");
    
    for (auto it=m.begin(); it!=m.end(); it++)
        std::println("{}, {}", it->first, it->second);
    
    std::println("m.size() = {}", m.size());

}