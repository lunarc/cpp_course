set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (LINUX)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)

    add_executable(buttons
        mainwindow.ui
        mainwindow.cpp
        main.cpp
    )

    target_link_libraries(buttons PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)
else()
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

    qt_standard_project_setup()

    add_executable(buttons
        mainwindow.h
        mainwindow.cpp
        main.cpp
    )
    target_include_directories(buttons PRIVATE ${EXPRTK_INCLUDE_DIRS})
    target_link_libraries(buttons PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

    set_target_properties(buttons PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
    )

    add_custom_command(TARGET buttons POST_BUILD 
        COMMAND Qt6::windeployqt
        ARGS $<TARGET_FILE:buttons>
    )
endif()

set_target_properties(
    qt_step4
    PROPERTIES
    FOLDER "ch_qt"
)


# resources.qrc

