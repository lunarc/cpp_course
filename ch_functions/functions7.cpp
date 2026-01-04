#include <print>

void print_array_1(int* a)
{
    for (int i=0; i<4; i++)
        std::print("{}, ", a[i]);
    std::println("");
}

void print_array_2(int a[])
{
    for (int i=0; i<4; i++)
        std::print("{}, ", a[i]);
    std::println("");
}

int main()
{
    int a[] = { 1, 2, 3, 4 };
    print_array_1(a);
    print_array_2(a);
}
