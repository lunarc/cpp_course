#include <print>

int main()
{
    enum { Red, Green, Blue, Yellow };

    std::println("RED = {}", static_cast<int>(Red));
    std::println("GREEN = {}", static_cast<int>(Green));
    std::println("BLUE = {}", static_cast<int>(Blue));
    std::println("YELLOW = {}", static_cast<int>(Yellow));

    int simple_color = Green;

    std::println("simple_color = {}", simple_color);

    enum flavor { Vanilla, Chocolate, Orange, Strawberry };

    flavor selectedFlavor = Orange;

    std::println("selectedFlavor = {}", static_cast<int>(selectedFlavor));

    enum status { Finished = 0, Error = 15 };

    status currentStatus = Error;

    std::println("currentStatus = {}", static_cast<int>(currentStatus));
}
