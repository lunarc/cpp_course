#include_directories(/opt/local/include /usr/include/python2.7)
link_directories(/opt/local/lib)

add_library(particles SHARED mymodule1.cpp)

target_link_libraries (particles boost_python-mt
    ${PYTHON_LIBRARIES}
    ${Boost_LIBRARIES}
)

set_target_properties(particles PROPERTIES PREFIX "")

