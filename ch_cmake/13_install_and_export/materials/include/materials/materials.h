#pragma once

#include <string>
#include <vector>

namespace materials {

// Linear elastic, isotropic material.
struct Material
{
    std::string name;
    double density;        // [kg/m^3]
    double youngs_modulus; // [Pa]
    double poissons_ratio; // [-]
    double yield_stress;   // [Pa]
};

// Look up a material by name. Throws std::out_of_range if unknown.
const Material& find(const std::string& name);

// All materials in the database.
const std::vector<Material>& all();

// Derived elastic properties.
double shear_modulus(const Material& m);
double bulk_modulus(const Material& m);

// Speed of longitudinal waves in a thin rod, sqrt(E / rho) [m/s].
double rod_wave_speed(const Material& m);

} // namespace materials
