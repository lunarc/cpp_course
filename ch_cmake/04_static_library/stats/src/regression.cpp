#include <stats/descriptive.h>
#include <stats/regression.h>

namespace stats {

LinearFit linear_fit(std::span<const double> x, std::span<const double> y)
{
    const double mx = mean(x);
    const double my = mean(y);

    double sxy = 0.0, sxx = 0.0, syy = 0.0;
    for (std::size_t i = 0; i < x.size(); ++i)
    {
        sxy += (x[i] - mx) * (y[i] - my);
        sxx += (x[i] - mx) * (x[i] - mx);
        syy += (y[i] - my) * (y[i] - my);
    }

    LinearFit fit;
    fit.slope = sxy / sxx;
    fit.intercept = my - fit.slope * mx;
    fit.r2 = (sxy * sxy) / (sxx * syy);
    return fit;
}

} // namespace stats
