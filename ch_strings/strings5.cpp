#include <print>
#include <cstring>
#include <string>

int main()
{
    const char* cString;
    char cString2[128];
    
    std::string cppString = "Hello, world!";
    
    cString = cppString.c_str();
    
    std::println("cString = {}", cString);
#ifndef WIN32
    strncpy(cString2, cppString.c_str(), cppString.length()+1);
#else
    strncpy_s(cString2, cppString.c_str(), cppString.length()+1);
#endif
    std::println("cString2 = {}", cString2);
}
