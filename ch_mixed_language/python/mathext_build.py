from setuptools import setup, Extension
import pybind11

ext = Extension(
    'mathext',
    sources=['mathext.cpp'],
    include_dirs=[pybind11.get_include()],
    language='c++',
    extra_compile_args=['-std=c++17'],
)

setup(
    name='mathext',
    ext_modules=[ext],
)