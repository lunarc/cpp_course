set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (UNIX)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    add_executable(calculator
        slurm_task_farm.h
        slurm_task_farm.cpp
        slurm_wizard.h
        slurm_wizard.ui
        slurm_wizard.cpp
        main.cpp
    )

    target_link_libraries(slurm_wizard PRIVATE Qt5::Widgets)
else()
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

    qt_standard_project_setup()

    qt_add_executable(slurm_wizard
        slurm_task_farm.h
        slurm_task_farm.cpp
        slurm_wizard.h
        slurm_wizard.ui
        slurm_wizard.cpp
        main.cpp
    )
    target_link_libraries(slurm_wizard PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

    set_target_properties(slurm_wizard PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
    )

    add_custom_command(TARGET slurm_wizard POST_BUILD 
        COMMAND Qt6::windeployqt
        ARGS $<TARGET_FILE:slurm_wizard>
    )
endif()

set_target_properties(
    slurm_wizard
    PROPERTIES
    FOLDER "ch_qt"
)


# resources.qrc

