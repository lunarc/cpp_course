#include <materials/materials.h>

#include <cmath>
#include <stdexcept>

namespace materials {

const std::vector<Material>& all()
{
    static const std::vector<Material> database = {
        {"steel", 7850.0, 210e9, 0.30, 250e6},
        {"aluminium", 2700.0, 70e9, 0.33, 95e6},
        {"titanium", 4500.0, 116e9, 0.34, 880e6},
        {"copper", 8960.0, 117e9, 0.34, 70e6},
        {"concrete", 2400.0, 30e9, 0.20, 3e6},
    };
    return database;
}

const Material& find(const std::string& name)
{
    for (const auto& m : all())
        if (m.name == name)
            return m;
    throw std::out_of_range("Unknown material: " + name);
}

double shear_modulus(const Material& m)
{
    return m.youngs_modulus / (2.0 * (1.0 + m.poissons_ratio));
}

double bulk_modulus(const Material& m)
{
    return m.youngs_modulus / (3.0 * (1.0 - 2.0 * m.poissons_ratio));
}

double rod_wave_speed(const Material& m)
{
    return std::sqrt(m.youngs_modulus / m.density);
}

} // namespace materials
