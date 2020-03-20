# Force CMake version 3.1 or above
cmake_minimum_required (VERSION 3.1)

# This project has the name: H08-unit-converter
project (H08-unit-converter)

# Create an executable named 'unit-converter' from the source file 'unit-converter.cxx'
add_executable(unit-converter src/unit-converter.cxx)

target_compile_features(unit-converter PRIVATE cxx_auto_type)
target_compile_features(unit-converter PRIVATE cxx_default_function_template_args)
