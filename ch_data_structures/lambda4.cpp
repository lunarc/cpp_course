#include <algorithm>
#include <print>
#include <vector>
#include <functional>

int main()
{
    std::vector v = { 6, 4, 7, 3, 9, 0, 1, 5 };

    if (std::all_of(v.begin(), v.end(), [](int i) { return i < 10; }))
        std::println("All values of v are less than 10.");

    if (std::any_of(v.begin(), v.end(), [](int i) { return i % 2 == 0; }))
        std::println("Some of the values are even.");

    if (std::none_of(v.begin(), v.end(), [](int i) { return i < 0; }))
        std::println("No numbers are less than zero.");

    if (std::ranges::all_of(v, [](int i) { return i < 10; }))
        std::println("All values of v are less than 10. (ranges)");

    if (std::ranges::any_of(v, [](int i) { return i % 2 == 0; }))
        std::println("Some of the values are even. (ranges)");

    if (std::ranges::none_of(v, [](int i) { return i < 0; }))
        std::println("No numbers are less than zero. (ranges)");

    auto number_of_values = std::count(v.begin(), v.end(), 5);
    std::println("{} items with the value 5 in v2. ", number_of_values);

    number_of_values = std::ranges::count(v, 5);
    std::println("{} items with the value 5 in v2. ", number_of_values);

    auto even_numbers = std::count_if(v.begin(), v.end(), [](int i) {return i % 2 == 0; });
    std::println("{} even numbers in v2.", even_numbers);

    even_numbers = std::ranges::count_if(v, [](int i) {return i % 2 == 0; });
    std::println("{} even numbers in v2 (ranges).", even_numbers);
}
