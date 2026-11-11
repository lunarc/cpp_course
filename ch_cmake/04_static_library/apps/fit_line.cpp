#include <stats/regression.h>

#include <print>
#include <vector>

int main()
{
    // Strain [-] and stress [MPa] in the elastic region of a steel specimen.
    std::vector<double> strain = {0.0000, 0.0002, 0.0004, 0.0006, 0.0008, 0.0010};
    std::vector<double> stress = {0.0, 41.8, 83.1, 124.9, 165.7, 208.2};

    auto fit = stats::linear_fit(strain, stress);

    std::println("Young's modulus E = {:.1f} GPa", fit.slope / 1000.0);
    std::println("Intercept         = {:.3f} MPa", fit.intercept);
    std::println("R^2               = {:.6f}", fit.r2);

    return 0;
}
