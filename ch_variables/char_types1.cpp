#include <print>

int main()
{
    char c;
    unsigned char uc;
    signed char sc;
    char16_t c16;
    char32_t c32;
    wchar_t w32;

    c = 'a';
    uc = 170;
    sc = 130;

    c16 = 'b';
    c32 = 'c';
    w32 = 'd';

    std::println("c = {} int(c) = {} sizeof(c) = {}", c, int(c), sizeof(c));
    std::println("uc = {} int(uc) = {} sizeof(c) = {}", uc, int(uc), sizeof(c));
    std::println("sc = {} int(sc) = {} sizeof(c) = {}", sc, int(sc), sizeof(c));
    std::println("c16 = {} int(c16) = {} sizeof(c16) = {}", char(c16), int(c16), sizeof(c16));
    std::println("c32 = {} int(c32) = {} sizeof(c32) = {}", char(c32), int(c32), sizeof(c16));
    std::println("w32 = {} int(w32) = {} sizeof(w32) = {}", char(w32), int(w32), sizeof(w32));
}
