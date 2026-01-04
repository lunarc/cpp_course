#include <print>
#include <string>

int main()
{
    std::string s1 = "hello";
    std::string s2 = ", world";
    std::string s3 = s1 + s2;
    std::println("s3 = '{}'", s3);
    std::println("s3.length() = {}", s3.length());
    std::println("s3[7] = {}", s3[7]);
    std::println("s3.at(7) = {}", s3.at(7));
}