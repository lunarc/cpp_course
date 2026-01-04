#include <print>
#include <string>

int main()
{
    std::string s = "The quick brown fox jumps over the lazy dog.";
    
    auto p0 = s.find("o");
    auto p1 = s.find("o", p0+1);
    auto p2 = s.find("xx");
    
    std::println("The first 'o' is at position {}", p0);
    std::println("The next 'o' is at position {}", p1);

    if (p2 == std::string::npos)
        std::println("xx was not found.");
    else
        std::println("xx was found.");
}
