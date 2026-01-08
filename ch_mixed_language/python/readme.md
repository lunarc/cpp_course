# Create comprehensive build environment
conda create -n mixed-lang-dev python=3.11 -c conda-forge

conda activate mixed-lang-dev

# Core build tools
conda install -c conda-forge \
    compilers \
    cmake \
    ninja \
    make \
    pkg-config

# Python development
conda install -c conda-forge \
    setuptools \
    wheel \
    pip \
    cython \
    pybind11 \
    numpy \
    pytest

# Scientific libraries (for examples)
conda install -c conda-forge \
    openblas \
    lapack \
    eigen \
    boost-cpp

# Development tools
conda install -c conda-forge \
    gdb \
    valgrind  # Linux only