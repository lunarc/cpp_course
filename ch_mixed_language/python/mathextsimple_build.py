from setuptools import setup, Extension
import pybind11

ext = Extension(
    'mathextsimple',
    sources=['mathextsimple.cpp'],
    include_dirs=[pybind11.get_include()],
    language='c++',
    extra_compile_args=['-std=c++17'],
)

setup(
    name='mathextsimple',
    ext_modules=[ext],
)