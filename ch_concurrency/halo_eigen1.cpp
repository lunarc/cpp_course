#include <Eigen/Dense>
#include <iomanip>
#include <iostream>
#include <omp.h>

class StencilComputation {
private:
    Eigen::MatrixXd current_grid;
    Eigen::MatrixXd next_grid;
    int size;

public:
    StencilComputation(int n) : size(n)
    {
        current_grid = Eigen::MatrixXd::Zero(n, n);
        next_grid = Eigen::MatrixXd::Zero(n, n);
    }

    void initialize()
    {
// Set initial conditions
#pragma omp parallel for collapse(2)
        for (int i = 1; i < size - 1; i++)
        {
            for (int j = 1; j < size - 1; j++)
            {
                current_grid(i, j) = 0.0;
            }
        }

// Set boundary conditions
#pragma omp parallel sections
        {
#pragma omp section
            {
                // Top boundary
                for (int j = 0; j < size; j++)
                {
                    current_grid(0, j) = 100.0;
                    next_grid(0, j) = 100.0;
                }
            }
#pragma omp section
            {
                // Bottom boundary
                for (int j = 0; j < size; j++)
                {
                    current_grid(size - 1, j) = 0.0;
                    next_grid(size - 1, j) = 0.0;
                }
            }
#pragma omp section
            {
                // Left boundary
                for (int i = 0; i < size; i++)
                {
                    current_grid(i, 0) = 50.0;
                    next_grid(i, 0) = 50.0;
                }
            }
#pragma omp section
            {
                // Right boundary
                for (int i = 0; i < size; i++)
                {
                    current_grid(i, size - 1) = 50.0;
                    next_grid(i, size - 1) = 50.0;
                }
            }
        }
    }

    void step()
    {
// Compute next timestep
#pragma omp parallel for collapse(2)
        for (int i = 1; i < size - 1; i++)
        {
            for (int j = 1; j < size - 1; j++)
            {
                next_grid(i, j) = 0.25 * (current_grid(i - 1, j) + current_grid(i + 1, j) + current_grid(i, j - 1) +
                                          current_grid(i, j + 1));
            }
        }

        // Swap grids
        std::swap(current_grid, next_grid);
    }

    void print_grid() const
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                std::cout << std::fixed << std::setprecision(1) << current_grid(i, j) << " ";
            }
            std::cout << "\n";
        }
    }

    double get_value(int i, int j) const
    {
        return current_grid(i, j);
    }
};

int main()
{
    const int N = 6000;       // Grid size
    const int max_iter = 100; // Number of iterations

    // Set number of OpenMP threads
    omp_set_num_threads(8);

    StencilComputation stencil(N);
    stencil.initialize();

    std::cout << "Initial state:\n";
    // stencil.print_grid();

    double start_time = omp_get_wtime();

    // Time stepping
    for (int iter = 0; iter < max_iter; iter++)
    {
        stencil.step();

        if (iter % 20 == 0)
        {
#pragma omp single
            {
                std::cout << "Completed iteration " << iter << "\n";
            }
        }
    }

    double end_time = omp_get_wtime();

    std::cout << "\nFinal state:\n";
    // stencil.print_grid();
    std::cout << "Computation took " << end_time - start_time << " seconds\n";

    return 0;
}
