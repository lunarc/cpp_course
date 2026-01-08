python test_build.py build_ext --inplace
python -c "import test_ext; print(test_ext.add(2, 3))"