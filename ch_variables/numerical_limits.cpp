#include <print>
#include <limits>

int main()
{
    std::println("Max, char {}", int(std::numeric_limits<char>::max()));
    std::println("Min, char {}", int(std::numeric_limits<char>::min()));
    std::println("Is char signed {}", std::numeric_limits<char>::is_signed);
    std::println("Max, unsigned char {}", int(std::numeric_limits<unsigned char>::max()));
    std::println("Min, unsigned char {}", int(std::numeric_limits<unsigned char>::min()));
    std::println("Max, short {}", std::numeric_limits<short>::max());
    std::println("Min, short {}", std::numeric_limits<short>::min());
    std::println("Max, int {}", std::numeric_limits<int>::max());
    std::println("Min, int {}", std::numeric_limits<int>::min());
    std::println("Max, long {}", std::numeric_limits<long>::max());
    std::println("Min, long {}", std::numeric_limits<long>::min());
    std::println("Max, float {}", std::numeric_limits<float>::max());
    std::println("Min, float {}", std::numeric_limits<float>::min());
    std::println("Max, double {}", std::numeric_limits<double>::max());
    std::println("Min, double {}", std::numeric_limits<double>::min());
    std::println("Max, long double {}", std::numeric_limits<long double>::max());
    std::println("Min, long double {}", std::numeric_limits<long double>::min());
}
