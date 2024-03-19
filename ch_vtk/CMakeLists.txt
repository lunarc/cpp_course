add_executable(vtk1 vtk1.cpp)
target_link_libraries(vtk1 PRIVATE ${VTK_LIBRARIES})

vtk_module_autoinit(
  TARGETS vtk1
  MODULES ${VTK_LIBRARIES}
)

add_executable(vtk2 vtk2.cpp)
target_link_libraries(vtk2 PRIVATE ${VTK_LIBRARIES})

vtk_module_autoinit(
  TARGETS vtk2
  MODULES ${VTK_LIBRARIES}
)

add_executable(vtk3 vtk3.cpp)
target_link_libraries(vtk3 PRIVATE ${VTK_LIBRARIES})

vtk_module_autoinit(
  TARGETS vtk3
  MODULES ${VTK_LIBRARIES}
)

set_target_properties(
    vtk1
    vtk2
    vtk3
    PROPERTIES
    FOLDER "ch_modern"
)