from setuptools import setup, Extension
import pybind11

ext = Extension(
    'test_ext',
    sources=['test_ext.cpp'],
    include_dirs=[pybind11.get_include()],
    language='c++',
    extra_compile_args=['-std=c++17'],
)

setup(
    name='test_ext',
    ext_modules=[ext],
)