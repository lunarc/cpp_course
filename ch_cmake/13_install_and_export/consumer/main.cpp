#include <materials/materials.h>

#include <print>

int main()
{
    std::println("{:<12}{:>10}{:>10}{:>10}{:>12}", "Material", "E [GPa]", "G [GPa]", "K [GPa]",
                 "c [m/s]");

    for (const auto& m : materials::all())
    {
        std::println("{:<12}{:>10.1f}{:>10.1f}{:>10.1f}{:>12.1f}", m.name, m.youngs_modulus / 1e9,
                     materials::shear_modulus(m) / 1e9, materials::bulk_modulus(m) / 1e9,
                     materials::rod_wave_speed(m));
    }

    return 0;
}
