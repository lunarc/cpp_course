#include <print>
#include <string>

int main()
{
    std::string s1 = "hello";
    std::string s2 = ", world";
    std::string s3 = s1 + s2;

    s3.append(". Strings in C++ are great!");
    std::println("s3 = {}", s3);
    
    s3.replace(33, 6, "nice! ");
    std::println("s3 = {}", s3);
    
    s3.insert(33, "great and ");
    std::println("s3 = {}", s3);
    
    std::string s4 = s3.substr(33, 6);
    std::println("s4 = {}", s4);
    
}