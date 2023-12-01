#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

int main()
{
    std::vector v = { 6, 4, 7, 3, 9, 0, 1, 5 };

    if (std::all_of(v.begin(), v.end(), [](int i) { return i < 10; }))
        std::cout << "All values of v are less than 10." << std::endl;

    if (std::any_of(v.begin(), v.end(), [](int i) { return i % 2 == 0; }))
        std::cout << "Some of the values are even." << std::endl;

    if (std::none_of(v.begin(), v.end(), [](int i) { return i < 0; }))
        std::cout << "No numbers are less than zero." << std::endl;

    if (std::ranges::all_of(v, [](int i) { return i < 10; }))
        std::cout << "All values of v are less than 10. (ranges)" << std::endl;

    if (std::ranges::any_of(v, [](int i) { return i % 2 == 0; }))
        std::cout << "Some of the values are even. (ranges)" << std::endl;

    if (std::ranges::none_of(v, [](int i) { return i < 0; }))
        std::cout << "No numbers are less than zero. (ranges)" << std::endl;

    auto number_of_values = std::count(v.begin(), v.end(), 5);
    std::cout << number_of_values << " items with the value 5 in v2. " << std::endl;

    number_of_values = std::ranges::count(v, 5);
    std::cout << number_of_values << " items with the value 5 in v2. " << std::endl;

    auto even_numbers = std::count_if(v.begin(), v.end(), [](int i) {return i % 2 == 0; });
    std::cout << even_numbers << " even numbers in v2." << std::endl;

    even_numbers = std::ranges::count_if(v, [](int i) {return i % 2 == 0; });
    std::cout << even_numbers << " even numbers in v2 (ranges)." << std::endl;
}
