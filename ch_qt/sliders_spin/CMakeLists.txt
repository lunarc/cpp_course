set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (LINUX)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    add_executable(sliders_spin
        mainwindow.ui
        mainwindow.cpp
        main.cpp
    )

    target_link_libraries(sliders_spin PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)
else()
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

    qt_standard_project_setup()

    add_executable(sliders_spin
        mainwindow.h
        mainwindow.cpp
        main.cpp
    )
    target_include_directories(sliders_spin PRIVATE ${EXPRTK_INCLUDE_DIRS})
    target_link_libraries(sliders_spin PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

    set_target_properties(sliders_spin PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
    )

    add_custom_command(TARGET sliders_spin POST_BUILD 
        COMMAND Qt6::windeployqt
        ARGS $<TARGET_FILE:sliders_spin>
    )
endif()

set_target_properties(
    sliders_spin
    PROPERTIES
    FOLDER "ch_qt"
)


# resources.qrc

