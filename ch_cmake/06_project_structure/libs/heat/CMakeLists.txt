# Paths in this file are relative to this directory (libs/heat).

add_library(heat STATIC
    src/heat1d.cpp
    include/heat/heat1d.h
)

target_include_directories(heat PUBLIC include)
target_compile_features(heat PUBLIC cxx_std_23)

# An alias with a namespace-like name. Linking to heat::heat gives a
# clear error if the target is missing, whereas a misspelled plain name
# would be treated as a system library and fail much later at link time.
add_library(heat::heat ALIAS heat)
